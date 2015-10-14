#include <iostream>
#include <sstream> // used for std::cout stream redirection

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

static const char* test_lifetime()
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

	// Return expected output
	return "";
}

#ifdef __GNUC__
#pragma GCC pop_options
#elif _MSC_VER
#pragma optimize("", on)
#elif __MINGW32__
#pragma GCC pop_options // TODO: verifier que ça compile avec mingw et ajouter mingw64
#endif

static const char* test_afficher()
{
	dog * dogsArray[3] = { new dog(color::GREEN, 50),
						new dog(color::RED, 3),
						new dog(color::BLUE, 99) };
	collection dogs1(dogsArray, 3);
	collection dogs2(2);

	dogs1.afficher();
	std::cout << std::endl;
	dogs2.afficher();

	// Return expected output
	return "";
}

static const char* test_ajouter()
{
	dog * dogsArray[3] = { new dog(color::GREEN, 50),
		new dog(color::RED, 3),
		new dog(color::BLUE, 99) };

	collection dogs1(dogsArray, 3);
	dogs1.ajouter(new dog(color::GREEN, 5));
	dogs1.afficher();
	std::cout << std::endl;

	collection dogs2(0);
	dogs2.ajouter(new dog(color::GREEN, 5));
	dogs2.afficher();
	std::cout << std::endl;

	collection dogs3(2);
	dogs3.ajouter(new dog(color::GREEN, 5));
	dogs3.ajouter(nullptr);
	dogs3.afficher();
	std::cout << std::endl;

	// Return expected output
	return "";
}

static const char* test_retirer()
{

	// Return expected output
	return "";
}

static const char* test_ajuster()
{

	// Return expected output
	return "";
}

static const char* test_reunir()
{

	// Return expected output
	return "";
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

	if (testName != "" || testName == nullptr)
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

		std::cout << "FAILED : throwed an exception";
		return;
	}

	// Get real test output
	std::string str = buffer.str();
	const char* output = str.data();

	// Restore previous std::cout output buffer
	std::cout.rdbuf(old);

	// See if test output is as expected
	if (string_cmp(output, expected_str) == 0)
		std::cout << "PASSED";
	else
		std::cout << "FAILED : wrong output (\tEXPECTED =\t\"" << expected_str << "\",\n\t\t\tOUTPUT =\t\"" << output << "\")" << std::endl;
}

void main()
{
	std::cout
		<< R"(			 _________ ___    _____  __    __ )" << std::endl
		<< R"(			/_  __/ _ <  /   / ___/_/ /___/ /_)" << std::endl
		<< R"(			 / / / ___/ /   / /__/_  __/_  __/)" << std::endl
		<< R"(			/_/ /_/  /_/    \___/ /_/   /_/   )" << std::endl;

	std::cout << std::endl << "### TESTING COLLECTION CLASS (no dogs will be harmed during this test) ###";

	test(test_lifetime, "OBJECT LIFETIME");
	test(test_afficher, "AFFICHER");
	test(test_ajouter, "AJOUTER");
	test(test_retirer, "RETIRER");
	test(test_ajuster, "AJUSTER");
	test(test_reunir, "REUNIR");

	std::cout << std::endl << std::endl << "Press ENTER to exit...";
	std::cin.get();
}