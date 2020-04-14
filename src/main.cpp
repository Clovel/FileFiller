/**
 * FileFiller utility main source file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
#include "FileFiller.hpp"

/* C++ system */
#include <iostream>
#include <string>

/* Defines --------------------------------------------- */

/* Variable declarations ------------------------------- */

/* Usage function -------------------------------------- */
static void printUsage(const char * const pProgName)
{
    std::cout << "[USAGE] " << pProgName << std::endl;
    std::cout << "        <arg1> - Input file path" << std::endl;
    std::cout << "        <arg2> - Output file path" << std::endl;
}

/* ----------------------------------------------------- */
/* MAIN ------------------------------------------------ */
/* ----------------------------------------------------- */
int main(const int argc, const char * const * const argv) {
    /* Check arguments */
    if ((3 > argc) || (0 == strcmp(argv[1U], "--help"))) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const std::string lInputFilePath(argv[1U]);
    const std::string lOutputFilePath(argv[2U]);

    /* Build a replacement map */

    /* Get the input string from the input file */

    /* Create a file filler */
    FileFiller lParser;

    /* Parse the input and procede to replace the tags */

    /* Get the output string */

    /* Create the output file */

    return EXIT_SUCCESS;
}
