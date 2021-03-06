/*
 * helperfunc.h
 *
 *  Created on: 28 apr 2014
 *      Author: andreas
 */

#ifndef HELPERFUNC_H_
#define HELPERFUNC_H_
#include <SDL/SDL.h>
#include "create.h"
struct node{
	astroid astroid;
	struct node *next;
}typedef node;


//This function adds an astroid at the beginning of the linked list
//Example call: add_item_beginning(&root, image, 0 , 0 , 1); where root is a pointer to a node and image is a pointer to an image
extern void add_item_beginning(node ** root, float x, float y, int id);


//This function search and removes the node with the astroid id given
extern int remove_id(node ** root,int id);


//This function creates a linked list the pointer sent in will be the root of the list
//Example call: create_linked_list(root); where root is a pointer to a node
extern void create_linked_list();


//This function searches for an astroid id and returns the position in the linked list
extern int search_id();



//This function fills the list with Astroids and specifies the x,y and takes an image array. Note adds item at the beginning of the list
//Example call: fill_list(&root,images,0,0,10); where root is a pointer to a node and images is an array of pointers to SDL_Surface
extern void fill_list(node **root, float x, float y, int size);

//This function sets all asteroid's start position and velocity.
extern void set_asteroids();

#endif /* HELPERFUNC_H_ */
