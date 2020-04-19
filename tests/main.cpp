/**
 * @brief FileFiller main test file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
#include "FileFiller.hpp"
#include "FileFillerTagFactory.hpp"

/* C++ system */
#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <fstream>

/* C system */
#include <cstring>
#include <cassert>

/* Defines --------------------------------------------- */

/* Notes ----------------------------------------------- */

/* Variable declaration -------------------------------- */
static const std::string sReadFileTestExpectedStr1 = R"=====(/*
 * @brief Generated OD Object values
 * 
 * @file OSCOGenOD_Values.c
 */

/* Includes -------------------------------------------- */
/* OSCO OD module */
#include "OSCOOD.h"

/* OSCO public includes */
#include "OSCOTypes.h"

/* Min value declarations -------------------------- */
@@VALUE_ARRAYS@@)=====";

static const std::string sReadFileTestExpectedStr2 = R"=====(/*
 * @brief Generated OD Object Max values
 * 
 * @file OSCOGenOD_MaxValues.c
 */

/* Includes -------------------------------------------- */
/* OSCO OD module */
#include "OSCOOD.h"

/* Generated includes */
#include "OSCOGenNodeID.h"

/* OSCO public includes */
#include "OSCOTypes.h"

/* Max value declarations -------------------------- */
@@VALUE_ARRAYS@@)=====";

/* Type definitions ------------------------------------ */

/* Support functions ----------------------------------- */
static void printUsage(const char * const pProgName) {
    std::cout << "[USAGE] " << pProgName << std::endl;
    std::cout << "        <arg1>  : Test number" << std::endl << std::endl;
    std::cout << "        Test -1 : default/no test" << std::endl;
    std::cout << "        Test 0  : singleTagParsingTest" << std::endl;
    std::cout << "        Test 1  : duplicateTagParsingTest" << std::endl;
    std::cout << "        Test 2  : multipleTagParsingTest" << std::endl;
    std::cout << "        Test 3  : multipleTagParsingTest2" << std::endl;
}

static int readFile(const std::string &pFilePath, std::string &pOut) {
    int lResult = 0;

    /* Try to open the file */
    std::ifstream lIFS(pFilePath.c_str(), std::ios::in);
    if(!lIFS) {
        std::cerr << "[ERROR] <Tests::readFile> Failed to open the input file" << std::endl;
        return -1;
    }
    
    /* Temporary string to hold the contents of the file */
    std::string lContents; /* Not initialized on purpose */

    /* Get lenght of the file */
    lIFS.seekg(0, lIFS.end);

    /* Change the allocated memory size for the content string */
    lContents.resize(lIFS.tellg());

    /* Reset the position of the next character to the beginning of the file */
    lIFS.seekg(0, lIFS.beg);

    /* Read the whole file and set the contents as our input string */
    {
        lIFS.read(&lContents[0U], lContents.size());
        if(!lIFS) {
            std::cerr << "[ERROR] <FileFiller::parseFile> Error occured while reading file contents" << std::endl;

            /* Close the input file */
            lIFS.close();

            return -1;
        }

        /* Set the contents of the file as the input string */
        pOut = lContents;
    }

    /* Close the input file */
    lIFS.close();

    return lResult;
}

/* Factored test operations ---------------------------- */
static int parseInputString(const std::string &pInputStr,
    const std::string &pExpectedStr, 
    const int pExpectedReplacements, 
    const std::map<std::string, std::string> pMap)
{
    /* Create parser */
    FileFiller lParser(pMap, pInputStr);

    /* Parse */
    std::string lOutputStr1 = "";
    std::string lOutputStr2 = "";
    int lReplacements = lParser.parseString(&lOutputStr1);
    assert(pExpectedReplacements == lReplacements);

    std::cerr << "[INFO ] <Tests::parseInputString> Expected string = " << pExpectedStr << std::endl << std::flush;
    std::cerr << "[INFO ] <Tests::parseInputString> Got lOutputStr1 = " << lOutputStr1 << std::endl << std::flush;

    lOutputStr2 = lParser.outputString();
    std::cerr << "[INFO ] <Tests::parseInputString> Got lOutputStr2 = " << lOutputStr2 << std::endl << std::flush;

    assert(lOutputStr2 == lOutputStr1);
    assert(pExpectedStr == lOutputStr2);

    return lReplacements;
}

