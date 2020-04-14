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
#include <fstream>
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
        FileFiller(const std::map<std::string, std::string> pReplacementValues, const std::string &pInputStr = "");
        FileFiller(const std::map<std::string, std::string> pReplacementValues, const std::string &pInputFilePath, const std::string &pOutputFilePath);

        /* Destructor */
        virtual ~FileFiller();

        /* Getters */
        std::string inputString(void) const;
        std::string outputString(void) const;
        std::string inputFilePath(void) const;
        std::string outputFilePath(void) const;

        std::map<std::string, std::string> replacementValues(void) const;
        bool replacementValue(const std::string &pKey, std::string &pOut) const;

        /* Setters */
        void setInputString(const std::string &pStr);
        void setInputFilePath(const std::string &pStr);
        void setOutputFilePath(const std::string &pStr);
        void setReplacementValues(const std::map<std::string, std::string> &pMap);

        /* Parsers */
        int parseString(std::string * const pOut = nullptr);
        int parseFile(std::string * const pOut = nullptr);
        static int parseString(const std::map<std::string, std::string> pReplacementValues,
            const std::string &pInputStr,
            std::string &pOut);
        static int parseFile(const std::map<std::string, std::string> pReplacementValues,
            const std::string &pInputFilePath,
            const std::string &pOutputFilePath,
            std::string &pOut);

    protected:
    private:
        std::string mInputStr;
        std::string mOutputStr;

        std::map<std::string, std::string> mReplacementValues;

        std::string mInputFilePath;
        std::string mOutputFilePath;
};

#endif /* FILEFILLER_HPP */
