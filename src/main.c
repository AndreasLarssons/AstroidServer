/*
 * main.c
 *
 *  Created on: 23 apr 2014
 *      Author: andreas
 */
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>
#include <stdlib.h>
#include "network.h"

int main(int argc, char **arg) {

	if (SDLNet_Init() < 0) {
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_Thread *running_threads[4];
	int counter = 0;
	TCPsocket socket;
	TCPsocket accepted[4];
	socket = connect();
	accept_connections(&socket, running_threads, &counter, accepted);

	return 0;
}