static int parseInputFile(const std::string &pInputFileStr,
    const std::string &pOutputFileStr,
    const std::string &pExpectedFile, 
    const int pExpectedReplacements, 
    const std::map<std::string, std::string> pMap)
{
    /* Create parser */
    FileFiller lParser(pMap, pInputFileStr, pOutputFileStr);

    /* Parse */
    std::string lOutputStr1 = "";
    std::string lOutputStr2 = "";
    int lReplacements = lParser.parseFile(&lOutputStr1);
    assert(pExpectedReplacements == lReplacements);

    /* Read expected result from file */
    std::string lExpectedStr = "";
    assert(0 == readFile(pExpectedFile, lExpectedStr));

    /* Read output file contents */
    std::string lOutputFileContents = "";
    assert(0 == readFile(pOutputFileStr, lOutputFileContents));

    std::cerr << "[INFO ] <Tests::parseInputString> Expected string         = " << lExpectedStr << std::endl << std::flush;
    std::cerr << "[INFO ] <Tests::parseInputString> Got lOutputStr1         = " << lOutputStr1 << std::endl << std::flush;

    lOutputStr2 = lParser.outputString();
    std::cerr << "[INFO ] <Tests::parseInputString> Got lOutputStr2         = " << lOutputStr2 << std::endl << std::flush;
    std::cerr << "[INFO ] <Tests::parseInputString> Got lOutputFileContents = " << lOutputFileContents << std::endl << std::flush;

    assert(lOutputStr2 == lOutputStr1);
    assert(lExpectedStr == lOutputStr2);

    return lReplacements;
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
        std::cerr << "[ERROR] <Tests::singleTagParsingTest> Failed to insert pair into map" << std::endl << std::flush;
        assert(false);
    }

    /* Test our configuration */
    (void)parseInputString(lInputString, lExpectedOutputString, 1, lMap);

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
        std::cerr << "[ERROR] <Tests::duplicateTagParsingTest> Failed to insert pair into map" << std::endl << std::flush;
        assert(false);
    }

    /* Test our configuration */
    (void)parseInputString(lInputString, lExpectedOutputString, 3, lMap);

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
        std::cerr << "[ERROR] <Tests::multipleTagParsingTest> Failed to insert pair into map" << std::endl << std::flush;
        assert(false);
    }

    /* Test our configuration */
    (void)parseInputString(lInputString, lExpectedOutputString, 3, lMap);

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
        std::cerr << "[ERROR] <Tests::multipleTagParsingTest2> Failed to insert pair into map" << std::endl << std::flush;
        assert(false);
    }

    /* Test our configuration */
    (void)parseInputString(lInputString, lExpectedOutputString, 4, lMap);

    return 0;
}

static int fileMultipleTagParsingTest(const std::string &pInputFilePath,
    const std::string &pExpectedFilePath,
    const std::string &pOutFilePath)
{
    /* Create replacement map */
    std::map<std::string, std::string> lMap;
    try {
        lMap["ACTION1"] = "ski";
        lMap["ACTION2"] = "tennis";
        lMap["ACTION3"] = "foot";
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] <Tests::fileMultipleTagParsingTest> Failed to insert pair into map" << std::endl << std::flush;
        assert(false);
    }

    /* Test our configuration */
    (void)parseInputFile(pInputFilePath, pOutFilePath, pExpectedFilePath, 4, lMap);

    return 0;
}

static int fileMultipleLinesParsingTest(const std::string &pInputFilePath,
    const std::string &pExpectedFilePath,
    const std::string &pOutFilePath)
{
    /* Create replacement map */
    std::map<std::string, std::string> lMap;
    try {
        lMap["ACTION1"] = "ski";
        lMap["ACTION2"] = "tennis";
        lMap["ACTION3"] = "foot";
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] <Tests::fileMultipleLinesParsingTest> Failed to insert pair into map" << std::endl << std::flush;
        assert(false);
    }

    /* Test our configuration */
    (void)parseInputFile(pInputFilePath, pOutFilePath, pExpectedFilePath, 12, lMap);

    return 0;
}

