/*
 * draw.c
 *
 *  Created on: 2 maj 2014
 *      Author: andreas
 */
#include <SDL/SDL_framerate.h>
#include "draw.h"


int control_astroids(void *data) {
	astroid_data *given_data = (astroid_data *) data;

	FPSmanager manager = { 0 };
	SDL_initFramerate(&manager);
	SDL_setFramerate(&manager, 60);

	while(1){
		update_asteroids(given_data->root);
		SDL_framerateDelay(&manager);
	}
	return 0;
}

void update_asteroids(node *root) {
	node * iterate = root;
	int i, a;

	iterate = root;
	int x = rand() % 1366 + 1, y = rand() % 768 + 1;
	SDL_Delay(5);
	for (i = 0; i < 11; i++) {
		if (iterate != NULL) {
			if (i != 0) {
				iterate->astroid.x += iterate->astroid.velocity;
				iterate->astroid.y += iterate->astroid.velocity;
				if (iterate->astroid.y > 740) {
					iterate->astroid.y = 0;
				} else if (iterate->astroid.x > 1350) {
					iterate->astroid.x = 0;
				}
			}
			iterate = iterate->next;
		}
	}
	iterate = root;
}

int set_x() {
	return rand() % 2 + 1;
}

