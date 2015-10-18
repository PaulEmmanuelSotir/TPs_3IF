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
	{
		dog * dogsArray[3] = { new dog(color::GREEN, 50),
			new dog(color::RED, 3),
			new dog(color::BLUE, 99) };

		collection dogs1(3);
		collection dogs2(dogsArray, 3);
	} // 'dogs1' and 'dogs2' destructors will be called here

	volatile collection* dogs = new collection(100);
	delete dogs;

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
	std::cout << " ";
	dogs2.afficher();

	// Return expected output
	return "{ 50, 3, 99 } { }";
}

static const char* test_ajouter()
{
	dog * dogsArray[3] = { new dog(color::GREEN, 50),
		new dog(color::RED, 3),
		new dog(color::BLUE, 99) };

	{
		collection dogs(dogsArray, 3);
		dogs.ajouter(new dog(color::GREEN, 5));
		dogs.afficher();
	}

	std::cout << " ";

	{
		collection dogs(0);
		dogs.ajouter(new dog(color::GREEN, 5));
		dogs.afficher();
	}

	std::cout << " ";

	{
		collection dogs(2);
		dogs.ajouter(new dog(color::GREEN, 5));
		dogs.ajouter(nullptr);
		dogs.afficher();
	}

	// Return expected output
	return "{ 50, 3, 99, 5 } { 5 } { 5 }";
}

static const char* test_retirer()
{
	// We need different allocation for each test as collection takes ownership over dogs and could delete them during 'retirer(...)' calls
	auto create_dogs = []() {
		auto dogsArray = new dog*[3];
		dogsArray[0] = new dog(color::GREEN, 50);
		dogsArray[1] = new dog(color::RED, 3);
		dogsArray[2] = new dog(color::BLUE, 99);
		return dogsArray;
	};

	{
		dog** dogsArray = create_dogs();

		collection dogs(dogsArray, 3);
		dogs.retirer(nullptr, 0);
		dogs.afficher();
	}

	std::cout << " ";

	{
		dog** dogsArray = create_dogs();

		collection dogs(dogsArray, 3);
		dogs.retirer(dogsArray, 3);
		dogs.afficher();
	}

	std::cout << " ";

	{
		dog** dogsArray = create_dogs();

		collection dogs(dogsArray, 3);
		dogs.ajouter(new dog(color::RED, 3));
		dogs.retirer(*dogsArray[1]);
		dogs.afficher();
	}

	std::cout << " ";

	{
		dog** dogsArray = create_dogs();

		collection dogs(0);
		dogs.ajouter(new dog(color::GREEN, 5));
		dogs.retirer(dogsArray, 3);
		dogs.afficher();
	}

	// Return expected output
	return "{ 50, 3, 99 } { } { 50, 99 } { 5 }";
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
}
