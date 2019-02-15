#include "mem.h"

int main()
{

	std::string ps = "MV 3 4 CM RM 83 MR 0 83 OF fib XR 0 DR 3 JZ 64 CLF CP p3 1 JP 7 CLF SM 79 3 SP END ";
	std::string ps1 = "MV 2 4 MV 0 0 MV 1 1 EL 2 2 JZ 40 JP 52 MV 0 1 RT 0 ET MC 3 0 AD 0 1 MC 1 3 MW 0 124 SM 124 2 CM RM 129 DR 2 JZ 121 JE 0 SP";
	std::string ps2 = "MV 0 0 JP 16 MV 0 1 JP 32 MV 0 2 JP 48 MV 0 3 JP 64 MV 0 4 JP 80 MV 0 5 JP 96 MV 0 6 JP 112 MV 0 7 JP 128 MV 0 8 JP 144 MV 0 9 JP 160 SP";

	mem M = mem();

	M.dodaj_proces(1, ps);
	for(auto e : M.ram)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	M.wykonaj_krok(1);
	for (auto e : M.ram)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	M.wykonaj_krok(1);
	std::cout << std::endl;
	std::cout << std::endl;
	for (auto e : M.ram)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cin.ignore();
	return 1;
}