#include <iostream>

#include "collection.h"

// Avoid compiler optimization for this test if possible
#ifdef __GNUC__
#pragma GCC push_options
#pragma GCC optimize ("O0")
#elif _MSC_VER
#pragma optimize("", off)
#elif __MINGW32__
#pragma GCC push_options // TODO: verifier que ça compile avec mingw et ajouter mingw64
#pragma GCC optimize ("O0")
#endif

static void test_lifetime()
{
	dog * dogsArray[3] = { new dog(color::GREEN, 50),
		new dog(color::RED, 3),
		new dog(color::BLUE, 99) };

	{
		collection dogs1(3);
		collection dogs2(dogsArray, 3);
	}

	volatile collection* dogs3 = new collection(100);
	delete dogs3;
}

#ifdef __GNUC__
#pragma GCC pop_options
#elif _MSC_VER
#pragma optimize("", on)
#elif __MINGW32__
#pragma GCC pop_options // TODO: verifier que ça compile avec mingw et ajouter mingw64
#endif

static void test_afficher()
{
	dog * dogsArray[3] = { new dog(color::GREEN, 50),
						new dog(color::RED, 3),
						new dog(color::BLUE, 99) };
	collection dogs1(dogsArray, 3);
	collection dogs2(2);

	dogs1.afficher();
	std::cout << std::endl;
	dogs2.afficher();
}

static void test_ajouter()
{
	dog * dogsArray[3] = { new dog(color::GREEN, 50),
		new dog(color::RED, 3),
		new dog(color::BLUE, 99) };

	collection dogs1(dogsArray, 3);
	dogs1.ajouter(new dog(color::GREEN, 5));
	dogs1.afficher();

	collection dogs2(0);
	dogs2.ajouter(new dog(color::GREEN, 5));
	dogs2.afficher();

	collection dogs3(2);
	dogs3.ajouter(new dog(color::GREEN, 5));
	dogs3.ajouter(nullptr);
	dogs3.afficher();
}

static void test_retirer()
{

}

static void test_ajuster()
{

}

static void test_reunir()
{

}


/*
* Testing helper function
*/
static void test(void(*testFunc)(), const char* testName = "")
{
	static unsigned test_count = 0;

	if (testName != "" || testName == nullptr)
		std::cout << std::endl << std::endl << "### TEST " << ++test_count << " ###" << std::endl;
	else 
		std::cout << std::endl << std::endl << "### TEST " << ++test_count << " (" << testName << ") ###" << std::endl;

	try
	{
		testFunc();
		std::cout << "PASSED";
	}
	catch (...) // can't use std::exception :(
	{
		std::cout << "FAILED";
	}
}

void main()
{
	std::cout << "### TESTING COLLECTION CLASS (no dogs will be harmed during this test) ###";

	test(test_lifetime, "OBJECT LIFETIME");
	test(test_afficher, "AFFICHER");
	test(test_ajouter, "AJOUTER");
	test(test_retirer, "RETIRER");
	test(test_ajuster, "AJUSTER");
	test(test_reunir, "REUNIR");

	std::cout << std::endl << std::endl << "Press ENTER to exit...";
	std::cin.get();
}