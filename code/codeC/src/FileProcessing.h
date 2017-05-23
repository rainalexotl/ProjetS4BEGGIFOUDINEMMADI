//
//  FileProcessing.h
//  FileProcessing
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.
//

#ifndef FileProcessing_h
#define FileProcessing_h
// si on n'en a pas besoin
//#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <string.h> /* in order to use strcmp */
#include <sys/wait.h>
#include <sys/stat.h> /* in order to use the symbolic constants (access rights) */
#include <fcntl.h> /* in order to use the symbolic constants for the different read modes */
#include <dirent.h> /* to run through a directory */

/*gets the board spots from a file named fileName
(either in the SaveFiles directory if loaded game 
or the config directory if new)*/
char * getSpotsFromFile(const char * fileName);

/*saves the spots of the board into a file along with a
summary of the moves played by each player (into the SaveFiles directory)*/
void saveBoardFile(const char * fileName, const char *spots, int bTabGame[], int wTabGame[]);

/*saves the information of the game players into a file
in the SaveFiles/saveplayers directory*/
void savePlayer(const char * fileNameOfSavePlayer, const char * bPlayer, const char * wPlayer);

/*loads the previously saved information of players from a file
in the saveplayers directory*/
char * loadPlayer(char color, const char * fileNameOfLoadPlayer);

/*returns a list of all the save files in the SaveFiles directory*/
char ** getSaveFiles(const char * dirName, int * nbFiles);

/*deletes all the saved files in the SaveFiles directory*/
void destroySaveFiles(char ** saveFiles);

#endif /* FileProcessing_h */
