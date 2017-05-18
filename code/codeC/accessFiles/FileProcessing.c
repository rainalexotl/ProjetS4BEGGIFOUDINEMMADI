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

char * transformGraphToBoardOfChar(const char * fileName){
 	FILE *file = NULL;
    int size = 0;
 	char buff[20];
 	char *tab = malloc(sizeof(char)*(size*size));
 	char car = 0;
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
                    fscanf(file, "%c",&car);
                    if (car == '.' || car == '*' || car == 'o') {
                        tab[j++] = car;
                    }
                }
                tab[j] = '\0';
                ok = 0;
            }
        } while (ok);

	}else {
	  fprintf(stderr,"error : %s not found !",fileName);
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

 void saveBoardFile(const char * fileName, const char *spots, int BTabGame[], int WTabGame[]) {
     FILE *file = NULL;
     if ((file = fopen(fileName, "w")) == NULL) {
         fprintf(stderr, "error : %s not create\n", fileName);
         exit(-1);
     }

     //configuration du fichier
     //spots[0] = la dimention du fichier
     // i = a global value in this fonction
     int i = 0;
     char buf[5];
     do {
         buf[i] = spots[i];
         i++;
     } while(spots[i] != '#');
     int dim = atoi(buf);
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
     int Bsize = 0;
     int Wsize = 0;
    //  afficheTab(BTabGame);
    //  afficheTab(WTabGame);
     //scanf("%s\n", buf);
     int maxSize = (BTabGame[0] > WTabGame[0])? BTabGame[0] : WTabGame[0];
     int k = 0;
     while (k < maxSize) {
         if (quiACommencer) {
             if (Bsize != BTabGame[0]) {
                 fprintf(file, "\\play * %d %d\n", BTabGame[Bsize+1], BTabGame[Bsize+2]);
                 //printf("taille dest tab de int b = %d w = %d\n", BTabGame[i], WTabGame[i]);
                 Bsize +=2;
             }
             if (Wsize != WTabGame[0]) {
                fprintf(file, "\\play o %d %d\n", WTabGame[Wsize+1], WTabGame[Wsize+2]);
                //printf("taille dest tab de int b = %d w = %d\n", BTabGame[i], WTabGame[i]);
                Wsize +=2;
             }
         }else{
             printf("j'enntre dans le else \n");
             if (Wsize != WTabGame[0]) {
                fprintf(file, "\\play o %d %d\n", WTabGame[Wsize+1], WTabGame[Wsize+2]);
                Wsize +=2;
             }
             if (Bsize != BTabGame[0]) {
                fprintf(file, "\\play * %d %d\n", BTabGame[Bsize+1], BTabGame[Bsize+2]);
                Bsize +=2;
             }
         }
         k++;
     }
     fprintf(file, "\\endgame\n");
     fprintf(file, "\\endhex\n");
     fclose(file);
 }

 void savePlayer(const char * fileNameOfSavePlayer, const char * Bplayer, const char * Wplayer) {
    FILE *file = NULL;
    if ((file = fopen(fileNameOfSavePlayer, "w")) == NULL) {
        fprintf(stderr, "error : %s not create !\n", fileNameOfSavePlayer);
        exit(-1);
    }
    int Bsize = (int)strlen(Bplayer);
    int Wsize = (int)strlen(Wplayer);
    fprintf(file, "\\blackPlayer %d\n", Bsize);
    fprintf(file, "*%s\n", Bplayer);
    fprintf(file, "\\whitePlayer %d\n", Wsize);
    fprintf(file, "o%s\n", Wplayer);
    fclose(file);
}

char * loarPlayer(char color, const char* stringFromFilInC) {
    FILE * file = NULL;
    if ((file = fopen(stringFromFilInC,"r")) == NULL) {
        fprintf(stderr, "error : %s not found !\n", stringFromFilInC);
        exit(-1);
    }
    int ok = 1;
    char buf[50] = {0};
    char *chaine = NULL;
    int size = 0;
    if (color == '*') {
        do {
            fscanf(file, "%s", buf);
            if (strcmp(buf, "\\blackPlayer") == 0) {
                //printf("buf %s\n", buf);
                fscanf(file, "%s\n", buf);
                size = atoi(buf);
                char Bchaine[size+2];
                size_t i = 0;
                for (i = 0; i < size+1; i++) {
                    fscanf(file, "%c", &Bchaine[i]);
                }
                Bchaine[i] = '\0';
                //we must be free this malloc after use this String
                chaine = malloc(sizeof(char)*(size));
                strcpy(chaine, Bchaine);
                ok = 0;
            }
        } while(ok);
    }else {
        do {
            fscanf(file, "%s", buf);
            if (strcmp(buf, "\\whitePlayer") == 0) {
                fscanf(file, "%s\n", buf);
                size = atoi(buf);
                char Wchaine[size+2];
                size_t i = 0;
                for (i = 0; i < size+1; i++) {
                    fscanf(file, "%c", &Wchaine[i]);
                }
                //we must be free this malloc after use this String
                chaine = malloc(sizeof(char)*size);
                strcpy(chaine, Wchaine);
                ok = 0;
            }
        } while(ok);
    }
    return chaine;
}
/*-------------------------------------------------------------------------------------------------*/
//this fonction return the name of save
char ** getSaveFile(const char* NomRep, int *i) {

    char **saveFile = malloc(sizeof(char*)*LONG_MAX_REP);  //
    for (size_t j = 0; j < LONG_MAX_REP; j++) {
        saveFile[j] = malloc(sizeof(char)*40);
    }
    char newEnTeteRep[300];
    struct stat infos;
    DIR *srcDir = NULL;
    struct dirent *fichOuRep = NULL;
    if ((srcDir = opendir(NomRep)) == NULL) {
        perror("Erreur d'ouverture du repertoire\n");
        exit(1);
    }else{
        while ((fichOuRep = readdir(srcDir)) != NULL) {
            if ((strcmp (fichOuRep->d_name, ".") != 0) && (strcmp (fichOuRep->d_name, "..") != 0)
                && (strcmp (fichOuRep->d_name, ".DS_Store") != 0)) {
                //creation du chemin du prochain de mon fichOuRep
                strcpy(newEnTeteRep, NomRep);
                strcat(newEnTeteRep, "/");
                strcat(newEnTeteRep, fichOuRep->d_name);
                if (stat(newEnTeteRep, &infos) == -1) {
                    perror("Erreur stat");
                    exit(2);
                }
                //test si l'on travail avec un repertoire ou un fichier
                //le comportement est different l'appel recursif se fait dans le cas ou c'est un dossier
                if (!S_ISDIR(infos.st_mode)) {
                    strcpy(saveFile[(*i)++], fichOuRep->d_name);
                }
            }
        }
    }
    return saveFile;
}
//We use this foncton to free the saveFile
void freeSaveFile(char** saveFile) {
    for (size_t i = 0; i < LONG_MAX_REP; i++) {
        free (saveFile[i]);
    }
    free(saveFile);
}