static int buildTagMapParsingTest(void) {
    const std::string lInputStr = R"=====(ACTION1;ski
ACTION2;tennis
ACTION3;foot
)=====";

    /* Build expected tag map */
    std::map<std::string, std::string> lExpectedMap;
    try {
        lExpectedMap["ACTION1"] = "ski";
        lExpectedMap["ACTION2"] = "tennis";
        lExpectedMap["ACTION3"] = "foot";
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] <Tests::buildTagMapParsingTest> Failed build expected map" << std::endl << std::flush;
        assert(false);
    }

    std::map<std::string, std::string> lResultMap;
    int lResult = FileFillerTagFactory::buildTagMap(lInputStr, lResultMap);
    assert(0 == lResult);

    for(const auto &lExpectedElmt : lExpectedMap) {
        try {
            assert(lExpectedElmt.second == lResultMap.at(lExpectedElmt.first));
        } catch (const std::exception &e) {
            std::cerr << "[DEBUG] <Tests::buildTagMapParsingTest> Failed to get tag " << lExpectedElmt.first << " value" << std::endl << std::flush;
            assert(false);
        }
    }

    return 0;
}

static int buildTagMapFileParsingTest(const std::string &pInputFilePath) {
    std::map<std::string, std::string> lResultMap;

    /* Build expected tag map */
    std::map<std::string, std::string> lExpectedMap;
    try {
        lExpectedMap["ACTION1"] = "ski";
        lExpectedMap["ACTION2"] = "tennis";
        lExpectedMap["ACTION3"] = "foot";
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] <Tests::buildTagMapFileParsingTest> Failed build expected map" << std::endl << std::flush;
        assert(false);
    }

    int lResult = FileFillerTagFactory::parseTagMapFile(pInputFilePath, lResultMap);
    assert(0 == lResult);

    for(const auto &lExpectedElmt : lExpectedMap) {
        try {
            assert(lExpectedElmt.second == lResultMap.at(lExpectedElmt.first));
        } catch (const std::exception &e) {
            std::cerr << "[DEBUG] <Tests::buildTagMapFileParsingTest> Failed to get tag " << lExpectedElmt.first << " value" << std::endl << std::flush;
            assert(false);
        }
    }

    return 0;
}

static int tagMapFileParsingAndOutputGenerationTest(const std::string &pInputFilePath,
    const std::string &pExpectedFilePath,
    const std::string &pOutFilePath,
    const std::string &pTagMappingFilePath)
{
    /* Create replacement map */
    std::map<std::string, std::string> lMap;
    int lResult = FileFillerTagFactory::parseTagMapFile(pTagMappingFilePath, lMap);
    assert(0 == lResult);

    /* Test our configuration */
    (void)parseInputFile(pInputFilePath, pOutFilePath, pExpectedFilePath, 12, lMap);

    return 0;
}

static int tagMapFileParsingAndOutputGenerationTest_missingTag(const std::string &pTagMappingFilePath) {
    /* Create replacement map */
    std::map<std::string, std::string> lMap;
    int lResult = FileFillerTagFactory::parseTagMapFile(pTagMappingFilePath, lMap);
    assert(-1 == lResult);

    return 0;
}

int removeLineTest(const std::string &pInputFilePath,
    const std::string &pExpectedFilePath,
    const std::string &pOutFilePath,
    const std::string &pTagMappingFilePath)
{
    /* Create replacement map */
    std::map<std::string, std::string> lMap;
    int lResult = FileFillerTagFactory::parseTagMapFile(pTagMappingFilePath, lMap);
    assert(0 == lResult);

    /* Test our configuration */
    (void)parseInputFile(pInputFilePath, pOutFilePath, pExpectedFilePath, 14, lMap);

    return 0;
}

