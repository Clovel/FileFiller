/**
 * C example for the usage of the C Wrapper of the FileFiller library
 * 
 * @file main.c
 */

/* Includes -------------------------------------------- */
#include "C_FileFiller.h"

/* C system */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Defines --------------------------------------------- */

/* Variable declarations ------------------------------- */

/* Usage function -------------------------------------- */
static void printUsage(const char * const pProgName)
{
    printf("[USAGE] %s usage\n", pProgName);
    printf("        <arg1> - Input file path\n");
    printf("        <arg2> - Output file path\n");
    printf("        <arg3> - Tag mapping file path\n");
}

/* Main routine ---------------------------------------- */
int main(const int argc, const char * const * const argv) {
    /* Check arguments */
    if ((4 > argc) || (0 == strcmp(argv[1U], "--help"))) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const char *lInputFilePath = argv[1U];
    const char *lOutputFilePath = argv[2U];
    const char *lTagFilePath = argv[3U];

    char lOutputBuffer[4096U];
    memset(lOutputBuffer, 0, 4096U);

    int lResult = FileFiller_parseFile(lTagFilePath, lInputFilePath, lOutputFilePath, (char ** const)&lOutputBuffer);
    if(0 > lResult) {
        fprintf(stderr, "[ERROR] FileFiller_parseFile failed\n");
        return EXIT_FAILURE;
    } else {
        printf("[INFO ] FileFiller_parseFile replaced %d tags\n", lResult);
        printf("[INFO ] FileFiller_parseFile Got string :\n%s\n", lOutputBuffer);
    }

    return EXIT_SUCCESS;
}
