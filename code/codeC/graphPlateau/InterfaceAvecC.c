#include <jni.h>
#include <stdio.h>
#include <stdbool.h>
#include <mm_malloc.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "../../codeJava/InterfaceAvecC.h"
#include "Graph.h"
#include "ReducedGraph.h"
/*-----------------------------------------------------------------------------*/
//Global Value
Graph globGraph;
ReducedGraph * globRg;
/* -*************************************************************************- */

/*-------------------------IMPLEMENTATION InterfaceAvecC-----------------------*/
// JNIEXPORT jobject JNICALL
// Java_InterfaceAvecC_nativeInitPiece (JNIEnv * env, jclass cl, jchar color) {
//     jclass piece = (*env)->FindClass(env, "Piece");
//     if (/* condition */) {
//         /* code */
//     }
//     jmethodID mid = (*env)->GetMethodID(env, piece, "<init>", "(C)V");
//     jobject object = (*env)->NewObject(env, piece, mid, color);
//     return object;
// }


// JNIEXPORT jobject JNICALL
// Java_InterfaceAvecC_nativeInitHex (JNIEnv * env, jclass cl, jint x, jint y, jchar color) {
//     jclass hex = (*env)->FindClass(env, "Hex");
//     jmethodID mid = (*env)->GetMethodID(env, hex, "<init>", "(IIC)V");
//     jobject object = (*env)->NewObject(env, hex, mid, x, y, color);
//     return object;
// }

// JNIEXPORT jobject JNICALL
// Java_InterfaceAvecC_nativeInitBoard (JNIEnv * env, jclass cl, jint sizeBoard, jstring spots) {
//     printf("je passe par initBoard\n");
//     jclass board = (*env)->FindClass(env, "Board");
//     if (board == NULL) {
//         fprintf(stderr, "error : class not found !\n");
//         exit(-1);
//     }
//     printf("je passe par initBoard\n");
//     jmethodID mid = (*env)->GetMethodID(env, board, "<init>", "(ILjava/lang/String;)V");
//     if (mid == NULL) {
//         fprintf(stderr, "error : method not found !\n");
//         exit(-1);
//     }
//     printf("je passe par initBoard\n");
//     jobject object = (*env)->NewObject(env, board, mid, sizeBoard, spots);
//     printf("je passe par initBoard\n");
//     return object;
// }

//appel la methode play de java
JNIEXPORT jchar JNICALL
Java_InterfaceAvecC_nativeInitGame (JNIEnv * env, jclass cl, jstring spots, jobject obj) {
    const char * s = (*env)->GetStringUTFChars(env, spots, 0);
    int nbSpots= strlen(s); printf("nbSpots = %d\n", nbSpots);
    int sizeBoard = sqrt(nbSpots); printf("sizeBoard = %d\n", sizeBoard);
    int loaded = 0;
    globGraph = CreateGraph(sizeBoard);
    globGraph = CreateBoardGraph(globGraph, s, &loaded);
    globRg = createReducedGraph(globGraph);
    if (loaded == 1) {
        globRg = reloadGroups(globGraph, globRg);
    }
    //printf("je passe la \n");
    jclass jeuHex = (*env)->GetObjectClass(env, obj);
    if (jeuHex == NULL) {
        fprintf(stderr, "error : class not found !\n");
        exit(-1);
    }

    jmethodID play = (*env)->GetMethodID(env, jeuHex, "play", "()C");
    if (play == NULL) {
        fprintf(stderr, "error : method not found !\n");
        exit(-1);
    }
    //printf("je passe la \n");
    jchar circonstance = (*env)->CallIntMethod(env, obj, play, sizeBoard, s);
    //printf("je passe la \n");
    // destroyGraph(globGraph);
    (*env)->ReleaseStringUTFChars(env, spots, s);
    return circonstance;
}

JNIEXPORT jint JNICALL
Java_InterfaceAvecC_nativeCalcXCoord (JNIEnv * env, jclass cl, jint i, jint sizeBoard) {
    return calculateCoordinates(i, sizeBoard).x;
}

JNIEXPORT jint JNICALL
Java_InterfaceAvecC_nativeCalcYCoord (JNIEnv * env, jclass cl, jint i, jint sizeBoard) {
    return calculateCoordinates(i, sizeBoard).y;
}

JNIEXPORT jint JNICALL
Java_InterfaceAvecC_nativeCalcPosition (JNIEnv * env, jclass cl, jint x, jint y, jint sizeBoard) {
    return calculateSquareCoordinates(x, y, sizeBoard);
}

