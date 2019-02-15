#pragma once
#include <string>
#include <vector>
#include <list>
#include <map>
#include <iostream>

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
	~proc();
};

class mem
{
public:
	char pw[256];
	char ram[128];
	bool zaj_pw[16];
	std::list<int> zaj_ram;
	unsigned int wolne = 16;
	std::vector<proc*> proceski;

	mem();
	~mem();

	void dodaj_proces(int pid, std::string roz);
	void usun_proces(int pid);
	void wpisz_do_ramu(int pid);
	void wpisz_do_pw(int pid, std::string roz);
	void wypisz_ram();
	void wypisz_pw();
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
		if (e->pid == pid)
		{
			e->pcb++;
			return;
		}
		
	}
}

 void mem::dodaj_proces(int pid, std::string roz)
 {
	 for (auto e : proceski)
	 {
		 if (e->pid == pid) return;
	 }
	 unsigned int rozm = roz.length();
	 unsigned int ilosc = ceil(rozm / 16.00);
	 if (wolne < ilosc) return;
	 int pos = 0;
	 proc *e = new proc(pid);
	 bool koniec = true;
	 while (koniec)
	 {
		 for (int i = 0; i < ilosc; i++)
		 {
			 wolne--;
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
	proceski.push_back(e);
}

 void mem::usun_proces(int pid)
{
	int pos = 0;
	for (auto &e : proceski)
	{
		if (e->pid == pid)
		{
			for (auto i : e->stronice)
			{
				for (int j = i * 16; j < (i * 16) + 16; j++)
				{
					pw[j] = ' ';
				}
				zaj_pw[i] = false;
				wolne++;
			}
			proceski.erase(proceski.begin() + pos);
			return;
		}
		pos++;
	}
}

 void mem::wpisz_do_ramu(int pid)
{
	int pos = 0;
	for (auto &e : proceski)
	{
		if (e->pid == pid)
		{
			int k = zaj_ram.front();
			zaj_ram.pop_front();
			for(int i = 0; i < 16; i++)
			{
				ram[i+k] = pw[(e->stronice[e->pcb])*16 + i];
				pw[(e->stronice[e->pcb]) * 16 + i] = ' ';
			}
			zaj_ram.push_back(k);
		}
		pos++;
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
}

 void mem::wypisz_pw()
 {
	 for (int o = 0; o < 16; o++)
	 {
		 int addr = o * 16;
		 std::cout << "Linia nr: " << o;
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
 }