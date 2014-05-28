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
	node * root;

}typedef thread_data;
TCPsocket connected_clients[4] = { NULL };
int count_thread[4] = { 0 };

TCPsocket connect() {
	IPaddress ip;
	TCPsocket socket;
	int port = 0;
	printf("Enter port to listen to: ");
	scanf("%d", &port);

	if (SDLNet_ResolveHost(&ip, NULL, port) == -1) {
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(1);
	}
	ip.host = INADDR_ANY;

	socket = SDLNet_TCP_Open(&ip);
	if (!socket) {
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}
	return socket;
}
void accept_connections(TCPsocket *socket, SDL_Thread *connected[],
		int *counter, node * root) {
	TCPsocket acc_socket;
	int open_slot = 0;
	int count_slot = 0;
	int error = 1;
	int id_counter = 0;
	SDL_mutex *mutex = SDL_CreateMutex();
//	SDL_Thread *send_thread = SDL_CreateThread(forward_data, NULL);
	while (error) {
		SDL_Delay(3000);
		acc_socket = SDLNet_TCP_Accept(*socket);
		if (count_slot == 4) {
			send_data("Error\0", acc_socket);
			SDLNet_TCP_Close(acc_socket);
		}
		if (!acc_socket) {
			//printf("SDLNet_TCP_Accept: %s\n", SDLNet_GetError());
			SDLNet_TCP_Close(acc_socket);
		} else {

			if ((open_slot = check_open_slot()) != -1) {
				thread_data data;
				data.socket = &acc_socket;
				data.slot = open_slot;
				data.id = id_counter;
				data.root = root;
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
			if (send_data(msg, connected_clients[i], format_string) == -1) {
				return -1;
			}
			//printf("%s, %d\n", msg, my_id);
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
	int i = 0;
	char handshake[10];
	char *client_data[10] = { NULL };
	char msg[10];
	int x = 0, y = 0, id = 0;
	double angle = 0;
	sprintf(handshake, "#|%d|#", input_data->id);
	send_data(handshake, socket, "#|%d|#");
	SDL_Delay(10);
	node * tmp = input_data->root;
	for (i = 0; i < 11; i++) {
		if (tmp != NULL) {
			sprintf(msg, "*%d|%d|%d|%d*", tmp->astroid.id, tmp->astroid.x,
					tmp->astroid.y, tmp->astroid.velocity);
			send_data(msg, socket, "*%d|%d|%d|%d*");
			printf("Asteroid #%d: %s\n", tmp->astroid.id, msg);
			tmp = tmp->next;
			SDL_Delay(10);
		}
	}

	printf("Server: Start receiving data\n");
	ready = 1;
	while (1) {
		//SDL_Delay(10);
		if (read_data(msg, socket, &id, &x, &y, &angle, "#%d|%d|%d|%d|%d|%d#")
				== -1) {
			if (forward_data(msg, id, "#%d|%d|%d|%lf#") == -1) {
				return 0;
			}
		} else if (read_bullet_data(msg, "?%d|%d|%d|%d|%d?") == -1) {
			if (forward_data(msg, id, "#%d|%d|%d|%lf#") == -1) {
				return 0;
			}
		} else if (read_astroid_data(msg, "*%d|%d|%d*", input_data->root)
				== -1) {
			printf("YO!\n");
			if (forward_data(msg, id, "#%d|%d|%d|%lf#") == -1) {
				return 0;
			}
		}
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
		double *angle, char format_string[]) {
	int len, result;

	len = strlen(msg) + 1; // add one for the terminating NULL
	result = SDLNet_TCP_Recv(socket, msg, 100);
	if (result < len) {
		printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
		return -1;
		// It may be good to disconnect sock because it is likely invalid now.
	}
	if (sscanf(msg, format_string, id, x, y, angle) == 6) {
		return -1;
	}
	return 0;
}

int read_bullet_data(char msg[], char format_string[]) {
	int id, x, y, angle, slot;
	if (sscanf(msg, format_string, &id, &slot, &x, &y, &angle) == 5) {
		return -1;
	}
	return 0;
}

int read_astroid_data(char msg[], char format_string[], node * root) {
	int id, slot, asteroid;
	if (sscanf(msg, format_string, &id, &asteroid, &slot) == 3) {
		remove_id(&root, asteroid);
		return -1;
	}
	return 0;
}
