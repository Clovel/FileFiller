/**
 * FileFiller class C wrapper
 * 
 * @file C_FileFiller.h
 */

#ifndef C_FILEFILLER_H
#define C_FILEFILLER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes -------------------------------------------- */

/* Defines --------------------------------------------- */

/* Variable declarations ------------------------------- */

/* FileFiller class wrapper ---------------------------- */
/**
 * @brief Parses an input string, replaces tags and outputs a string.
 * 
 * @warning The output string argument's memory must be allocated
 * before calling this function.
 * 
 * @param[in]   pMapping        Tag mapping string
 * @param[in]   pInputString    Input string.
 * @param[out]  pOutputString   Output string. Memory must be allocated beforehand.
 * 
 * @return Number of replaced tags. Negative if failed.
 */
int FileFiller_parseString(const char * const pMapping, const char * const pInputString, char ** const pOutputString);


/**
 * @brief Parses an input file, replaces tags and outputs a file.
 * 
 * @warning The output string argument's memory must be allocated
 * before calling this function.
 * 
 * @param[in]   pMappingFilePath    Tag mapping file.
 * @param[in]   pInputFilePath      Input file path.
 * @param[in]   pOutputFilePath     Output file path.
 * @param[out]  pOutputString   Output string. Memory must be allocated beforehand.
 * 
 * @return Number of replaced tags. Negative if failed.
 */
int FileFiller_parseFile(const char * const pMappingFilePath, const char * const pInputFilePath, const char * const pOutputFilePath, char ** const pOutputString);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* C_FILEFILLER_H */
