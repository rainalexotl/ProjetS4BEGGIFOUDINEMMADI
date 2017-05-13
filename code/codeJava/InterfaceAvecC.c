#include <jni.h>
#include <stdio.h>
#include <stdbool.h>
#include <mm_malloc.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "InterfaceAvecC.h"
#include "../codeC/graphPlateau/Graph.h"
/*-----------------------------------------------------------------------------*/
//Global Value
Graph globGraph;
/* -*************************************************************************- */

/*-------------------------IMPLEMENTATION InterfaceAvecC-----------------------*/
JNIEXPORT jobject JNICALL
Java_InterfaceAvecC_nativeInitPiece (JNIEnv * env, jclass cl, jchar color) {
    jclass piece = (*env)->FindClass(env, "Piece");
    jmethodID mid = (*env)->GetMethodID(env, piece, "<init>", "(C)V");
    jobject object = (*env)->NewObject(env, piece, mid, color);
    return object;
}


JNIEXPORT jobject JNICALL
Java_InterfaceAvecC_nativeInitHex (JNIEnv * env, jclass cl, jint x, jint y, jchar color) {
    jclass hex = (*env)->FindClass(env, "Hex");
    jmethodID mid = (*env)->GetMethodID(env, hex, "<init>", "(IIC)V");
    jobject object = (*env)->NewObject(env, hex, mid, x, y, color);
    return object;
}

JNIEXPORT jobject JNICALL
Java_InterfaceAvecC_nativeInitBoard (JNIEnv * env, jclass cl, jint sizeBoard, jstring spots) {
    printf("je passe par initBoard\n");
    jclass board = (*env)->FindClass(env, "Board");
    if (board == NULL) {
        fprintf(stderr, "error : class not found !\n");
        exit(-1);
    }
    printf("je passe par initBoard\n");
    jmethodID mid = (*env)->GetMethodID(env, board, "<init>", "(ILjava/lang/String;)V");
    if (mid == NULL) {
        fprintf(stderr, "error : method not found !\n");
        exit(-1);
    }
    printf("je passe par initBoard\n");
    jobject object = (*env)->NewObject(env, board, mid, sizeBoard, spots);
    printf("je passe par initBoard\n");
    return object;
}

//appel la methode play de java
JNIEXPORT int JNICALL
Java_InterfaceAvecC_nativeInitGame (JNIEnv * env, jclass cl, jstring spots, jobject obj) {
    const char * s = (*env)->GetStringUTFChars(env, spots, 0);
    int nbSpots= strlen(s); printf("nbSpots = %d\n", nbSpots);
    int sizeBoard = sqrt(nbSpots); printf("sizeBoard = %d\n", sizeBoard);
    globGraph = CreateGraph(sizeBoard);
    globGraph = CreateBoardGraph(globGraph, s);
    printf("je passe la \n");
    jclass jeuHex = (*env)->GetObjectClass(env, obj);
    if (jeuHex == NULL) {
        fprintf(stderr, "error : class not found !\n");
        exit(-1);
    }

    jmethodID play = (*env)->GetMethodID(env, jeuHex, "play", "()I");
    if (play == NULL) {
        fprintf(stderr, "error : method not found !\n");
        exit(-1);
    }
    printf("je passe la \n");
    jint etatDuJeu = (*env)->CallIntMethod(env, obj, play, sizeBoard, s);
    printf("je passe la \n");
    // destroyGraph(globGraph);
    (*env)->ReleaseStringUTFChars(env, spots, s);
    return etatDuJeu;
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
JNIEXPORT void JNICALL
Java_InterfaceAvecC_nativePlacePiece (JNIEnv * env, jclass cl, jint pos, jchar color) {
    printf("1 %d %c\n", pos, color);
    postUpBoard(globGraph);
    printf("2\n");
    replaceVertexGraph(globGraph, pos, color);
    printf("3\n");
    postUpBoard(globGraph);
    printf("4\n");
}

JNIEXPORT jstring JNICALL
Java_InterfaceAvecC_nativeGetSpots (JNIEnv * env, jclass cl, jstring fileName) {
    const char *s = (*env)->GetStringUTFChars(env, fileName, 0);
    char *spots = transformGraphToBoardOfChar(s);
    jstring str = (*env)->NewStringUTF(env, spots);
    (*env)->ReleaseStringUTFChars(env, fileName, spots);
    return str;
}
/*-----------------------------------------------------------------------------*/
/* -*************************************************************************- */
