//
//  FileProcessing.c
//  FileProcessing
//
//  Created by name on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//
//
#include "FileProcessing.h"

#define LONG_MAX_NOM 50
#define LONG_MAX_REP 50
#define OK 0
#define ERR_NB_PARAM 1
#define ERR_ACCES_FICHIER 2
#define ERR_CREATION_FIC 3

char * getSpotsFromFile(const char * fileName){
 	FILE *file = NULL;
    int size = 0;
 	char buff[20];
 	char *tab = malloc(sizeof(char)*(size*size));
 	char charac = 0;
    int ok = 1;
	file = fopen(fileName, "r");
	if (file) {
		int j;
		// i = 0;
        j = 0;
        ok = 1;
		do {
		    fscanf(file,"%s", buff);
            if (strcmp(buff,"\\dim") == 0) {
                fscanf(file,"%s", buff);
                //printf("%s\n", buff);
                size = atoi(buff);
                //printf("%d\n", size);
            }
            if (strcmp(buff,"\\board") == 0 && size != 0) {
                while(j < size*size) {
                    fscanf(file, "%c",&charac);
                    if (charac == '.' || charac == '*' || charac == 'o') {
                        tab[j++] = charac;
                    }
                }
                tab[j] = '\0';
                ok = 0;
            }
        } while (ok);

	}else {
	  fprintf(stderr,"Error : %s not found!",fileName);
      exit(-1);
	}
	fclose(file);
    return tab;
 }


