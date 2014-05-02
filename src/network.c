/*
 * network.c
 *
 *  Created on: 23 apr 2014
 *      Author: andreas
 */
#include "network.h"
#define MAXCONNECTIONS 4
struct thread_data {
	TCPsocket *socket;
	int slot;
	int id;
	int *ready;

}typedef thread_data;
TCPsocket connected_clients[4] = { NULL };
int count_thread[4] = { 0 };

TCPsocket connect() {
	IPaddress ip;
	TCPsocket socket;

	if (SDLNet_ResolveHost(&ip, NULL, 9999) == -1) {
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(1);
	}

	socket = SDLNet_TCP_Open(&ip);
	if (!socket) {
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}
	return socket;
}
void accept_connections(TCPsocket *socket, SDL_Thread *connected[],
		int *counter) {
	TCPsocket acc_socket;
	int open_slot = 0;
	int count_slot = 0;
	int error = 1;
	int id_counter = 0;
	SDL_mutex *mutex = SDL_CreateMutex();
//	SDL_Thread *send_thread = SDL_CreateThread(forward_data, NULL);
	while (error) {
		acc_socket = SDLNet_TCP_Accept(*socket);
		if (count_slot == 4) {
			send_data("Error\0", acc_socket);
			SDLNet_TCP_Close(acc_socket);
		}
		if (!acc_socket) {
			//printf("SDLNet_TCP_Accept: %s\n", SDLNet_GetError());

		} else {

			if ((open_slot = check_open_slot()) != -1) {
				thread_data data;
				data.socket = &acc_socket;
				data.slot = open_slot;
				data.id = id_counter;
				SDL_LockMutex(mutex);
				connected_clients[count_slot] = acc_socket;
				SDL_UnlockMutex(mutex);
				//fill_socket(connected_clients, data.connected_clients, count_slot);
				connected[open_slot] = SDL_CreateThread(connected_client,
						&data);
				count_slot++;
				id_counter++;
			}
		}
	}
}

int forward_data(char msg[], int my_id, char format_string[]) {
	int i = 0;
	while (connected_clients[i] != NULL) {

		if (i != my_id) {
			if (send_data(msg, connected_clients[i], "#%d|%d|%d#") == -1) {
				return 0;
			}
			printf("%s, %d\n", msg, my_id);
		}
		i++;
	}
	i = 0;
	return 0;
}

void fill_socket(TCPsocket *from[], TCPsocket * to[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		from[i] = to[i];
	}
}

int check_open_slot() {
	int slot;
	for (slot = 0; slot < MAXCONNECTIONS; slot++) {
		if (count_thread[slot] == 0) {
			count_thread[slot] = 1;
			return slot;
		}
	}
	return -1;
}
int connected_client(void *data) {
	thread_data *input_data = (thread_data *) data;
	TCPsocket socket = *input_data->socket;
	int my_slot = input_data->slot;
	char handshake[10];
	char *client_data[10] = { NULL };
	char msg[10];
	int x = 0, y = 0, id = 0;
	sprintf(handshake, "#|%d|#", input_data->id);
	send_data(handshake, socket, "#|%d|#");
	ready = 1;
	while (1) {
		SDL_Delay(100);
		read_data(msg, socket, &id, &x, &y, "#%d|%d|%d#");
		printf("%s\n",msg);
//		answer = client_data;
		//SDL_Delay(100);
//		sscanf(*answer, "#%d|%d|%d#", *id_global, &x, &y);
//		sprintf(answer, "#%d|%d|%d#", id, x + 100, y + 100);
		forward_data(msg,id, "#%d|%d|%d#");
	}

	return 0;
}

int send_data(char msg[], TCPsocket socket, char format_string[]) {

	int len, result;

	len = strlen(msg) + 1; // add one for the terminating NULL
	result = SDLNet_TCP_Send(socket, msg, len);
	if (result < len) {
		printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		// It may be good to disconnect sock because it is likely invalid now.
		return -1;
	}
	return 0;
}
int read_data(char msg[], TCPsocket socket, int *id, int *x, int *y,
		char format_string[]) {
	int len, result;

	len = strlen(msg) + 1; // add one for the terminating NULL
	result = SDLNet_TCP_Recv(socket, msg, 100);
	if (result < len) {
		printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
		return -1;
		// It may be good to disconnect sock because it is likely invalid now.
	}
	sscanf(msg, format_string, id, x, y);
	return 0;
}
