/**
 * FileFillerTagFactory class implementation
 * 
 * @file FileFillerTagFactory.cpp
 */

/* Includes -------------------------------------------- */
#include "FileFillerTagFactory.hpp"

/* C++ system */
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

/* Defines --------------------------------------------- */

/* Variable declarations ------------------------------- */

/* Forward declarations -------------------------------- */

/* FileFillerTagFactory class implementation ----------- */

int FileFillerTagFactory::buildTagMap(const std::string &pStr, std::map<std::string, std::string> &pOut) {
    /*
     * The tag format should have the following format :
     * ```csv
     * TAG1;tagValue;
     * TAG2;tag_value;
     * TAG3;tAgVaLuE;
     * etc.
     * ```
     */

    std::map<std::string, std::string> lMap;

    /* Create a stringstream */
    std::istringstream lISS(pStr);

    /* Parse the string */
    unsigned int lLineCount = 0U;
    for(std::string lLine; std::getline(lISS, lLine); lLineCount++) {
        std::cout << "[DEBUG] <FileFillerTagFactory::buildTagMap> lLine = " << lLine << std::endl;
        std::string lTag = "", lVal = "";
        bool lTagFound = false, lValFound = false, lIgnoreLine = false;
        size_t lPos = 0U;

        /* Find first ";" delimiter */
        while((std::string::npos != lPos) && !(lTagFound && lValFound)) {
            lPos = lLine.find(';');

            if(std::string::npos == lPos) {
                /* Delimiter not found */
                
                /* If the tag wasn't found yet, this line doesn't have a ";" delimiter
                 * Ignoring this line for now
                 */
                if(!lTagFound) {
                    lIgnoreLine = true;
                    break;
                }
            }

            /* Delimiter found */
            if(!lTagFound) {
                lTag = lLine.substr(0U, lPos);

                /* Check if tag is empty */
                if(lTag.empty()) {
                    std::cerr << "[ERROR] <FileFillerTagFactory::buildTagMap> Tag is empty at line " << lLineCount << std::endl;
                    return -1;
                }

                lLine = lLine.substr(lPos + 1U);
                lTagFound = true;
                std::cout << "[DEBUG] <FileFillerTagFactory::buildTagMap> Got tag : " << lTag << std::endl;
                continue;
            }

            /* Tag was found previously */
            if (!lValFound) {
                lVal = lLine.substr(0U, lPos);

                /* Check if value is empty */
                if(lTag.empty()) {
                    std::cerr << "[WARN ] <FileFillerTagFactory::buildTagMap> Value is empty at line " << lLineCount << std::endl;
                }

                lValFound = true;
                std::cout << "[DEBUG] <FileFillerTagFactory::buildTagMap> Got value : " << lVal << std::endl;
                continue;
            }
        }

        if(lIgnoreLine) {
            std::cerr << "[WARN ] <FileFillerTagFactory::buildTagMap> No delimiter, ingore line (" << lLine << ")" << std::endl;
            break;
        }

        /* Check if we found everything we needed */
        if(lTagFound && lValFound) {
            try {
                lMap[lTag] = lVal;
            } catch (const std::exception &e) {
                std::cerr << "[ERROR] <FileFillerTagFactory::buildTagMap> Failed to insert pair into map" << std::endl;
            }
        } else {
            std::cerr << "[ERROR] <FileFillerTagFactory::buildTagMap> Parsed line, but Tag/Value pair not found" << std::endl;
            return -1;
        }
    }

    /* Set output map */
    pOut = lMap;

    return 0;

}

int FileFillerTagFactory::parseTagMapFile(const std::string &pFilePath, std::map<std::string, std::string> &pOut) {
    /* Try to open the file */
    std::ifstream lIFS(pFilePath.c_str(), std::ios::in);
    if(!lIFS) {
        std::cerr << "[ERROR] <FileFillerTagFactory::parseTagMapFile> Failed to open the input file : " << pFilePath << std::endl;
        return -1;
    }

    std::string lInputStr = "";

    /* Get lenght of the file */
    lIFS.seekg(0, lIFS.end);
    const int lFileLength = lIFS.tellg();

    /* Reset the position of the next character to the beginning of the file */
    lIFS.seekg(0, lIFS.beg);

    /* Read the whole file and set the contents as our input string */
    {
        char *lBuf = (char *)malloc(lFileLength);
        lIFS.read(lBuf, lFileLength);
        if(!lIFS) {
            std::cerr << "[ERROR] <FileFillerTagFactory::parseTagMapFile> Error occured while reading file contents" << std::endl;

            /* Free the allocated memory */
            free(lBuf);

            /* Close the input file */
            lIFS.close();

            return -1;
        }
        lInputStr = std::string(lBuf);

        /* Free the allocated memory */
        free(lBuf);
    }

    /* Close the input file */
    lIFS.close();

    /* build the tag map */
    if(0 > buildTagMap(lInputStr, pOut)) {
        std::cerr << "[ERROR] <FileFillerTagFactory::parseTagMapFile> Call to \"buildTagMap\" failed" << std::endl;
        return -1;
    }

    return 0;
}
