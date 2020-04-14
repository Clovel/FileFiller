/**
 * FileFiller utility main source file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
#include "FileFiller.hpp"
#include "FileFillerTagFactory.hpp"

/* C++ system */
#include <iostream>
#include <string>

/* C system */
#include <cstring>
#include <cassert>

/* Defines --------------------------------------------- */

/* Variable declarations ------------------------------- */

/* Usage function -------------------------------------- */
static void printUsage(const char * const pProgName)
{
    std::cout << "[USAGE] " << pProgName << std::endl;
    std::cout << "        <arg1> - Input file path" << std::endl;
    std::cout << "        <arg2> - Output file path" << std::endl;
    std::cout << "        <arg3> - Tag mapping file path" << std::endl;
}

/* ----------------------------------------------------- */
/* MAIN ------------------------------------------------ */
/* ----------------------------------------------------- */
int main(const int argc, const char * const * const argv) {
    /* Check arguments */
    if ((4 > argc) || (0 == std::strcmp(argv[1U], "--help"))) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const std::string lInputFilePath(argv[1U]);
    const std::string lOutputFilePath(argv[2U]);
    const std::string lTagFilePath(argv[3U]);

    /* Build a replacement map */
    std::map<std::string, std::string> lMap;
    int lResult = FileFillerTagFactory::parseTagMapFile(lTagFilePath, lMap);
    if(0 > lResult) {
        std::cerr << "[ERROR] Failed to parse tag mapping file" << std::endl;
        exit(EXIT_FAILURE);
    }

    /* Parse the input and procede to replace the tags */
    std::string lOutput = "";

    /* Create a file filler */
    FileFiller::parseFile(lMap, lInputFilePath, lOutputFilePath, lOutput);

    /* TODO : If verbose, print output */

    return EXIT_SUCCESS;
}
