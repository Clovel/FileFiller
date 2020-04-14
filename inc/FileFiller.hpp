/**
 * FileFiller class
 * 
 * @file FileFiller.hpp
 */

#ifndef FILEFILLER_HPP
#define FILEFILLER_HPP

/* Includes -------------------------------------------- */
#include "APIExports.h"

/* C++ system */
#include <iostream>
#include <string>
#include <map>

/* Defines --------------------------------------------- */

/* Variable declarations ------------------------------- */

/* Forward declarations -------------------------------- */

/* FileFiller class ------------------------------------ */
class API_EXPORT FileFiller {
    public:
        /* Constructors */
        FileFiller();
        FileFiller(const std::map<std::string, std::string> pReplacementValues);
        FileFiller(const std::map<std::string, std::string> pReplacementValues, const std::string &pInputStr);
        /* TODO : Constructor w/ file argument */

        /* Destructor */
        virtual ~FileFiller();

        /* Getters */
        std::string inputString(void) const;
        std::string outputString(void) const;

        std::map<std::string, std::string> replacementValues(void) const;
        bool replacementValue(const std::string &pKey, std::string &pOut) const;

        /* Setters */
        void setInputString(const std::string &pStr);
        void setReplacementValues(const std::map<std::string, std::string> &pMap);

        /* Parsers */
        int parse(std::string * const pOut = nullptr);
        static int parseString(const std::map<std::string, std::string> pReplacementValues, const std::string &pStr, std::string &pOut);
    protected:
    private:
        std::string mInputStr;
        std::string mOutputStr;

        std::map<std::string, std::string> mReplacementValues;
};

#endif /* FILEFILLER_HPP */
