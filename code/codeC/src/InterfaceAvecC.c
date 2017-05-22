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

JNIEXPORT jchar JNICALL
Java_InterfaceAvecC_nativeInitGame (JNIEnv * env, jclass cl, jstring spots, jobject obj) {
    const char * s = (*env)->GetStringUTFChars(env, spots, 0);
    int nbSpots= strlen(s); printf("nbSpots = %d\n", nbSpots);
    int sizeBoard = sqrt(nbSpots); printf("sizeBoard = %d\n", sizeBoard);
    int loaded = 0;
    globGraph = createGraph(sizeBoard);
    globGraph = createBoardGraph(globGraph, s, &loaded);
    globRg = createReducedGraph(globGraph);
    if (loaded == 1) {
        globRg = reloadGroups(globGraph, globRg);
    }

    jclass jeuHex = (*env)->GetObjectClass(env, obj);
    if (jeuHex == NULL) {
        fprintf(stderr, "Error : class not found !\n");
        exit(-1);
    }

    jmethodID play = (*env)->GetMethodID(env, jeuHex, "play", "()C");
    if (play == NULL) {
        fprintf(stderr, "Error : method not found !\n");
        exit(-1);
    }
    jchar event = (*env)->CallIntMethod(env, obj, play, sizeBoard, s);
    (*env)->ReleaseStringUTFChars(env, spots, s);

    destroyReducedGraph(globRg);
    printf("is null Graph %d\n", globGraph == NULL);
    //destroyGraph(globGraph);
    //printf("is null Graph1 %d\n", globGraph == NULL);
    return event;
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
    return calculateHexCoordinates(x, y, sizeBoard);
}

JNIEXPORT int JNICALL
Java_InterfaceAvecC_nativePlacePiece (JNIEnv * env, jclass cl, jint pos, jchar color) {
    jint win = 0;
    replaceVertexGraph(globGraph, pos, color);
    if (color == BLACK) {
        win = searchGroup(globRg->blackHashTab, globGraph, pos, BLACK);
        printf("black win %d\n", win);
    }else {
        win = searchGroup(globRg->whiteHashTab, globGraph, pos, WHITE);
        printf("black win %d\n", win);
    }
    return win;
}

JNIEXPORT jstring JNICALL
Java_InterfaceAvecC_nativeGetSpots (JNIEnv * env, jclass cl, jstring fileName) {
    const char *s = (*env)->GetStringUTFChars(env, fileName, 0);
    char *spots = getSpotsFromFile(s);

    jstring str = (*env)->NewStringUTF(env, spots);
    (*env)->ReleaseStringUTFChars(env, fileName, s);
    free(spots); // je libère le spots
    return str;
}

JNIEXPORT void JNICALL
Java_InterfaceAvecC_nativeSaveGame (JNIEnv * env, jclass cl,
    jstring savedFileName, jstring stringToSave, jintArray bMovesTab, jintArray wMovesTab) {
    jsize bSize = (*env)->GetArrayLength(env, bMovesTab);
    jsize wSize = (*env)->GetArrayLength(env, wMovesTab);

    jint *bBody = (*env)->GetIntArrayElements(env, bMovesTab, 0);
    jint *wBody = (*env)->GetIntArrayElements(env, wMovesTab, 0);

    int bMovesTabBis[bSize];
    int wMovesTabBis[wSize];

    //conversion of the java tables into c tables
	for (int i = 0; i < bSize; i++) {
        bMovesTabBis[i] = bBody[i];
    }
	for (int i = 0; i < wSize; i++) {
         wMovesTabBis[i] = wBody[i];
    }

    const char * fileName = (*env)->GetStringUTFChars(env, savedFileName, 0);
    const char * strToSave = (*env)->GetStringUTFChars(env, stringToSave, 0);

    saveBoardFile(fileName, strToSave, bMovesTabBis, wMovesTabBis);

    //for the free in java
    (*env)->ReleaseStringUTFChars(env, savedFileName, fileName);
    (*env)->ReleaseStringUTFChars(env, stringToSave, strToSave);
    (*env)->ReleaseIntArrayElements(env, bMovesTab, bBody, 0);
    (*env)->ReleaseIntArrayElements(env, wMovesTab, wBody, 0);
}

//save player
JNIEXPORT void JNICALL
Java_InterfaceAvecC_nativeSavePlayer (
    JNIEnv *env, jclass cl, jstring nameOfSavePlayer, jstring bPlayer, jstring wPlayer) {

    const char * fileName = (*env)->GetStringUTFChars(env, nameOfSavePlayer, 0);
    const char * blackP = (*env)->GetStringUTFChars(env, bPlayer, 0);
    const char * whiteP = (*env)->GetStringUTFChars(env, wPlayer, 0);

    savePlayer(fileName, blackP, whiteP);

    (*env)->ReleaseStringUTFChars(env, nameOfSavePlayer, fileName);
    (*env)->ReleaseStringUTFChars(env, bPlayer, blackP);
    (*env)->ReleaseStringUTFChars(env, wPlayer, whiteP);
}

//load
JNIEXPORT jstring JNICALL
Java_InterfaceAvecC_nativeStringToLoadPlayer (JNIEnv * env, jclass cl, jchar color,
    jstring loadFileName) {

    const char * fileName = (*env)->GetStringUTFChars(env, loadFileName, 0);
    char *s = loadPlayer(color, fileName);
    jstring loadFile = (*env)->NewStringUTF(env, s);
    (*env)->ReleaseStringUTFChars(env, loadFileName, fileName);
    free(s); //je libere le chaine
    return loadFile;
}

JNIEXPORT jobjectArray JNICALL
Java_InterfaceAvecC_nativeGetSaveFile (JNIEnv * env, jclass cl) {
    const char* dirName = "../../../doc/SaveFiles";
    int size = 0;
    char ** saveFile = getSaveFiles(dirName, &size);
    // retrieval of the java String class
    jclass stringClass = (*env)->FindClass(env, "java/lang/String");
    // construction of an array of strings
    jobjectArray tabString = (jobjectArray)(*env)->NewObjectArray(env, size, stringClass, NULL);

    for (size_t i = 0; i < size; i++) {
        jstring str = (*env)->NewStringUTF(env, saveFile[i]);
        (*env)->SetObjectArrayElement(env, tabString, i, (jobject)str);
    }
    destroySaveFiles(saveFile); //libere le tableau de chaine de caractere
    return tabString;
}
/*-----------------------------------------------------------------------------*/
/* -*************************************************************************- */
