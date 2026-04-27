#ifndef _PLANELIST_H
#define _PLANELIST_H

#include "airplane.h"

void planelist_init();
void planelist_add(airplane *plane);
void planelist_remove(airplane *plane);
airplane *planelist_find(char *flightid);
void planelist_destroy();

#endif  // _PLANELIST_H