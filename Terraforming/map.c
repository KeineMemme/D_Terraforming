#include"map.h"

void clear_pathfinder_track() {
	int y,x;
	for(y = 0; y < HEIGHT; y++) {
		for(x = 0; x < WIDTH; x++) {
			if(Game_Map[y][x]==left||Game_Map[y][x]==up||Game_Map[y][x]==right||Game_Map[y][x]==down) {
				Game_Map[y][x] = freespace;
			}
		}
	}

}

int is_connected_to_player1(int y, int x) {
	//Can I go upstairs?
	if(Game_Map[y-1][x] == freespace || Game_Map[y-1][x] == player1) {
		//Is here player1?
		if(Game_Map[y-1][x] == player1) {
			return 1;	//Yipi :) I found him! This map is ok :)
		}
		//Set Arrow in player2 direction
		Game_Map[y-1][x] = down;
		if(is_connected_to_player1(y-1,x)) {
			return 1;
		}
	}
	//Can I go right?
	else if(Game_Map[y][x+1] == freespace || Game_Map[y][x+1] == player1) {
		//Is here player1?
		if(Game_Map[y][x+1] == player1) {
			return 1;	//Yipi :) I found him! This map is ok :)
		}
		//Set Arrow in player2 direction
		Game_Map[y][x+1] = left;
		if(is_connected_to_player1(y,x+1)) {
			return 1;
		}
	}
	//Can I go down?
	else if(Game_Map[y+1][x] == freespace || Game_Map[y+1][x] == player1) {
		//Is here player1?
		if(Game_Map[y+1][x] == player1) {
			return 1;	//Yipi :) I found him! This map is ok :)
		}
		//Set Arrow in player2 direction
		Game_Map[y+1][x] = up;
		if(is_connected_to_player1(y+1,x)) {
			return 1;
		}
	}
	//Can I go left?
	else if(Game_Map[y][x-1] == freespace || Game_Map[y][x-1] == player1) {
		//Is here player1?
		if(Game_Map[y][x-1] == player1) {
			return 1;	//Yipi :) I found him! This map is ok :)
		}
		//Set Arrow in player2 direction
		Game_Map[y][x-1] = right;
		if(is_connected_to_player1(y,x-1)) {
			return 1;
		}
	}
	return 0;

}

void generate_map() {
	int x,y;
	int rnd_choose_maptyp;
	int rnd_choose_player1_posX, rnd_choose_player1_posY, rnd_choose_player2_posX, rnd_choose_player2_posY, status;
	srand(time(NULL));
	//Create Map without players..
	//printf("Create Map without players..\n");
	for(y = 0; y < HEIGHT; y++) {
		for(x = 0; x < WIDTH; x++) {
			if(y == 0 || x == 0 || y == HEIGHT-1 || x == HEIGHT-1) {
				Game_Map[y][x] = wall;	//Mapedges always border..
				/*
					 wall
				wall Map wall
					 wall
				*/
			}	
			else {
				//Random Map:
				rnd_choose_maptyp = rand() % 100;
				if(rnd_choose_maptyp < 30) {
					//0-19 create new Wall ca. 2/10 Wall
					Game_Map[y][x] = wall;
				}
				else {
					//10-99 creae freespace ca. 8/10 freespace
					Game_Map[y][x] = freespace;
				}			
							
			}
		}
	}
	//printf("Map created..\n");
	//Add players to map..
	//Player1
	status == 0;
	do {
		rnd_choose_player1_posY = rand() % HEIGHT;
		rnd_choose_player1_posX = rand() % WIDTH; 
		//Do not spawn player1 at a edge-wall
		if(rnd_choose_player1_posY == 0 || rnd_choose_player1_posX == 0 || rnd_choose_player1_posY == HEIGHT-1 || 				rnd_choose_player1_posX == HEIGHT-1) {
			continue;	//New try..
		}	
		else {
			//Somewhere..
			//Do not spawn player1 at a wall
			//..check it..
			if(Game_Map[rnd_choose_player1_posY][rnd_choose_player1_posX] == wall) {
				continue;	//New try			
			}
			else {
				//Ok it could be a nice place..
				//Check neighborhood
				if(Game_Map[rnd_choose_player1_posY][rnd_choose_player1_posX-1] == freespace ||
					Game_Map[rnd_choose_player1_posY+1][rnd_choose_player1_posX] == freespace || 
					Game_Map[rnd_choose_player1_posY][rnd_choose_player1_posX+1] == freespace || 
					Game_Map[rnd_choose_player1_posY-1][rnd_choose_player1_posX] == freespace) {
					//Ok there is a little bit freespace, so spawn player1 here..
					Game_Map[rnd_choose_player1_posY][rnd_choose_player1_posX] = player1;
					status = 1;	//Ok
				}
			}
		}	
	}while(status == 0);
	show_map();
	//Player2
	status = 0;
	do {
		rnd_choose_player2_posY = rand() % HEIGHT;
		rnd_choose_player2_posX = rand() % WIDTH; 
		//Do not spawn player2 at a edge-wall
		if(rnd_choose_player2_posY == 0 || rnd_choose_player2_posX == 0 || rnd_choose_player2_posY == HEIGHT-1 || 				rnd_choose_player2_posX == HEIGHT-1) {
			continue;	//New try..
		}	
		else {
			//Somewhere..
			//Do not spawn player2 at a wall or on player1
			//..check it..
			if(Game_Map[rnd_choose_player2_posY][rnd_choose_player2_posX] == wall||Game_Map[rnd_choose_player2_posY][rnd_choose_player2_posX] == player1) {
				continue;	//New try			
			}
			else {
				//Ok it could be a nice place..
				//Is there a connection to player1?
				if(is_connected_to_player1(rnd_choose_player2_posY, rnd_choose_player2_posX) == 0) {
					//No..
					clear_pathfinder_track();
					//printf("Wrong player2 position..\n");
					continue;
				}
				else {
					//Yes
					//OK player2.. let's settle down :)
					clear_pathfinder_track();
					Game_Map[rnd_choose_player2_posY][rnd_choose_player2_posX] = player2;
					status = 1;
				}
				
			}
		}	
	}while(status == 0);
}

void show_map() {
	int y,x;
	for(y = 0; y < HEIGHT; y++) {
		for(x = 0; x < WIDTH; x++) {
			printf("%c",Game_Map[y][x]);		
		}
		printf("\n");
	}
}
