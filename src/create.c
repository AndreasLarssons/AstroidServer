/*
 * create.c
 *
 *  Created on: 28 apr 2014
 *      Author: andreas
 */
#include "create.h"
#include "draw.h"

void set_astroid_pos(node * root, int size) {
	int i = 0;
	node * iterate = root;
	for (i = 0; i < size; i++) {
		iterate->astroid.direction = rand() % 4;
		if (iterate->astroid.direction == RIGHT) {
			if ((iterate->astroid.x = rand() % (1366 / 2) + (1366 / 2)) == 1366) {
				iterate->astroid.y = rand() % (768 / 2);
			} else {
				iterate->astroid.y = 0;
			}
		} else if (iterate->astroid.direction == LEFT) {

			if ((iterate->astroid.x = rand() % (1366 / 2)) == 0) {
				iterate->astroid.y = rand() % (768 / 2);
			} else {
				iterate->astroid.y = 0;
			}
		}else if(iterate->astroid.direction == UP){

			iterate->astroid.x = rand() % 1366;
			iterate->astroid.y = 768;
		}
		iterate->astroid.velocity = rand() % 5 + 1;
		iterate = iterate->next;
	}
}

