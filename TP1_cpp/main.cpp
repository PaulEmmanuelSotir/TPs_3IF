#include <iostream>
#include <sstream> // used for std::cout stream redirection

#include "collection.h"

// Avoid compiler optimization for this test if possible
#ifdef __GNUC__
#pragma GCC push_options
#pragma GCC optimize ("O0")
#elif _MSC_VER
#pragma optimize("", off)
#endif

static const char* test_lifetime()
{
	{
		TP1::dog dogsArray[3] = {
			TP1::dog(TP1::color::GREEN, 50),
			TP1::dog(TP1::color::RED, 3),
			TP1::dog(TP1::color::BLUE, 99) };

		TP1::collection dogs1(3);
		TP1::collection dogs2(dogsArray, 3);
	} // 'dogs1' and 'dogs2' destructors will be called here

	volatile auto dogs = new TP1::collection(100);
	delete dogs;

	// Return expected output
	return "";
}

#ifdef __GNUC__
#pragma GCC pop_options
#elif _MSC_VER
#pragma optimize("", on)
#endif

static const char* test_afficher()
{
	TP1::dog dogsArray[3] = {
		TP1::dog(TP1::color::GREEN, 50),
		TP1::dog(TP1::color::RED, 3),
		TP1::dog(TP1::color::BLUE, 99) };

	TP1::collection dogs1(dogsArray, 3);
	TP1::collection dogs2(2);

	dogs1.afficher();
	std::cout << " ";
	dogs2.afficher();

	// Return expected output
	return "{ 50, 3, 99 } { }";
}

static const char* test_ajouter()
{
	{
		TP1::dog dogsArray[3] = {
			TP1::dog(TP1::color::GREEN, 50),
			TP1::dog(TP1::color::RED, 3),
			TP1::dog(TP1::color::BLUE, 99) };

		TP1::collection dogs(dogsArray, 3);
		dogs.ajouter(TP1::dog(TP1::color::GREEN, 5));
		dogs.afficher();
	}

	std::cout << " ";

	{
		TP1::collection dogs(0);
		dogs.ajouter(TP1::dog(TP1::color::GREEN, 5));
		dogs.afficher();
	}

	// Return expected output
	return "{ 50, 3, 99, 5 } { 5 }";
}

static const char* test_retirer()
{
	TP1::dog dogsArray[3] = {
		TP1::dog(TP1::color::GREEN, 50),
		TP1::dog(TP1::color::RED, 3),
		TP1::dog(TP1::color::BLUE, 99) };

	{
		TP1::collection dogs(dogsArray, 3);
		dogs.retirer(nullptr, 0);
		dogs.afficher();
	}

	std::cout << " ";

	{
		TP1::collection dogs(dogsArray, 3);
		dogs.retirer(dogsArray, 3);
		dogs.afficher();
	}

	std::cout << " ";

	{
		TP1::collection dogs(dogsArray, 3);
		dogs.ajouter(TP1::dog(TP1::color::RED, 3));
		dogs.retirer(dogsArray[1]);
		dogs.afficher();
	}

	std::cout << " ";

	{
		TP1::collection dogs(0);
		dogs.ajouter(TP1::dog(TP1::color::GREEN, 5));
		dogs.retirer(dogsArray, 3);
		dogs.afficher();
	}

	// Return expected output
	return "{ 50, 3, 99 } { } { 50, 99 } { 5 }";
}

static const char* test_ajuster()
{
	TP1::dog dogsArray[3] = {
		TP1::dog(TP1::color::GREEN, 50),
		TP1::dog(TP1::color::RED, 3),
		TP1::dog(TP1::color::BLUE, 99) };

	{
		TP1::collection dogs(dogsArray, 3);
		dogs.ajouter(TP1::dog(TP1::color::YELLOW, 5));
		std::cout << dogs.ajuster(4) << " ";
		dogs.afficher();
	}

	std::cout << " ";

	{
		TP1::collection dogs(dogsArray, 3);
		std::cout << dogs.ajuster(2) << " ";
		dogs.afficher();
	}

	std::cout << " ";

	{
		TP1::collection dogs(5);
		std::cout << dogs.ajuster(0) << " ";
		dogs.afficher();
	}

	std::cout << " ";

	{
		TP1::collection dogs(dogsArray, 3);
		std::cout << dogs.ajuster(10) << " ";
		dogs.afficher();
	}

	// Return expected output
	return "1 { 50, 3, 99, 5 } 0 { 50, 3, 99 } 1 { } 1 { 50, 3, 99 }";
}

