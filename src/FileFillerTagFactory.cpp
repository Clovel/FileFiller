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
    for(std::string lLine; std::getline(lISS, lLine); ) {
        std::cout << "[DEBUG] <FileFillerTagFactory::buildTagMap> lLine = " << lLine << std::endl;
        std::string lTag = "", lVal = "";
        bool lTagFound = false, lValFound = false, lIgnoreLine = false;
        size_t lPos = 0U, lOldPos = 0U;

        /* Find first ";" delimiter */
        while((std::string::npos != lPos)) {
            lOldPos = lPos;
            lPos = lLine.find(';', lPos);

            if(std::string::npos == lPos) {
                /* Delimiter not found */
                
                /* Maybe the delimiter was omitted after le tage value */
                if(lTagFound && !lValFound) {
                    lVal = lLine.substr(lOldPos + 1U);
                    lValFound = true;
                } else {
                    lIgnoreLine = true;
                }
                break;
            }

            /* Delimiter found */
            if(!lTagFound) {
                lTag = lLine.substr(0U, lPos);
                lTagFound = true;
                std::cout << "[DEBUG] <FileFillerTagFactory::buildTagMap> Got tag : " << lTag << std::endl;
            } else if (!lValFound) {
                lVal = lLine.substr(lPos + 1U, lOldPos);
                std::cout << "[DEBUG] <FileFillerTagFactory::buildTagMap> Got value : " << lVal << std::endl;
                lValFound = true;
            }
            
            if(lTagFound && lValFound) {
                /* Both were found */
                break;
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
