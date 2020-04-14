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
    mOutputStr("")
{
    /* Empty.
     * You'll have to use the setters */
}

FileFiller::FileFiller(const std::map<std::string, std::string> pReplacementValues) :
    mInputStr(""),
    mOutputStr(""),
    mReplacementValues(pReplacementValues)
{
    /* Empty */
}
FileFiller::FileFiller(const std::map<std::string, std::string> pReplacementValues, const std::string &pInputStr) :
    mInputStr(pInputStr),
    mOutputStr(""),
    mReplacementValues(pReplacementValues)
{
    /* Empty */
}
/* TODO : Constructor w/ file argument */

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

void FileFiller::setReplacementValues(const std::map<std::string, std::string> &pMap) {
    mReplacementValues = pMap;
}

/* Parsers */
int FileFiller::parse(std::string * const pOut) {
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

int FileFiller::parseString(const std::map<std::string, std::string> pReplacementValues, const std::string &pInputStr, std::string &pOut) {
    /* Create a FileFiller instance */
    FileFiller lParser(pReplacementValues, pInputStr);

    /* Parse the input string */
    int lReplacements = lParser.parse(&pOut);
    if(0 > lReplacements) {
        std::cerr << "[ERROR] <FileFiller::parseString> Call to \"parse\" failed" << std::endl;
    }

    return lReplacements;
}