static const char* test_reunir()
{
	TP1::dog dogsArray[3] = {
		TP1::dog(TP1::color::GREEN, 50),
		TP1::dog(TP1::color::RED, 3),
		TP1::dog(TP1::color::BLUE, 99) };

	{
		TP1::dog dogsArray2[2] = {
			TP1::dog(TP1::color::RED, 4),
			TP1::dog(TP1::color::YELLOW, 1) };

		TP1::collection dogs1(dogsArray, 3);
		TP1::collection dogs2(dogsArray2, 2);
		dogs1.reunir(dogs2);
		dogs1.afficher();
	}

	std::cout << " ";

	{
		TP1::collection dogs1(dogsArray, 3);
		TP1::collection dogs2(2);
		dogs1.reunir(dogs2);
		dogs1.afficher();
	}

	std::cout << " ";

	{
		TP1::collection dogs1(10);
		TP1::collection dogs2(dogsArray, 3);
		dogs1.reunir(dogs2);
		dogs1.afficher();
	}

	// Return expected output
	return "{ 50, 3, 99, 4, 1 } { 50, 3, 99 } { 50, 3, 99 }";
}

/*
* String comparition helper function
*/
static int string_cmp(const char* lhs, const char* rhs)
{
	const unsigned char *str1 = (const unsigned char *)lhs;
	const unsigned char *str2 = (const unsigned char *)rhs;

	while (*str1 != '\0') {
		if (*str2 == '\0') return  1;
		if (*str2 > *str1) return -1;
		if (*str1 > *str2) return  1;

		++str1;
		++str2;
	}

	// Return -1 if 'str2' has more characters than 'str1'
	if (*str2 != '\0')
		return -1;

	return 0;
}

/*
* Testing helper function
*/
static void test(const char*(*testFunc)(), const char* testName = "")
{
	static unsigned test_count = 0;

	if (testName[0] == '\0' || testName == nullptr)
		std::cout << std::endl << std::endl << "### TEST " << ++test_count << " ###" << std::endl;
	else
		std::cout << std::endl << std::endl << "### TEST " << ++test_count << " (" << testName << ") ###" << std::endl;

	// Create a std::stringstream to redirect std::cout output
	std::stringstream buffer;
	std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

	const char* expected_str;

	try {
		// Execute test function and get expected output
		expected_str = testFunc();
	}
	catch (...) {
		// Restore previous std::cout output buffer
		std::cout.rdbuf(old);

		std::cout << "FAILED : Throwed an exception!";
		return;
	}

	// Get real test output
	std::string str = buffer.str();
	const char* output = str.data();

	// Restore previous std::cout output buffer
	std::cout.rdbuf(old);

	// See if test output is as expected
	if (string_cmp(output, expected_str) == 0)
		std::cout << "PASSED (OUTPUT = \"" << output << "\")";
	else
		std::cout << "FAILED : wrong output (\tEXPECTED =\t\"" << expected_str << "\",\n\t\t\tOUTPUT =\t\"" << output << "\")" << std::endl;
}

int main()
{
	std::cout
		<< R"(			 _________ ___    _____  __    __ )" << std::endl
		<< R"(			/_  __/ _ <  /   / ___/_/ /___/ /_)" << std::endl
		<< R"(			 / / / ___/ /   / /__/_  __/_  __/)" << std::endl
		<< R"(			/_/ /_/  /_/    \___/ /_/   /_/   )" << std::endl << std::endl;

	std::cout << "### TESTING COLLECTION CLASS (no dogs will be harmed during this test) ###";

	test(test_lifetime, "OBJECT LIFETIME");
	test(test_afficher, "AFFICHER");
	test(test_ajouter, "AJOUTER");
	test(test_retirer, "RETIRER");
	test(test_ajuster, "AJUSTER");
	test(test_reunir, "REUNIR");

	std::cout << std::endl << std::endl << "Press ENTER to exit...";
	std::cin.get();

	return 0;
}
