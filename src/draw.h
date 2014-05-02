/*
 * draw.h
 *
 *  Created on: 2 maj 2014
 *      Author: andreas
 */

#ifndef DRAW_H_
#define DRAW_H_
#include <SDL/SDL_net.h>
#include "create.h"
#include "helperfunc.h"
#include "network.h"
struct astroid_data{
	node * root;
	int size;
	int *ready;
}typedef astroid_data;
extern int control_astroids();
extern int set_y();
extern int set_x();
extern TCPsocket connected_clients[4];
extern int ready;
#endif /* DRAW_H_ */
