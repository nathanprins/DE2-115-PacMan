/*
 * PacMan.h
 *
 *  Created on: 2 May 2018
 *      Author: natha
 */

#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include "ControllerInterface.h"
#include "VideoInterface.h"
#include "PacMan.h"

#define H(x) (h*8)+x
#define V(y) (v*8)+y
#define SHORTEST(a, b) (a > b ? b : a)

#define MAP_OFFSET_X 76
#define MAP_OFFSET_Y 12

typedef enum {
	em, pd,
	c1, c2, c3, c4,
	ph, pv,
	tu, td, tl, tr,
	cu, cd, cl, cr
} map_item_t;

typedef enum {
	LEVEL_START,
	LEVEL_RUN
} game_state_t;

class Game {
	public:
		Game(ControllerInterface* control, VideoInterface* video);
		void update(int elapsedTime);
		void draw();
	private:
		void drawMap();
		void setInSquare(Entity* en, int xs, int ys);
		void updateMovement(Entity* en, int elapsedTime);
		void distanceToWalls(Entity* en, int* up, int* down, int* left, int* right);
		bool walkable(map_item_t item);
		ControllerInterface* ci;
		VideoInterface* vi;
		PacMan player = PacMan(8, 8);
		game_state_t state = LEVEL_START;
		uint8_t simpleMap = 0;
		int points = 0;
		map_item_t map[27][21] = {
			{c1,ph,ph,ph,ph,ph,ph,ph,ph,ph,td,ph,ph,ph,ph,ph,ph,ph,ph,ph,c2},
			{pv,pd,pd,pd,pd,pd,pd,pd,pd,pd,pv,pd,pd,pd,pd,pd,pd,pd,pd,pd,pv},
			{pv,pd,c1,ph,c2,pd,c1,ph,c2,pd,pv,pd,c1,ph,c2,pd,c1,ph,c2,pd,pv},
			{pv,em,pv,em,pv,pd,pv,em,pv,pd,pv,pd,pv,em,pv,pd,pv,em,pv,em,pv},
			{pv,pd,c3,ph,c4,pd,c3,ph,c4,pd,cu,pd,c3,ph,c4,pd,c3,ph,c4,pd,pv},
			{pv,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pv},
			{pv,pd,c1,ph,c2,pd,cd,pd,c1,ph,ph,ph,c2,pd,cd,pd,c1,ph,c2,pd,pv},
			{pv,pd,c3,ph,c4,pd,pv,pd,c3,ph,td,ph,c4,pd,pv,pd,c3,ph,c4,pd,pv},
			{pv,pd,pd,pd,pd,pd,pv,pd,pd,pd,pv,pd,pd,pd,pv,pd,pd,pd,pd,pd,pv},
			{c3,ph,ph,ph,c2,pd,tr,ph,cl,em,cu,em,cr,ph,tl,pd,c1,ph,ph,ph,c4},
			{em,em,em,em,pv,pd,pv,em,em,em,em,em,em,em,pv,pd,pv,em,em,em,em},
			{em,em,em,em,pv,pd,pv,em,c1,cl,em,cr,c2,em,pv,pd,pv,em,em,em,em},
			{cr,ph,ph,ph,c4,pd,cu,em,pv,em,em,em,pv,em,cu,pd,c3,ph,ph,ph,cl},
			{em,em,em,em,em,pd,em,em,pv,em,em,em,pv,em,em,em,em,em,em,em,em},
			{cr,ph,ph,ph,c2,pd,cd,em,c3,ph,ph,ph,c4,em,cd,pd,c1,ph,ph,ph,cl},
			{em,em,em,em,pv,pd,pv,em,em,em,em,em,em,em,pv,em,pv,em,em,em,em},
			{em,em,em,em,pv,pd,pv,em,c1,ph,ph,ph,c2,em,pv,em,pv,em,em,em,em},
			{c1,ph,ph,ph,c4,pd,cu,em,c3,ph,td,ph,c4,em,cu,pd,c3,ph,ph,ph,c2},
			{pv,pd,pd,pd,pd,pd,pd,pd,pd,pd,pv,pd,pd,pd,pd,pd,pd,pd,pd,pd,pv},
			{pv,pd,cr,ph,c2,pd,cr,ph,cl,pd,cu,pd,cr,ph,cl,pd,c1,ph,cl,pd,pv},
			{pv,pd,pd,pd,pv,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pv,pd,pd,pd,pv},
			{tr,ph,c2,pd,pv,pd,cd,pd,c1,ph,ph,ph,c2,pd,cd,pd,pv,pd,c1,ph,tl},
			{tr,ph,c4,pd,cu,pd,pv,pd,c3,ph,td,ph,c4,pd,pv,pd,cu,pd,c3,ph,tl},
			{pv,pd,pd,pd,pd,pd,pv,pd,pd,pd,pv,pd,pd,pd,pv,pd,pd,pd,pd,pd,pv},
			{pv,pd,cr,ph,ph,ph,tu,ph,cl,pd,cu,pd,cr,ph,tu,ph,ph,ph,cl,pd,pv},
			{pv,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pd,pv},
			{c3,ph,ph,ph,ph,ph,ph,ph,ph,ph,ph,ph,ph,ph,ph,ph,ph,ph,ph,ph,c4}
		};

};

#endif /* GAME_H_ */
