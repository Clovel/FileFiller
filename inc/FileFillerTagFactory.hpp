/**
 * FileFillerTagFactory class
 * 
 * @file FileFillerTagFactory.hpp
 */

#ifndef FILEFILLERTAGFACTORY_HPP
#define FILEFILLERTAGFACTORY_HPP

/* Includes -------------------------------------------- */
#include "APIExports.h"

/* C++ system */
#include <string>
#include <map>

/* Defines --------------------------------------------- */

/* Variable declarations ------------------------------- */

/* Forward declarations -------------------------------- */

/* FileFillerTagFactory class -------------------------- */
class API_EXPORT FileFillerTagFactory {
    public:
        static int buildTagMap(const std::string &pStr, std::map<std::string, std::string> &pOut);
        static int parseTagMapFile(const std::string &pFilePath, std::map<std::string, std::string> &pOut);
    protected:
    private:
};

#endif /* FILEFILLERTAGFACTORY_HPP */
