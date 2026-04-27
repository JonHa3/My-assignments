#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "airplane.h"
#include "airs_protocol.h"
#include "planelist.h"

#define PORT 8080

void *handle_plane(void *arg) {
    pthread_detach(pthread_self());

    int sockfd = *(int *)arg;
    free(arg);

    // Create two independent file handles from the socket
    int sockfd2 = dup(sockfd);
    FILE *fp_send = fdopen(sockfd, "w");
    FILE *fp_recv = fdopen(sockfd2, "r");

    // Set line buffering
    setvbuf(fp_send, NULL, _IOLBF, 0);
    setvbuf(fp_recv, NULL, _IOLBF, 0);

    airplane *plane = malloc(sizeof(airplane));
    airplane_init(plane, fp_send, fp_recv);
    planelist_add(plane);

    char *lineptr = NULL;
    size_t linesize = 0;

    while (plane->state != PLANE_DONE) {
        if (getline(&lineptr, &linesize, plane->fp_recv) < 0) {
            break;
        }
        docommand(plane, lineptr);
    }

    free(lineptr);
    planelist_remove(plane);
    airplane_destroy(plane);
    free(plane);

    return NULL;
}

int main(int argc, char *argv[]) {
    planelist_init();

    int serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd < 0) {
        perror("socket");
        exit(1);
    }

    // Allow port reuse so we can restart quickly
    int opt = 1;
    setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(serverfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(serverfd, 10) < 0) {
        perror("listen");
        exit(1);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        int *clientfd = malloc(sizeof(int));
        *clientfd = accept(serverfd, NULL, NULL);
        if (*clientfd < 0) {
            perror("accept");
            free(clientfd);
            continue;
        }

        pthread_t thread;
        pthread_create(&thread, NULL, handle_plane, clientfd);
    }

    planelist_destroy();
    return 0;
}