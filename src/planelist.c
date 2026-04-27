#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "alist.h"
#include "airplane.h"
#include "planelist.h"

static alist planes;
static pthread_mutex_t list_lock = PTHREAD_MUTEX_INITIALIZER;

void planelist_init() {
    alist_init(&planes, free);
}

void planelist_add(airplane *plane) {
    pthread_mutex_lock(&list_lock);
    alist_add(&planes, plane);
    pthread_mutex_unlock(&list_lock);
}

void planelist_remove(airplane *plane) {
    pthread_mutex_lock(&list_lock);
    for (int i = 0; i < alist_size(&planes); i++) {
        if (alist_get(&planes, i) == plane) {
            alist_remove(&planes, i);
            break;
        }
    }
    pthread_mutex_unlock(&list_lock);
}

airplane *planelist_find(char *flightid) {
    pthread_mutex_lock(&list_lock);
    for (int i = 0; i < alist_size(&planes); i++) {
        airplane *p = alist_get(&planes, i);
        if (strcmp(p->id, flightid) == 0) {
            pthread_mutex_unlock(&list_lock);
            return p;
        }
    }
    pthread_mutex_unlock(&list_lock);
    return NULL;
}

void planelist_destroy() {
    alist_destroy(&planes);
}