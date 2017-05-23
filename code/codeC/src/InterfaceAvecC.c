//  InterfaceAvecC.c
//  InterfaceAvecC
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.
//

#include <jni.h>
#include <stdio.h>
#include <stdbool.h>
#include <mm_malloc.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "InterfaceAvecC.h"
#include "Graph.h"
#include "ReducedGraph.h"
#include "TreeOfGameIA.h"

#define ERR_CLASS_ACCESS 1
#define ERR_METHOD_ACCESS 2

/*-----------------------------------------------------------------------------*/
//Global Value
Graph globGraph;
ReducedGraph * globRg;
/* -*************************************************************************- */

/*-------------------------IMPLEMENTATION InterfaceAvecC-----------------------*/
JNIEXPORT jchar JNICALL
Java_InterfaceAvecC_nativeInitGame (JNIEnv * env, jclass cl, jstring spots, jobject obj) {
    const char * s = (*env)->GetStringUTFChars(env, spots, 0);
    int nbSpots= strlen(s);
    int sizeBoard = sqrt(nbSpots);
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
        exit(ERR_CLASS_ACCESS);
    }

    jmethodID play = (*env)->GetMethodID(env, jeuHex, "play", "()C");
    if (play == NULL) {
        fprintf(stderr, "Error : method not found !\n");
        exit(ERR_METHOD_ACCESS);
    }
    jchar event = (*env)->CallIntMethod(env, obj, play, sizeBoard, s);
    (*env)->ReleaseStringUTFChars(env, spots, s);

    destroyReducedGraph(globRg);
    destroyGraph(globGraph);
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
    }else {
        win = searchGroup(globRg->whiteHashTab, globGraph, pos, WHITE);
    }
    return win;
}

JNIEXPORT jstring JNICALL
Java_InterfaceAvecC_nativeGetSpots (JNIEnv * env, jclass cl, jstring fileName) {
    const char *s = (*env)->GetStringUTFChars(env, fileName, 0);
    char *spots = getSpotsFromFile(s);

    jstring str = (*env)->NewStringUTF(env, spots);
    (*env)->ReleaseStringUTFChars(env, fileName, s);
    free(spots);
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
    free(s);
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

JNIEXPORT jint JNICALL
Java_InterfaceAvecC_nativeMiniMax (JNIEnv * env, jclass cl) {
    return minimax(globGraph, 2); //2 is the depth of TreeOfGameIA
}
/*-----------------------------------------------------------------------------*/
/* -*************************************************************************- */
