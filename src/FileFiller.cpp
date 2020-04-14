/**
 * FileFiller class implementation
 * 
 * @file FileFiller.cpp
 */

/* Includes -------------------------------------------- */
#include "FileFiller.hpp"

/* C++ system */
#include <exception>

/* Defines --------------------------------------------- */

/* Variable declarations ------------------------------- */

/* Forward declarations -------------------------------- */

/* FileFiller class implementation --------------------- */

/* Constructors */
FileFiller::FileFiller() :
    mInputStr(""),
    mOutputStr(""),
    mInputFilePath(""),
    mOutputFilePath("")
{
    /* Empty.
     * You'll have to use the setters */
}

FileFiller::FileFiller(const std::map<std::string, std::string> pReplacementValues, const std::string &pInputStr) :
    mInputStr(pInputStr),
    mOutputStr(""),
    mReplacementValues(pReplacementValues),
    mInputFilePath(""),
    mOutputFilePath("")
{
    /* Empty */
}

FileFiller::FileFiller(const std::map<std::string, std::string> pReplacementValues, const std::string &pInputFilePath, const std::string &pOutputFilePath) :
    mInputStr(""),
    mOutputStr(""),
    mReplacementValues(pReplacementValues),
    mInputFilePath(pInputFilePath),
    mOutputFilePath(pOutputFilePath)
{
    /* Empty */
}


/* Destructor */
FileFiller::~FileFiller() {
    /* Empty */
}

/* Getters */
std::string FileFiller::inputString(void) const {
    return mInputStr;
}

std::string FileFiller::outputString(void) const {
    return mOutputStr;
}


std::string FileFiller::inputFilePath(void) const {
    return mInputFilePath;
}

std::string FileFiller::outputFilePath(void) const {
    return mOutputFilePath;
}

std::map<std::string, std::string> FileFiller::replacementValues(void) const {
    return mReplacementValues;
}

bool FileFiller::replacementValue(const std::string &pKey, std::string &pOut) const {
    try {
        pOut = mReplacementValues.at(pKey);
        return true;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] <FileFiller::replacementValue> Key \"" << pKey << "\" not found" << std::endl;
        return false;
    }
}

/* Setters */
void FileFiller::setInputString(const std::string &pStr) {
    mInputStr = pStr;
}

void FileFiller::setInputFilePath(const std::string &pStr) {
    mInputFilePath = pStr;
}

void FileFiller::setOutputFilePath(const std::string &pStr) {
    mOutputFilePath = pStr;
}

void FileFiller::setReplacementValues(const std::map<std::string, std::string> &pMap) {
    mReplacementValues = pMap;
}

/* Parsers */
int FileFiller::parseString(std::string * const pOut) {
    int lReplacements = 0;

    /* Create a copy of the input string.
     * The std::string::replace method will change said string.
     */
    std::string lTempInput = mInputStr;

    /* Procede to replace the tags */
    for(const auto &lElmt : mReplacementValues) {
        if("" == lElmt.first) {
            std::cerr << "[WARN ] <FileFiller::parse> Empty tag detected, with replacmeent value set to " << lElmt.second << std::endl;
            continue;
        }

        /* Get tag to replace */
        const std::string lTag = "@@" + lElmt.first + "@@";

        /* Find tag */
        size_t lPos = 0;
        while(std::string::npos != lPos) {
            /* Search for the tag */
            lPos = lTempInput.find(lTag, lPos);

            /* Have we found the tag ? */
            if(std::string::npos == lPos) {
                /* Tag not found */
                break;
            }

            /* Tag found, replace it */
            mOutputStr = lTempInput.replace(lPos, lTag.size(), lElmt.second);
            ++lReplacements;
        }
    }

    /* Set the output string in the output argument */
    if(nullptr != pOut) {
        *pOut = outputString();
    }

    return lReplacements;
}

int FileFiller::parseFile(std::string * const pOut) {
    int lReplacements = 0;

    /* Try to open the file */
    std::ifstream lIFS(mInputFilePath.c_str(), std::ios::in);
    if(!lIFS) {
        std::cerr << "[ERROR] <FileFiller::parseFile> Failed to open the input file : " << mInputFilePath << std::endl;
        return -1;
    }

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
            std::cerr << "[ERROR] <FileFiller::parseFile> Error occured while reading file contents" << std::endl;

            /* Free the allocated memory */
            free(lBuf);

            /* Close the input file */
            lIFS.close();

            return -1;
        }
        mInputStr = std::string(lBuf);

        /* Free the allocated memory */
        free(lBuf);
    }

    /* Close the input file */
    lIFS.close();

    /* Parse the input string */
    lReplacements = parseString(pOut);
    if(0 > lReplacements) {
        std::cerr << "[ERROR] <FileFiller::parseFile> Call to \"parseString\" failed" << std::endl;
    }

    /* Write the output file */
    std::ofstream lOFS(mOutputFilePath.c_str(), std::ios::out | std::ios::trunc);
    if(!lOFS) {
        std::cerr << "[ERROR] <FileFiller::parseFile> Failed to open the output file : " << mOutputFilePath << std::endl;
        return -1;
    }

    /* Write the output string in the output file */
    lOFS << mOutputStr;

    /* Close the output file */
    lOFS.close();

    return lReplacements;
}

int FileFiller::parseString(const std::map<std::string, std::string> pReplacementValues, const std::string &pInputStr, std::string &pOut) {
    /* Create a FileFiller instance */
    FileFiller lParser(pReplacementValues, pInputStr);

    /* Parse the input string */
    int lReplacements = lParser.parseString(&pOut);
    if(0 > lReplacements) {
        std::cerr << "[ERROR] <FileFiller::parseString> Call to \"parseString\" failed" << std::endl;
    }

    return lReplacements;
}

int FileFiller::parseFile(const std::map<std::string, std::string> pReplacementValues, const std::string &pInputFilePath, const std::string &pOutputFilePath, std::string &pOut) {
    /* Create a FileFiller instance */
    FileFiller lParser(pReplacementValues, pInputFilePath, pOutputFilePath);

    /* Parse the input string */
    int lReplacements = lParser.parseFile(&pOut);
    if(0 > lReplacements) {
        std::cerr << "[ERROR] <FileFiller::parseFile> Call to \"parseFile\" failed" << std::endl;
    }

    return lReplacements;
}