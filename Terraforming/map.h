#ifndef MAP_H
#define MAP_H
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


//Constants
#define HEIGHT 30
#define WIDTH 30

//Datatypes..
enum Map {
	wall = 'x', freespace = ' ', player1 = 'H', player2 = 'U', bullet = 'O',
	left = 'l', up = 'u', right = 'r', down = 'd'
};

enum Map Game_Map[HEIGHT][WIDTH];	



//Functions:
void clear_pathfinder_track();	//Clear algorithm path, so it looks like much better(only with H,U,X)
int is_connected_to_player1(int y, int x);	//Is position(y,x) connected with player1 position?
void generate_map();	//Generate random map
void show_map();		//Show map as a 2d ascii table


#endif