void afficheTab(int tab[]) {
    printf("taille = %d\n", tab[0]);
    for (size_t i = 1; i < tab[0]+1; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void saveBoardFile(const char * fileName, const char *spots, int bTabGame[], int wTabGame[]) {
    FILE *file = NULL;
    if ((file = fopen(fileName, "w")) == NULL) {
        fprintf(stderr, "Error : %s not created!\n", fileName);
        exit(-1);
    }

    //configuration du fichier
    //spots[0] = la dimention du fichier
    // i = a global value in this fonction
    int i = 0;
    char buff[5];
    do {
        buff[i] = spots[i];
        i++;
    } while(spots[i] != '#');
    int dim = atoi(buff);
    printf("dim %d\n", dim);
    i = i+1;
    fprintf(file, "\\Hex\n");
    fprintf(file, "\\dim %d\n", dim);
    //save board
    fprintf(file, "\\board\n");
    for (int j = 0; j < dim*dim; j++) {
        if (j%dim == 0 && j != 0) {
            fprintf(file, "\n");
            fprintf(file, "%c ", spots[i++]);
        }else {
            fprintf(file, "%c ", spots[i++]);
        }
    }

    printf("je passe la boucle \n");
    fprintf(file, "\n\\endboard\n");
    fprintf(file, "\\game\n");

    int quiACommencer = spots[i]-48;
    int bSize = 0;
    int wSize = 0;
    //  afficheTab(bTabGame);
    //  afficheTab(wTabGame);
    //scanf("%s\n", buff);
    int maxSize = (bTabGame[0] > wTabGame[0])? bTabGame[0] : wTabGame[0];
    int k = 0;
    while (k < maxSize) {
        if (quiACommencer) {
            if (bSize != bTabGame[0]) {
                fprintf(file, "\\play * %d %d\n", bTabGame[bSize+1], bTabGame[bSize+2]);
                //printf("taille dest tab de int b = %d w = %d\n", bTabGame[i], wTabGame[i]);
                bSize +=2;
            }
            if (wSize != wTabGame[0]) {
               fprintf(file, "\\play o %d %d\n", wTabGame[wSize+1], wTabGame[wSize+2]);
                //printf("taille dest tab de int b = %d w = %d\n", bTabGame[i], wTabGame[i]);
               wSize +=2;
            }
        }else{
            if (wSize != wTabGame[0]) {
               fprintf(file, "\\play o %d %d\n", wTabGame[wSize+1], wTabGame[wSize+2]);
               wSize +=2;
            }
            if (bSize != bTabGame[0]) {
               fprintf(file, "\\play * %d %d\n", bTabGame[bSize+1], bTabGame[bSize+2]);
               bSize +=2;
            }
        }
        k++;
    }
    fprintf(file, "\\endgame\n");
    fprintf(file, "\\endhex\n");
    fclose(file);
}

void savePlayer(const char * fileNameOfSavePlayer, const char * bPlayer, const char * wPlayer) {
    FILE *file = NULL;
    if ((file = fopen(fileNameOfSavePlayer, "w")) == NULL) {
        fprintf(stderr, "Error : %s not created!\n", fileNameOfSavePlayer);
        exit(-1);
    }
    int bSize = (int)strlen(bPlayer);
    int wSize = (int)strlen(wPlayer);
    fprintf(file, "\\blackPlayer %d\n", bSize);
    fprintf(file, "*%s\n", bPlayer);
    fprintf(file, "\\whitePlayer %d\n", wSize);
    fprintf(file, "o%s\n", wPlayer);
    fclose(file);
}

char * loadPlayer(char color, const char * fileNameOfLoadPlayer) {
    FILE * file = NULL;
    if ((file = fopen(fileNameOfLoadPlayer,"r")) == NULL) {
        fprintf(stderr, "Error : %s not found!\n", fileNameOfLoadPlayer);
        exit(-1);
    }
    int ok = 1;
    char buff[50] = {0};
    char *chaine = NULL;
    int size = 0;
    if (color == '*') {
        do {
            fscanf(file, "%s", buff);
            if (strcmp(buff, "\\blackPlayer") == 0) {
                //printf("buf %s\n", buf);
                fscanf(file, "%s\n", buff);
                size = atoi(buff);
                char bChaine[size+2];
                size_t i = 0;
                for (i = 0; i < size+1; i++) {
                    fscanf(file, "%c", &bChaine[i]);
                }
                bChaine[i] = '\0';
                //we must be free this malloc after use this String
                chaine = malloc(sizeof(char)*(size));
                strcpy(chaine, bChaine);
                ok = 0;
            }
        } while(ok);
    }else {
        do {
            fscanf(file, "%s", buff);
            if (strcmp(buff, "\\whitePlayer") == 0) {
                fscanf(file, "%s\n", buff);
                size = atoi(buff);
                char wChaine[size+2];
                size_t i = 0;
                for (i = 0; i < size+1; i++) {
                    fscanf(file, "%c", &wChaine[i]);
                }
                //we must be free this malloc after use this String
                chaine = malloc(sizeof(char)*size);
                strcpy(chaine, wChaine);
                ok = 0;
            }
        } while(ok);
    }
    return chaine;
}
/*-------------------------------------------------------------------------------------------------*/
//this fonction return the name of save
char ** getSaveFiles(const char * dirName, int * nbFiles) {

    char ** saveFile = malloc(sizeof(char*)*LONG_MAX_REP);  //
    for (size_t j = 0; j < LONG_MAX_REP; j++) {
        saveFile[j] = malloc(sizeof(char)*40);
    }
    char newDirPath[300];
    struct stat infos;
    DIR * srcDir = NULL;
    struct dirent * fileOrDir = NULL;
    if ((srcDir = opendir(dirName)) == NULL) {
        perror("Error opening the directory\n");
        exit(1);
    }else{
        while ((fileOrDir = readdir(srcDir)) != NULL) {
            if ((strcmp (fileOrDir->d_name, ".") != 0) && (strcmp (fileOrDir->d_name, "..") != 0)
                && (strcmp (fileOrDir->d_name, ".DS_Store") != 0)) {
                //creation du chemin du prochain de mon fileOrDir
                strcpy(newDirPath, dirName);
                strcat(newDirPath, "/");
                strcat(newDirPath, fileOrDir->d_name);
                if (stat(newDirPath, &infos) == -1) {
                    perror("Stat error");
                    exit(2);
                }
                //test si l'on travail avec un repertoire ou un fichier
                //le comportement est different l'appel recursif se fait dans le cas ou c'est un dossier
                if (!S_ISDIR(infos.st_mode)) {
                    strcpy(saveFile[(*nbFiles)++], fileOrDir->d_name);
                }
            }
        }
    }
    return saveFile;
}
//We use this foncton to free the saveFile
void destroySaveFiles(char ** saveFiles) {
    for (size_t i = 0; i < LONG_MAX_REP; i++) {
        free (saveFiles[i]);
    }
    free(saveFiles);
}
