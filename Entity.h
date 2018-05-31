/*
 * Entity.h
 *
 *  Created on: 23 May 2018
 *      Author: natha
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "VideoInterface.h"
#include <stdio.h>
#include <math.h>

typedef enum E_DIR {
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_NO_DIR
} e_dir_t;

class Entity {
	public:
		Entity(int x, int y);
		void draw(VideoInterface* vi);
		void update(int elapsedTime); // time is ms
		void setDir(e_dir_t dir);
		bool hasCollided(Entity* with);
		void setPos(int x, int y);
		int getVelocity();
		int getX();
		int getY();
		e_dir_t getDir();
	protected:
		virtual void _draw(VideoInterface* vi) = 0;
		virtual void _update(int elapsedTime) = 0;
		int x;
		int y;
		int prev_x;
		int prev_y;
		int width;
		int height;
		int velocity; // pixels per second
		uint8_t redraw = 1;
		e_dir_t dir = DIR_NO_DIR;
		e_dir_t prev_dir;
};

#endif /* ENTITY_H_ */