//modifier la couleur du graph
//on cherchera les groupe
JNIEXPORT int JNICALL
Java_InterfaceAvecC_nativePlacePiece (JNIEnv * env, jclass cl, jint pos, jchar color) {
    jint win = 0;
    replaceVertexGraph(globGraph, pos, color);
    if (color == BLACK) {
        win = searchGroup(globRg->blackHashTab, globGraph, pos, BLACK);
    }else {
        win = searchGroup(globRg->whiteHashTab, globGraph, pos, WHITE);
    }
    return win;
}

JNIEXPORT jstring JNICALL
Java_InterfaceAvecC_nativeGetSpots (JNIEnv * env, jclass cl, jstring fileName) {
    const char *s = (*env)->GetStringUTFChars(env, fileName, 0);
    char *spots = transformGraphToBoardOfChar(s);

    jstring str = (*env)->NewStringUTF(env, spots);
    (*env)->ReleaseStringUTFChars(env, fileName, s);
    return str;
}

JNIEXPORT void JNICALL
Java_InterfaceAvecC_nativeSaveGame (JNIEnv * env, jclass cl,
    jstring savedFileName, jstring stringToSave, jintArray BMovesTab, jintArray WMovesTab) {
    jsize Bsize = (*env)->GetArrayLength(env, BMovesTab);
    jsize Wsize = (*env)->GetArrayLength(env, WMovesTab);

    jint *Bbody = (*env)->GetIntArrayElements(env, BMovesTab, 0);
    jint *Wbody = (*env)->GetIntArrayElements(env, WMovesTab, 0);

    int bMovesTab[Bsize];
    int wMovesTab[Wsize];

	for (int i = 0; i <= Bsize; i++) { bMovesTab[i] = Bbody[i]; } //conversion des tab en c
	for (int i = 0; i <= Wsize; i++) { wMovesTab[i] = Wbody[i]; }

    const char * fileName = (*env)->GetStringUTFChars(env, savedFileName, 0);
    const char * strToSave = (*env)->GetStringUTFChars(env, stringToSave, 0);

    saveBoardFile(fileName, strToSave, bMovesTab, wMovesTab);

    //for the free from java
    (*env)->ReleaseStringUTFChars(env, savedFileName, fileName);
    (*env)->ReleaseStringUTFChars(env, stringToSave, strToSave);
    (*env)->ReleaseIntArrayElements(env, BMovesTab, Bbody, 0);
    (*env)->ReleaseIntArrayElements(env, WMovesTab, Wbody, 0);
}

//save player
JNIEXPORT void JNICALL
Java_InterfaceAvecC_nativeSavePlayer (
    JNIEnv *env, jclass cl, jstring nameOfSavePlayer, jstring Bplayer, jstring Wplayer) {

    const char * fileName = (*env)->GetStringUTFChars(env, nameOfSavePlayer, 0);
    const char * blackP = (*env)->GetStringUTFChars(env, Bplayer, 0);
    const char * whiteP = (*env)->GetStringUTFChars(env, Wplayer, 0);

    savePlayer(fileName, blackP, whiteP);

    (*env)->ReleaseStringUTFChars(env, nameOfSavePlayer, fileName);
    (*env)->ReleaseStringUTFChars(env, Bplayer, blackP);
    (*env)->ReleaseStringUTFChars(env, Wplayer, whiteP);
}

//load
JNIEXPORT jstring JNICALL
Java_InterfaceAvecC_nativeStringToLoadPlayer (JNIEnv * env, jclass cl, jchar color,
    jstring stringFromFilInC) {

    const char * fileName = (*env)->GetStringUTFChars(env, stringFromFilInC, 0);
    char *s = loarPlayer(color, fileName);
    jstring loadFil = (*env)->NewStringUTF(env, s);
    (*env)->ReleaseStringUTFChars(env, stringFromFilInC, fileName);
    return loadFil;
}

JNIEXPORT jobjectArray JNICALL
Java_InterfaceAvecC_nativeGetSaveFile (JNIEnv * env, jclass cl) {
    const char* NomRep = "../../SaveFiles";
    int size = 0;
    char ** saveFile = getSaveFile(NomRep, &size);
    for (size_t i = 0; i < size; i++) {
        printf("str1 = %s\n", saveFile[i]);
    }
    // On récupère l'objet classe String
    jclass stringClass = (*env)->FindClass(env, "java/lang/String");
    // On construit un tableau de String
    jobjectArray tabString = (jobjectArray)(*env)->NewObjectArray(env, size, stringClass, NULL);

    for (size_t i = 0; i < size; i++) {
        jstring str = (*env)->NewStringUTF(env, saveFile[i]);
        (*env)->SetObjectArrayElement(env, tabString, i, (jobject)str);
        //(*env)->ReleaseStringUTFChars(env, str, saveFile[i++]);
    }
    //freeSaveFile(saveFile);
    return tabString;
}
/*-----------------------------------------------------------------------------*/
/* -*************************************************************************- */
