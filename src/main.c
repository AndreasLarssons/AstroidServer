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
#include "create.h"
#include "draw.h"
#include "helperfunc.h"

int **id_global = NULL;
char **answer = NULL;
int ready = 0;
int main(int argc, char **arg) {
	if (SDLNet_Init() < 0) {
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	node *root = NULL;
	create_linked_list(root);
	fill_list(&root,0,0,11);
	//set_asteroids(root);
//	printf("%d\n", search_id(root, 10));
	SDL_Thread *running_threads[4] = {NULL};
	int counter = 0;
	TCPsocket socket;
	socket = connect();
	astroid_data astroid_data;
	astroid_data.size = 11;
	astroid_data.ready = 0;
	astroid_data.root = root;
	SDL_Thread * astroid_control = SDL_CreateThread(control_astroids, &astroid_data);
	accept_connections(&socket, running_threads, &counter, root);

	return 0;
}
