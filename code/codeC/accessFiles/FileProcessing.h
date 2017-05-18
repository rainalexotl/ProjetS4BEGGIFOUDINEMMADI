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
#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <string.h> /* utiliser strcmp */
#include <sys/wait.h>
#include <sys/stat.h> /* constantes symboliques pour les droits d’accès */
#include <fcntl.h> /*constantes symboliques pour les différents types d’ouverture */
#include <dirent.h> /*pour le parcours de repertoire */

char * getSpotsFromFile(const char * fileName);
void saveBoardFile(const char * fileName, const char *spots, int bTabGame[], int wTabGame[]);
void savePlayer(const char * fileNameOfSavePlayer, const char * bPlayer, const char * wPlayer);
char * loadPlayer(char color, const char * fileNameOfLoadPlayer);
char ** getSaveFiles(const char * dirName, int * nbFiles);
void destroySaveFiles(char ** saveFiles);

#endif /* FileProcessing_h */
