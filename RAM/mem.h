#pragma once
#include <string>
#include <vector>
#include <list>
#include <map>
#include <iostream>

struct ts
{
	int pid;
	std::map<int, int> tablica;

	ts(int p)
	{
		this->pid = p;
	};

	~ts() = default;;
};

struct FIFO
{
	int pid;
	int strona;
};

struct proc
{
	int pid;
	std::vector<int> stronice;
	int pcb;


	proc(int p)
	{
		this->pid = p;
		this->pcb = 0;
	};
	~proc() = default;;
};

class mem
{
public:
	char pw[256];
	char ram[128];
	bool zaj_pw[16];
	std::list<int> zaj_ram;
	std::map<proc*,ts*> proceski;
	std::list<FIFO> kolejka;

	mem();
	~mem();

	void dodaj_proces(int pid, std::string roz);
	void usun_proces(int pid);
	void wpisz_do_ramu(int pid);
	void wpisz_do_pw(int pid, std::string roz);
	void wypisz_ram();
	void wypisz_pw();
	void wypisz_ts(int pid);
	void wypisz_tab();
	void wypisz_stronice(int pid);
	int znajdz_wolna();
	void wykonaj_krok(int pid);

};



mem::mem()
{
	for (auto e : zaj_pw)
	{
		zaj_pw[e] = false;
	}

	for (int i = 0; i < 8; i++)
	{
		zaj_ram.push_back(i*16);
	}

}


mem::~mem()
{
}

 int mem::znajdz_wolna()
{
	for(int i = 0; i < 16; i++)
	{
		if (!zaj_pw[i]) return i;
	}
	return  -1;
}

 void mem::wykonaj_krok(int pid)
{
	for (auto &e : proceski)
	{
		if (e.first->pid == pid)
		{
			e.first->pcb++;
			if (e.first->pcb > e.first->stronice.size())
			{
				usun_proces(pid);
			}
			return;
		}
		
	}
}

 void mem::dodaj_proces(int pid, std::string roz)
 {
	 for (auto &e : proceski)
	 {
		 if (e.first->pid == pid) return;
	 }
	 unsigned int rozm = roz.length();
	 unsigned int ilosc = ceil(rozm / 16.00);
	 int wolne = 0;
		for(auto e : zaj_pw) if(!e) wolne++;
	 if ( wolne < ilosc) return;
	 int pos = 0;
	 proc *e = new proc(pid);
	 ts   *a = new ts(pid);
	
	 bool koniec = true;
	 while (koniec)
	 {
		 for (int i = 0; i < ilosc; i++)
		 {
			 int t = znajdz_wolna();
			 e->stronice.push_back(t);
			 zaj_pw[t] = true;
			 for (int j = t * 16; j < (t * 16) + 16; j++)
			 {
				 if (pos >= rozm)
				 {
					 pw[j] = ' ';
					 koniec = false;
				 }
				 else
				 {
					 //std::cout << roz[pos] << " ";
					 pw[j] = roz[pos];
				 }
				 pos++;

			 }
			 
		 }
 }
	proceski.insert(std::pair<proc*,ts*>(e,a));
}

 void mem::usun_proces(int pid)
{
	int pos = 0;

	for (auto &e : proceski)
	{
		if (e.first->pid == pid)
		{
			int st = 0;
			for (auto i : e.first->stronice)
			{
				for (int j = i * 16; j < (i * 16) + 16; j++)
				{
					pw[j] = ' ';
				}
				zaj_pw[i] = false;
				
				st++;
			}
			e.first->stronice.erase(e.first->stronice.begin(),e.first->stronice.end());
			auto it = proceski.find(e.first);
			proceski.erase(it);
			return;
		}
	
		pos++;
	}
}

 void mem::wpisz_do_ramu(int pid)
{
	for (auto &e : proceski)
	{
		if (e.first->pid == pid)
		{
			int k = zaj_ram.front();
			zaj_ram.pop_front();
			e.second->tablica[e.first->stronice[e.first->pcb]] = k / 16;

			for(int i = 0; i < 16; i++)
			{
				ram[i+k] = pw[(e.first->stronice[e.first->pcb])*16 + i];
				pw[(e.first->stronice[e.first->pcb]) * 16 + i] = ' ';
			}
			zaj_ram.push_back(k);
		}
	}
}

 void mem::wypisz_ram()
{
	for (int o = 0; o < 8; o++)
	{
		int addr = o * 16;
		std::cout << "Ramka nr: " << o;
		if (o >= 0)
		{
			std::cout << ", zawiera strone nr: " << o;
		}
		std::cout << std::endl;

		for (int i = 0; i < 16; i++)
		{
			if (addr + i < 10)
				printf("  %d  |", addr + i);
			else
				printf(" %3d |", addr + i);
		}
		std::cout << std::endl;
		// wyzwietla zawartosc RAMu
		addr = o * 16;

		for (int i = 0; i < 16; i++)
		{
			printf("  %c  |", ram[addr + i]);

		}
		std::cout << std::endl;
		// ----------------------------------------------------------------------
		// wyzwietla spod ramki
	}
	std::cout << std::endl; 
	std::cout << std::endl;
}

 void mem::wypisz_pw()
 {
	 for (int o = 0; o < 16; o++)
	 {
		 int addr = o * 16;
		 std::cout << "Stronica nr: " << o;
		 if (o >= 0)
		 {
			 std::cout << ", zawiera ";
		 }
		 std::cout << std::endl;

		 for (int i = 0; i < 16; i++)
		 {
			 if (addr + i < 10)
				 printf("  %d  |", addr + i);
			 else
				 printf(" %3d |", addr + i);
		 }
		 std::cout << std::endl;
		 // wyzwietla zawartosc RAMu
		 addr = o * 16;

		 for (int i = 0; i < 16; i++)
		 {
			 printf("  %c  |", pw[addr + i]);

		 }
		 std::cout << std::endl;
		 // ----------------------------------------------------------------------
		 // wyzwietla spod ramki
	 }
	 std::cout << std::endl;
	 std::cout << std::endl;
 }

 void mem::wypisz_ts(int pid)
{
	for(auto &e : proceski)
	{
		if(e.first->pid == pid)
		{
			for (auto &r : e.second->tablica)
			{
				std::cout << "Proces: " << e.first->pid << " Stronica: " << r.first << " Rama: " << r.second << std::endl;
			}
		}
	}
}

 void mem::wypisz_tab()
{
	for(auto &e : proceski)
	{
		std::cout << "Proces: " << e.first->pid << std::endl;
		for(auto &r : e.second->tablica)
		{
			std::cout << "          Stronica: " << r.first << "    Rama: " << r.second << std::endl;
		}
		std::cout << "-------------------------------------" << std::endl;
	}
}