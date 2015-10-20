/*********************************************************************************
					tests.h  -  Unary tests for TP1::collection class
					-------------------------------------------------
date                 : 10/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

#ifndef TESTS_H
#define TESTS_H

//------------------------------------------------------------------------ INCLUDE
//---------------------------------------------------------------- Include système
#include <iostream>
#include <sstream> // utilisé uniquement std::cout pour rediriger la sortie de std::cout

//----------------------------------------------------------- Interfaces utilisées
#include "collection.h"

//------------------------------------------------------------------------- USINGS
// Using définissant le prototype d'une fonction de test
using TestFuncPtr = const char*(*)();

//---------------------------------------------------------------------- FONCTIONS

// Forward déclaration de la fonction statique d'aide 'string_cmp'
static int string_cmp(const char* lhs, const char* rhs);

// Mode d'emploi: Excecute une fonction de test donnée en paramètre
//		testFunc: pointeur vers une fonction de test
//		testName: nom optionel du test
void test(TestFuncPtr testFunc, const char* testName = "")
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

//-------------------------------------------------------------------------- TESTS

// Empêche l'optimization du compilateur pour ce test, si possible
#ifdef __GNUC__
#pragma GCC push_options
#pragma GCC optimize ("O0")
#elif _MSC_VER
#pragma optimize("", off)
#endif

// Mode d'emploi: test des constructeurs et du destructeur de la classe TP1::collection
//		RETOURNE: la chaine de charactère qui devrait être affichée si la méthode testée 
//			est correcte
//		NOTE: L'optimization de ce test est désactivée car on ne veut pas que les objets
//			de type 'TP1::collection' soit enlevés car non utilisés.
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

// Mode d'emploi: test de la méthode afficher de la classe TP1::collection
//		RETOURNE: la chaine de charactère qui devrait être affichée si la méthode testée
//			est correcte
const char* test_afficher()
{
	TP1::dog dogsArray[3] = {
		TP1::dog(TP1::color::GREEN, 50),
		TP1::dog(TP1::color::RED, 3),
		TP1::dog(TP1::color::BLUE, 99) };

	{ // Sub-test 1
		TP1::collection dogs(dogsArray, 3);
		dogs.afficher();
	}

	std::cout << " ";

	{ // Sub-test 2
		TP1::collection dogs(2);
		dogs.afficher();
	}

	// Return expected output
	return
		"({ 50, 3, 99 }, 3) "	// Sub-test 1
		"({ }, 2)";				// Sub-test 2
}

// Mode d'emploi: test de la méthode ajouter de la classe TP1::collection
//		RETOURNE: la chaine de charactère qui devrait être affichée si la méthode testée
//			est correcte
const char* test_ajouter()
{
	{ // Sub-test 1
		TP1::dog dogsArray[3] = {
			TP1::dog(TP1::color::GREEN, 50),
			TP1::dog(TP1::color::RED, 3),
			TP1::dog(TP1::color::BLUE, 99) };

		TP1::collection dogs(dogsArray, 3);
		dogs.ajouter(TP1::dog(TP1::color::GREEN, 5));
		dogs.afficher();
	}

	std::cout << " ";

	{ // Sub-test 2
		TP1::collection dogs(0);
		dogs.ajouter(TP1::dog(TP1::color::GREEN, 5));
		dogs.afficher();
	}

	// Return expected output
	return
		"({ 50, 3, 99, 5 }, 6) "	// Sub-test 1
		"({ 5 }, 5)";				// Sub-test 2
}

// Mode d'emploi: test de la méthode retirer de la classe TP1::collection
//		RETOURNE: la chaine de charactère qui devrait être affichée si la méthode testée
//			est correcte
const char* test_retirer()
{
	TP1::dog dogsArray[3] = {
		TP1::dog(TP1::color::GREEN, 50),
		TP1::dog(TP1::color::RED, 3),
		TP1::dog(TP1::color::BLUE, 99) };

	{ // Sub-test 1
		TP1::collection dogs(dogsArray, 3);
		std::cout << dogs.retirer(nullptr, 0) << " ";
		dogs.afficher();
	}

	std::cout << " ";

	{ // Sub-test 2
		TP1::collection dogs(dogsArray, 3);
		std::cout << dogs.retirer(dogsArray, 3) << " ";
		dogs.afficher();
	}

	std::cout << " ";

	{ // Sub-test 3
		TP1::collection dogs(dogsArray, 3);
		dogs.ajouter(TP1::dog(TP1::color::RED, 3));
		std::cout << dogs.retirer(dogsArray[1]) << " ";
		dogs.afficher();
	}

	std::cout << " ";

	{ // Sub-test 4
		TP1::collection dogs(0);
		dogs.ajouter(TP1::dog(TP1::color::GREEN, 5));
		std::cout << dogs.retirer(dogsArray, 3) << " ";
		dogs.afficher();
	}

	// Return expected output
	return
		"0 ({ 50, 3, 99 }, 3) "	// Sub-test 1
		"1 ({ }, 0) "			// Sub-test 2
		"1 ({ 50, 99 }, 2) "	// Sub-test 3
		"0 ({ 5 }, 1)";			// Sub-test 4
}

// Mode d'emploi: test de la méthode ajuster de la classe TP1::collection
//		RETOURNE: la chaine de charactère qui devrait être affichée si la méthode testée
//			est correcte
const char* test_ajuster()
{
	TP1::dog dogsArray[3] = {
		TP1::dog(TP1::color::GREEN, 50),
		TP1::dog(TP1::color::RED, 3),
		TP1::dog(TP1::color::BLUE, 99) };

	{ // Sub-test 1
		TP1::collection dogs(dogsArray, 3);
		std::cout << dogs.ajuster(2) << " ";
		dogs.afficher();
	}

	std::cout << " ";

	{ // Sub-test 2
		TP1::collection dogs(5);
		std::cout << dogs.ajuster(0) << " ";
		dogs.afficher();
	}

	std::cout << " ";

	{ // Sub-test 3
		TP1::collection dogs(dogsArray, 3);
		std::cout << dogs.ajuster(10) << " ";
		dogs.afficher();
	}

	std::cout << " ";

	{ // Sub-test 4
		TP1::collection dogs(dogsArray, 3);
		dogs.ajuster(10);
		std::cout << dogs.ajuster(4) << " ";
		dogs.afficher();
	}

	// Return expected output
	return
		"0 ({ 50, 3, 99 }, 3) "		// Sub-test 1
		"1 ({ }, 0) "				// Sub-test 2
		"1 ({ 50, 3, 99 }, 10) "		// Sub-test 3
		"1 ({ 50, 3, 99 }, 4)";	// Sub-test 4
}

// Mode d'emploi: test de la méthode reunir de la classe TP1::collection
//		RETOURNE: la chaine de charactère qui devrait être affichée si la méthode testée
//			est correcte
const char* test_reunir()
{
	TP1::dog dogsArray[3] = {
		TP1::dog(TP1::color::GREEN, 50),
		TP1::dog(TP1::color::RED, 3),
		TP1::dog(TP1::color::BLUE, 99) };

	{ // Sub-test 1
		TP1::dog dogsArray2[2] = {
			TP1::dog(TP1::color::RED, 4),
			TP1::dog(TP1::color::YELLOW, 1) };

		TP1::collection dogs1(dogsArray, 3);
		TP1::collection dogs2(dogsArray2, 2);
		std::cout << dogs1.reunir(dogs2) << " ";
		dogs1.afficher();
	}

	std::cout << " ";

	{ // Sub-test 2
		TP1::collection dogs1(dogsArray, 3);
		TP1::collection dogs2(2);
		std::cout << dogs1.reunir(dogs2) << " ";
		dogs1.afficher();
	}

	std::cout << " ";

	{ // Sub-test 3
		TP1::collection dogs1(10);
		TP1::collection dogs2(dogsArray, 3);
		std::cout << dogs1.reunir(dogs2) << " ";
		dogs1.afficher();
	}

	// Return expected output
	// NOTE: Capacity of dogs1 after a 'dogs1.reunir(dogs2)' call must be 2 * (dogs1.m_size + dogs2.m_size)
	//	except if 'dogs1' have enought capacity to store 'dogs2' dogs (occurs in sub-test 2 and 3)
	return
		"1 ({ 50, 3, 99, 4, 1 }, 10) "	// Sub-test 1
		"0 ({ 50, 3, 99 }, 3) "			// Sub-test 2
		"1 ({ 50, 3, 99 }, 10)";		// Sub-test 3
}

//------------------------------------------------------------------------ STATIC

// Mode d'emploi: Fonction permettant de comparer deux chaines de charactères
//		lhs: première chaîne de charactère comparée
//		rhs: deuxième chaîne de charactère comparée
//		RETOURNE: un entier nul si les chaines sont égales, négatif si le premier 
//			charactère différent a une valeur inferieure dans lhs et un entier 
//			positif sinon.
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

#endif // TESTS_H
