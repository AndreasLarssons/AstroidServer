/*
 * helperfunc.c
 *
 *  Created on: 28 apr 2014
 *      Author: andreas
 */
#include "helperfunc.h"
#include <stdlib.h>
#define VELOCITY 10



void create_linked_list(node *root){
	root = malloc(sizeof(node));
	root->next = NULL;
}

void fill_list(node **root, float x, float y, int size){
	int i;
	for (i = 0; i < size; i++){
		add_item_beginning(root, x, y, i);
	}
}

void add_item_beginning(node ** root, float x, float y, int id){
	node * new_node;
	astroid * new_astroid;
	new_node = malloc (sizeof(node));
	new_astroid = malloc(sizeof(astroid));
	new_astroid->id = id;
//	new_astroid->image = image;
	new_astroid->velocity = VELOCITY;
	new_astroid->x = x;
	new_astroid->y = y;
	new_node->astroid = *new_astroid;
	new_node->next = *root;
	*root = new_node;
}


int search_id(node * root, int id){
	node * current = root;
	int pos;
	while(current != NULL){
		if (current->astroid.id == id){
			return pos;
		}
		current = current->next;
		pos++;
		printf("%d\n", pos);
	}
	return -1;

}

int remove_id(node ** root,int id){
	node * current = *root;
	node * temp_node = NULL;
	int pos = search_id(*root, id);
	int i;
	for (i = 0; i < pos -1; i++){
		if (current->next == NULL){
			return -1;
		}
		current = current->next;
	}
	temp_node = current->next;
	current->next = temp_node->next;
	free(temp_node);
	return 0;
}

