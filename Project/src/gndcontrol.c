#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "airplane.h"
#include "airs_protocol.h"

int main(int argc, char *argv[]) {
    airplane myplane;
    airplane_init(&myplane, stdout, stdin);

    char *lineptr = NULL;
    size_t linesize = 0;

    while (myplane.state != PLANE_DONE) {
        if (getline(&lineptr, &linesize, myplane.fp_recv) < 0) {
            break;
        }
        docommand(&myplane, lineptr);
    }

    return 0;
}