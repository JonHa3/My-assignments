#ifndef _AIRPLANE_H
#define _AIRPLANE_H

#include <stdio.h>
#include <pthread.h>

#define PLANE_MAXID 20

#define PLANE_UNREG 0
#define PLANE_DONE 1
#define PLANE_ATTERMINAL 2
#define PLANE_TAXIING 3
#define PLANE_CLEAR 4
#define PLANE_INAIR 5

typedef struct airplane {
    int state;
    FILE *fp_send;
    FILE *fp_recv;
    char id[PLANE_MAXID+1];
} airplane;

void airplane_init(airplane *plane, FILE *fp_send, FILE *fp_recv);
void airplane_destroy(airplane *plane);

#endif  // _AIRPLANE_H