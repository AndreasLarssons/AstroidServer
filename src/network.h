/*
 * network.h
 *
 *  Created on: 23 apr 2014
 *      Author: andreas
 */

#ifndef NETWORK_H_
#define NETWORK_H_
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>

extern TCPsocket connect();
extern TCPsocket accept();
extern void accept_connections();
extern int check_open_slot();
extern SDL_Thread create_thread();
extern int connected_client();

#endif /* NETWORK_H_ */
