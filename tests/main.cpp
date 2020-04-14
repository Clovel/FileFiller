/**
 * @brief FileFiller main test file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
#include "FileFiller.hpp"

/* C++ system */
#include <iostream>
#include <string>
#include <map>
#include <exception>

/* C system */
#include <cstring>

/* Defines --------------------------------------------- */

/* Notes ----------------------------------------------- */

/* Variable declaration -------------------------------- */

/* Type definitions ------------------------------------ */

/* Support functions ----------------------------------- */
static void printUsage(const char * const pProgName)
{
    std::cout << "[USAGE] " << pProgName << std::endl;
    std::cout << "        <arg1>  : Test number" << std::endl << std::endl;
    std::cout << "        Test -1 : default/no test" << std::endl;
    std::cout << "        Test 0  : singleTagParsingTest" << std::endl;
    std::cout << "        Test 1  : duplicateTagParsingTest" << std::endl;
    std::cout << "        Test 2  : multipleTagParsingTest" << std::endl;
    std::cout << "        Test 3  : multipleTagParsingTest2" << std::endl;
}

/* Factored test operations ---------------------------- */
void parseInputString(const std::string &pInputStr,
    const std::string &pExpectedStr, 
    const int pExpectedReplacements, 
    const std::map<std::string, std::string> pMap)
{
    /* Create parser */
    FileFiller lParser(pMap, pInputStr);

    /* Parse */
    std::string lOutputStr1 = "";
    std::string lOutputStr2 = "";
    int lReplacements = lParser.parse(&lOutputStr1);
    assert(pExpectedReplacements == lReplacements);

    std::cerr << "[ERROR] <Tests::parseInputString> Expected string = " << pExpectedStr << std::endl << std::flush;
    std::cerr << "[ERROR] <Tests::parseInputString> Got lOutputStr1 = " << lOutputStr1 << std::endl << std::flush;

    lOutputStr2 = lParser.outputString();
    std::cerr << "[ERROR] <Tests::parseInputString> Got lOutputStr2 = " << lOutputStr2 << std::endl << std::flush;

    assert(lOutputStr2 == lOutputStr1);
    assert(pExpectedStr == lOutputStr2);
}

/* ----------------------------------------------------- */
/* Tests ----------------------------------------------- */
/* ----------------------------------------------------- */
static int singleTagParsingTest(void) {
    /* Create input string */
    const std::string lInputString = "Toto fait du @@ACTION@@ !";

    /* Define expected output */ 
    const std::string lExpectedOutputString = "Toto fait du ski !";

    /* Create replacement map */
    std::map<std::string, std::string> lMap;
    try {
        lMap["ACTION"] = "ski";
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] <stringParsingTest> Failed to insert (" << "ACTION" << ", " << "ski" << ") into map" << std::endl << std::flush;
        assert(false);
    }

    /* Test our configuration */
    parseInputString(lInputString, lExpectedOutputString, 1, lMap);

    return 0;
}

static int duplicateTagParsingTest(void) {
    /* Create input string */
    const std::string lInputString = "Toto fait du @@ACTION@@, du @@ACTION@@, et encore @@ACTION@@ !";

    /* Define expected output */ 
    const std::string lExpectedOutputString = "Toto fait du ski, du ski, et encore ski !";

    /* Create replacement map */
    std::map<std::string, std::string> lMap;
    try {
        lMap["ACTION"] = "ski";
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] <stringParsingTest> Failed to insert (" << "ACTION" << ", " << "ski" << ") into map" << std::endl << std::flush;
        assert(false);
    }

    /* Test our configuration */
    parseInputString(lInputString, lExpectedOutputString, 3, lMap);

    return 0;
}


static int multipleTagParsingTest(void) {
    /* Create input string */
    const std::string lInputString = "Toto fait du @@ACTION1@@, du @@ACTION2@@, et du @@ACTION3@@ !";

    /* Define expected output */ 
    const std::string lExpectedOutputString = "Toto fait du ski, du tennis, et du foot !";

    /* Create replacement map */
    std::map<std::string, std::string> lMap;
    try {
        lMap["ACTION1"] = "ski";
        lMap["ACTION2"] = "tennis";
        lMap["ACTION3"] = "foot";
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] <stringParsingTest> Failed to insert (" << "ACTION" << ", " << "ski" << ") into map" << std::endl << std::flush;
        assert(false);
    }

    /* Test our configuration */
    parseInputString(lInputString, lExpectedOutputString, 3, lMap);

    return 0;
}

static int multipleTagParsingTest2(void) {
    /* Create input string */
    const std::string lInputString = "Toto fait du @@ACTION1@@, du @@ACTION2@@, du @@ACTION3@@, puis encore du @@ACTION1@@ !";

    /* Define expected output */ 
    const std::string lExpectedOutputString = "Toto fait du ski, du tennis, du foot, puis encore du ski !";

    /* Create replacement map */
    std::map<std::string, std::string> lMap;
    try {
        lMap["ACTION1"] = "ski";
        lMap["ACTION2"] = "tennis";
        lMap["ACTION3"] = "foot";
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] <stringParsingTest> Failed to insert (" << "ACTION" << ", " << "ski" << ") into map" << std::endl << std::flush;
        assert(false);
    }

    /* Test our configuration */
    parseInputString(lInputString, lExpectedOutputString, 4, lMap);

    return 0;
}

/* ----------------------------------------------------- */
/* Main test routine ----------------------------------- */
/* ----------------------------------------------------- */
int main(const int argc, const char * const * const argv) {
    /* Test function initialization */
    int32_t lTestNum;
    int16_t lResult = 0;

    if ((argc < 2) || (strcmp(argv[1], "--help") == 0)) {
        printUsage(argv[0]);
        return -1;
    }

    lTestNum = strtol(argv[1], NULL, 10);

    std::cout << "[TEST ] Executing test #" << lTestNum << std::endl;

    /* Executing test */
    switch (lTestNum) {
        case 0:
            lResult = singleTagParsingTest();
            break;
        case 1:
            lResult = duplicateTagParsingTest();
            break;
        case 2:
            lResult = multipleTagParsingTest();
            break;
        case 3:
            lResult = multipleTagParsingTest2();
            break;
        default:
            (void)lResult;
            std::cout << "[INFO ] test " << lTestNum << " not available" << std::endl << std::flush;
            break;
    }

    return lResult;
}
