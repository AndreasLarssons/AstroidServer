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
#include "draw.h"

extern TCPsocket connect();
extern TCPsocket accept();

//This function accepts new connections to clients and create specific threads for that connection.
//Also keeps that so no more than 4 clients can be connected at one time.
extern void accept_connections();

//Looks for an available slot in the global thread array.
extern int check_open_slot();


extern SDL_Thread create_thread();

//This function is the function all client threads use to receive data and forward it to all other clients.
extern int connected_client();

//Sends specified data to specified client.
extern int send_data();

//Read data from the network buffer and saves it, checks if the data is client position data.
extern int read_data();

//Sends specified data to all clients.
extern int forward_data();
extern void fill_socket(TCPsocket *from[], TCPsocket * to[], int size);
extern int **id_global;
extern char **answer;

//Checks if saved data is bullet data.
extern int read_bullet_data();

//Checks if saved data is asteroid data.
extern int read_astroid_data();

#endif /* NETWORK_H_ */