int readFileTest1(const std::string &pInputFilePath1) {
    FileFiller lParser;

    /* Read the file */
    lParser.readFile(&pInputFilePath1);

    /* Get the file contents */
    std::string lReadStr = lParser.inputString();

    if(sReadFileTestExpectedStr1 != lReadStr) {
        std::cerr << "[ERROR] <readFileTest> sReadFileTestExpectedStr1 != lReadStr" << std::endl << std::flush;
        std::cerr << "[INFO ] <readFileTest> sReadFileTestExpectedStr1 =" << std::endl << std::flush;
        std::cerr << sReadFileTestExpectedStr1 << std::endl << std::flush;
        std::cerr << "[INFO ] <readFileTest> lReadStr =" << std::endl << std::flush;
        std::cerr << lReadStr << std::endl << std::flush;
    }
    assert(sReadFileTestExpectedStr1 == lReadStr);

    return 0;
}

int readFileTest2(const std::string &pInputFilePath2) {
    FileFiller lParser;

    /* Read the file */
    lParser.readFile(&pInputFilePath2);

    /* Get the file contents */
    std::string lReadStr = lParser.inputString();

    if(sReadFileTestExpectedStr1 != lReadStr) {
        std::cerr << "[ERROR] <readFileTest> sReadFileTestExpectedStr2 != lReadStr" << std::endl << std::flush;
        std::cerr << "[INFO ] <readFileTest> sReadFileTestExpectedStr2 =" << std::endl << std::flush;
        std::cerr << sReadFileTestExpectedStr2 << std::endl << std::flush;
        std::cerr << "[INFO ] <readFileTest> lReadStr =" << std::endl << std::flush;
        std::cerr << lReadStr << std::endl << std::flush;
    }
    assert(sReadFileTestExpectedStr2 == lReadStr);

    return 0;
}

int readFileTest3(const std::string &pInputFilePath1, const std::string &pInputFilePath2) {
    readFileTest1(pInputFilePath1);
    readFileTest2(pInputFilePath2);

    return 0;
}

int readFileTest4(const std::string &pInputFilePath, const std::string &pExpectedStr) {
    FileFiller lParser;

    /* Read the file */
    lParser.readFile(&pInputFilePath);

    /* Get the file contents */
    std::string lReadStr = lParser.inputString();

    if(pExpectedStr != lReadStr) {
        std::cerr << "[ERROR] <readFileTest> pExpectedStr != lReadStr" << std::endl << std::flush;
        std::cerr << "[INFO ] <readFileTest> pExpectedStr =" << std::endl << std::flush;
        std::cerr << pExpectedStr << std::endl << std::flush;
        std::cerr << "[INFO ] <readFileTest> lReadStr =" << std::endl << std::flush;
        std::cerr << lReadStr << std::endl << std::flush;
    }
    assert(pExpectedStr == lReadStr);

    /* Read with the UT readFile function */
    std::string lUTReadFileStr = "";
    assert(0 == readFile(pInputFilePath, lUTReadFileStr));
    assert(pExpectedStr == lUTReadFileStr);
    assert(lReadStr == lUTReadFileStr);

    return 0;
}

int UTreadFileTest1(const std::string &pInputFilePath, const std::string &pExpectedStr) {
    /* Read the file */
    std::string lReadOutput = "";
    assert(0 == readFile(pInputFilePath, lReadOutput));
    if(pExpectedStr != lReadOutput) {
        std::cerr << "[ERROR] <readFileTest> pExpectedStr != lReadOutput" << std::endl << std::flush;
        std::cerr << "[INFO ] <readFileTest> pExpectedStr =" << std::endl << std::flush;
        std::cerr << pExpectedStr << std::endl << std::flush;
        std::cerr << "[INFO ] <readFileTest> lReadOutput =" << std::endl << std::flush;
        std::cerr << lReadOutput << std::endl << std::flush;
    }
    assert(pExpectedStr == lReadOutput);

    return 0;
}

int UTreadFileTest2(const std::string &pInputFilePath1,
    const std::string &pInputFilePath2,
    const std::string &pExpectedStr1,
    const std::string &pExpectedStr2)
{
    UTreadFileTest1(pInputFilePath1, pExpectedStr1);
    UTreadFileTest1(pInputFilePath2, pExpectedStr2);

    return 0;
}

