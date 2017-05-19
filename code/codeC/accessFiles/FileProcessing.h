//
//  FileProcessing.h
//  FileProcessing
//
//  Created by name on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//
//

#ifndef FileProcessing_h
#define FileProcessing_h
// si on n'en a pas besoin
// #define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <string.h> /* in order to use strcmp */
#include <sys/wait.h>
#include <sys/stat.h> /* in order to use the symbolic constants (access rights) */
#include <fcntl.h> /*in order to use the symbolic constants for the different read modes */
#include <dirent.h> /* to run through a directory */

char * getSpotsFromFile(const char * fileName);
void saveBoardFile(const char * fileName, const char *spots, int bTabGame[], int wTabGame[]);
void savePlayer(const char * fileNameOfSavePlayer, const char * bPlayer, const char * wPlayer);
char * loadPlayer(char color, const char * fileNameOfLoadPlayer);
char ** getSaveFiles(const char * dirName, int * nbFiles);
void destroySaveFiles(char ** saveFiles);

#endif /* FileProcessing_h */
