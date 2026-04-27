#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "util.h"
#include "airplane.h"
#include "planelist.h"
#include "airs_protocol.h"

void send_ok(airplane *plane) {
    fprintf(plane->fp_send, "OK\n");
}

void send_err(airplane *plane, char *desc) {
    fprintf(plane->fp_send, "ERR %s\n", desc);
}

void send_err_sarg(airplane *plane, char *fmtstring, char *sarg) {
    fprintf(plane->fp_send, "ERR ");
    fprintf(plane->fp_send, fmtstring, sarg);
    fprintf(plane->fp_send, "\n");
}

static void cmd_reg(airplane *plane, char *rest) {
    if (plane->state != PLANE_UNREG) {
        send_err(plane, "Already registered");
        return;
    }
    if (rest == NULL || strlen(rest) == 0) {
        send_err(plane, "REG requires a flight ID argument");
        return;
    }
    if (strlen(rest) > PLANE_MAXID) {
        send_err(plane, "Flight ID too long");
        return;
    }
    for (int i = 0; rest[i] != '\0'; i++) {
        if (!isalnum(rest[i])) {
            send_err(plane, "Invalid flight ID -- only alphanumeric characters allowed");
            return;
        }
    }
    // Check for duplicate flight ID
    if (planelist_find(rest) != NULL) {
        send_err(plane, "Flight ID already in use");
        return;
    }
    strncpy(plane->id, rest, PLANE_MAXID);
    plane->id[PLANE_MAXID] = '\0';
    plane->state = PLANE_ATTERMINAL;
    send_ok(plane);
}

static void cmd_reqtaxi(airplane *plane, char *rest) {
    if (plane->state == PLANE_UNREG) {
        send_err(plane, "Not registered");
        return;
    }
    send_err(plane, "Command not yet implemented");
}

static void cmd_bye(airplane *plane, char *rest) {
    plane->state = PLANE_DONE;
}

static void cmd_stub(airplane *plane) {
    if (plane->state == PLANE_UNREG) {
        send_err(plane, "Not registered");
        return;
    }
    send_err(plane, "Command not yet implemented");
}

void docommand(airplane *plane, char *command) {
    char *saveptr;
    char *cmd = strtok_r(command, " \t\r\n", &saveptr);
    if (cmd == NULL) {
        return;
    }
    char *args = strtok_r(NULL, "\r\n", &saveptr);
    if (args != NULL) {
        args = trim(args);
    }
    if (strcmp(cmd, "REG") == 0) {
        cmd_reg(plane, args);
    } else if (strcmp(cmd, "REQTAXI") == 0) {
        cmd_reqtaxi(plane, args);
    } else if (strcmp(cmd, "REQPOS") == 0) {
        cmd_stub(plane);
    } else if (strcmp(cmd, "REQAHEAD") == 0) {
        cmd_stub(plane);
    } else if (strcmp(cmd, "INAIR") == 0) {
        cmd_stub(plane);
    } else if (strcmp(cmd, "BYE") == 0) {
        cmd_bye(plane, args);
    } else {
        send_err(plane, "Unknown command");
    }
}