/* ----------------------------------------------------- */
/* Main test routine ----------------------------------- */
/* ----------------------------------------------------- */
int main(const int argc, const char * const * const argv) {
    /* Test function initialization */
    int32_t lTestNum;
    int16_t lResult = 0;

    if ((argc < 2) || (std::strcmp(argv[1], "--help") == 0)) {
        printUsage(argv[0]);
        return -1;
    }

    lTestNum = strtol(argv[1], NULL, 10);

    std::cout << "[TEST ] Executing test #" << lTestNum << std::endl;

    /* Executing test */
    switch (lTestNum) {
        case 1:
            lResult = singleTagParsingTest();
            break;
        case 2:
            lResult = duplicateTagParsingTest();
            break;
        case 3:
            lResult = multipleTagParsingTest();
            break;
        case 4:
            lResult = multipleTagParsingTest2();
            break;
        case 5:
            lResult = fileMultipleTagParsingTest(std::string(argv[2U]), std::string(argv[3U]), std::string(argv[4U]));
            break;
        case 6:
            lResult = fileMultipleLinesParsingTest(std::string(argv[2U]), std::string(argv[3U]), std::string(argv[4U]));
            break;
        case 7:
            lResult = buildTagMapParsingTest();
            break;
        case 8:
            lResult = buildTagMapFileParsingTest(std::string(argv[2U]));
            break;
        case 9:
            lResult = tagMapFileParsingAndOutputGenerationTest(std::string(argv[2U]), std::string(argv[3U]), std::string(argv[4U]), std::string(argv[5U]));
            break;
        case 10: /* Missing EoL semi-colon */
            lResult = tagMapFileParsingAndOutputGenerationTest(std::string(argv[2U]), std::string(argv[3U]), std::string(argv[4U]), std::string(argv[5U]));
            break;
        case 11: /* Missing tag */
            lResult = tagMapFileParsingAndOutputGenerationTest_missingTag(std::string(argv[2U]));
            break;
        case 12: /* Missing value w/ semi-colon */
            lResult = tagMapFileParsingAndOutputGenerationTest(std::string(argv[2U]), std::string(argv[3U]), std::string(argv[4U]), std::string(argv[5U]));
            break;
        case 13: /* Missing value w/o semi-colon */
            lResult = tagMapFileParsingAndOutputGenerationTest(std::string(argv[2U]), std::string(argv[3U]), std::string(argv[4U]), std::string(argv[5U]));
            break;
        case 14: /* REMOVE_LINE */
            lResult = removeLineTest(std::string(argv[2U]), std::string(argv[3U]), std::string(argv[4U]), std::string(argv[5U]));
            break;
        case 15: /* REMOVE_LINE EoF NL */
            lResult = removeLineTest(std::string(argv[2U]), std::string(argv[3U]), std::string(argv[4U]), std::string(argv[5U]));
            break;
        case 16:
            lResult = readFileTest1(std::string(argv[2U]));
            break;
        case 17:
            lResult = readFileTest2(std::string(argv[2U]));
            break;
        case 18:
            lResult = readFileTest3(std::string(argv[2U]), std::string(argv[3U]));
            break;
        case 19:
            lResult = readFileTest4(std::string(argv[2U]), sReadFileTestExpectedStr1);
            break;
        case 20:
            lResult = readFileTest4(std::string(argv[2U]), sReadFileTestExpectedStr2);
            break;
        case 21:
            lResult = UTreadFileTest1(std::string(argv[2U]), sReadFileTestExpectedStr1);
            break;
        case 22:
            lResult = UTreadFileTest1(std::string(argv[2U]), sReadFileTestExpectedStr2);
            break;
        case 23:
            lResult = UTreadFileTest2(std::string(argv[2U]), std::string(argv[3U]), sReadFileTestExpectedStr1, sReadFileTestExpectedStr2);
            break;
        default:
            (void)lResult;
            std::cout << "[INFO ] test " << lTestNum << " not available" << std::endl << std::flush;
            break;
    }

    return lResult;
}
