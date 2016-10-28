/*
 * lab1a.c
 *
 *  Created on:
 *      Author:
 */

/* include helper functions for game */
#include "lifegame.h"

/* add whatever other includes here */

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement */

/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);

/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

int main(void)
{
	int n;
	initialize_world();

	for (n = 0; n < NUM_GENERATIONS; n++) {
	    output_world();
		next_generation();
		sleep(1);
	}

	output_world();

	return 0;
}

void next_generation(void) {
    int x, y;
    for (x = 0; x < get_world_width(); x++) {
        for (y = 0; y < get_world_height(); y++) {
            set_cell_state(x, y, get_next_state(x, y));
        }
    }
	finalize_evolution(); /* called at end to finalize */
}

int get_next_state(int x, int y) {
    if (get_cell_state(x, y) == ALIVE) {
        if (num_neighbors(x, y) < 2) return DEAD;
        if (num_neighbors(x, y) < 4) return ALIVE;
        return DEAD;
    } else {
        if (num_neighbors(x, y) == 3) return ALIVE;
        return DEAD;
    }
}

int num_neighbors(int x, int y) {
    int neighborsCount = 0;
    if (get_cell_state(x - 1, y - 1) == ALIVE) neighborsCount++;
    if (get_cell_state(x - 1, y) == ALIVE) neighborsCount++;
    if (get_cell_state(x - 1, y + 1) == ALIVE) neighborsCount++;
    if (get_cell_state(x, y - 1) == ALIVE) neighborsCount++;
    if (get_cell_state(x, y + 1) == ALIVE) neighborsCount++;
    if (get_cell_state(x + 1, y - 1) == ALIVE) neighborsCount++;
    if (get_cell_state(x + 1, y) == ALIVE) neighborsCount++;
    if (get_cell_state(x + 1, y + 1) == ALIVE) neighborsCount++;
    return neighborsCount;
}
