/**
 * FileFiller class C wrapper implementation
 * 
 * @file C_FileFiller.cpp
 */

/* Includes -------------------------------------------- */
#include "C_FileFiller.h"
#include "FileFillerTagFactory.hpp"
#include "FileFiller.hpp"

/* C++ system */
#include <iostream>

/* C system */
#include <cstring>

/* Defines --------------------------------------------- */

/* Variable declarations ------------------------------- */

/* FileFiller class wrapper ---------------------------- */

/* C-style wrapper ------------------------------------- */

extern "C" {
    int FileFiller_parseString(const char * const pMapping, const char * const pInputString, char ** const pOutputString) {
        std::map<std::string, std::string> lMap;
        if(0 > FileFillerTagFactory::buildTagMap(std::string(pMapping), lMap)) {
            std::cerr << "[ERROR] <FileFiller_parseString> buildTagMap failed" << std::endl;
            return -1;
        }

        std::string lOutput     = "";
        int         lReplaced   = 0;

        if(0 > (lReplaced = FileFiller::parseString(lMap, std::string(pInputString), lOutput))) {
            std::cerr << "[ERROR] <FileFiller_parseString> parseString failed" << std::endl;
            return lReplaced;
        }

        (void)std::memcpy(*pOutputString, lOutput.c_str(), lOutput.size());

        return lReplaced;
    }

    int FileFiller_parseFile(const char * const pMappingFilePath, const char * const pInputFilePath, const char * const pOutputFilePath, char ** const pOutputString) {
        std::map<std::string, std::string> lMap;
        if(0 > FileFillerTagFactory::parseTagMapFile(std::string(pMappingFilePath), lMap)) {
            std::cerr << "[ERROR] <FileFiller_parseFile> parseTagMapFile failed" << std::endl;
            return -1;
        }

        std::string lOutput     = "";
        int         lReplaced   = 0;

        if(0 > (lReplaced = FileFiller::parseFile(lMap, std::string(pInputFilePath), std::string(pOutputFilePath), lOutput))) {
            std::cerr << "[ERROR] <FileFiller_parseFile> parseFile failed" << std::endl;
            return lReplaced;
        }

        (void)std::memcpy(pOutputString, lOutput.c_str(), lOutput.size());

        return lReplaced;
    }
}
