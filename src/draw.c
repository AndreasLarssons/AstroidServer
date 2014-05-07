/*
 * draw.c
 *
 *  Created on: 2 maj 2014
 *      Author: andreas
 */

#include "draw.h"

int control_astroids(void *data) {
	astroid_data *given_data = (astroid_data *) data;
	node *root = NULL;
	create_linked_list(root);
	fill_list(&root, 0, 0, 10);
	node * iterate = root;
	int i, a;
	for (i = 0; i < 10; i++) {
		iterate->astroid.x = rand()%1366 + 1;
		iterate->astroid.y = 0;
		iterate->astroid.velocity = set_x();
		iterate = iterate->next;
	}
	iterate = root;
	char answer[10];
	while (ready == 0) {
		SDL_Delay(100);
	}
	int x = rand()%1366 + 1, y = rand()%768 + 1;
	while (1) {
		SDL_Delay(5);
		for (i = 0; i < given_data->size; i++) {
			sprintf(answer, "*%d|%d|%d*", iterate->astroid.id, iterate->astroid.x, iterate->astroid.y);
			for (a = 0; a < 4; a++) {
				if (connected_clients[a] == NULL) {
					break;
				} else {
					send_data(answer, connected_clients[a], "*%d|%d|%d*");
					//printf("%s\n", answer);
				}
			}
			iterate->astroid.x += iterate->astroid.velocity;
			iterate->astroid.y += iterate->astroid.velocity;
			if (iterate->astroid.y > 740){
				iterate->astroid.y = 0;
			}else if (iterate->astroid.x > 1350){
				iterate->astroid.x = 0;
			}
			iterate = iterate->next;
		}
		iterate = root;
	}
	return 0;
}

int set_x() {
	return rand() % 2 + 1;
}

