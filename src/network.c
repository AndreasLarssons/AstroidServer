/*
 * network.c
 *
 *  Created on: 23 apr 2014
 *      Author: andreas
 */
#include "network.h"
#define MAXCONNECTIONS 4

TCPsocket connect(){
	IPaddress ip;
	TCPsocket socket;

	if(SDLNet_ResolveHost(&ip,NULL,9999)==-1) {
	    printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
	    exit(1);
	}

	socket=SDLNet_TCP_Open(&ip);
	if(!socket) {
	    printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
	    exit(2);
	}
	return socket;
}
void accept_connections(TCPsocket *socket, SDL_Thread *connected[], int *counter, TCPsocket accepted[]){
	TCPsocket acc_socket;
	int open_slot = 0;
	int error = 1;
	while(error){
		acc_socket = SDLNet_TCP_Accept(*socket);
		if(!acc_socket) {
			    printf("SDLNet_TCP_Accept: %s\n", SDLNet_GetError());
		}
		if ((open_slot = check_open_slot(connected)) != -1){
			connected[open_slot] = SDL_CreateThread(connected_client, NULL);
		}
	}
}

int check_open_slot(SDL_Thread *connected[]){

	int slot;
	for (slot = 0; slot < MAXCONNECTIONS; slot++){
		if (connected[slot] == 0){
			return slot;
		}
	}

	return -1;
}
int connected_client(void *data){

	return 0;
}
