/*
 * Ghost.cpp
 *
 *  Created on: 28 Jun 2018
 *      Author: natha
 */

#include "Ghost.h"

Ghost::Ghost(uint16_t color) : Entity(8, 8) {
	this->color = color;
	this->width = 12;
	this->height = 12;
	this->curr_dir = DIR_NO_DIR;
	this->velocity = 50;
};

static bool withinBounds(int x, int y, int xmin, int xmax, int ymin, int ymax){
	return (x >= xmin && x <= xmax) && (y >= ymin && y <= ymax);
}


uint16_t Ghost::getColor(int frame, e_dir_t dir, int x, int y){
	if(x < 0 || x > this->width - 1)
		return 0;
	if(y < 0 || y > this->height - 1)
		return 0;

	if(bmp[frame][y][x])
		return color;

	for(int eyenum = 0; eyenum < 2; eyenum++){
		if(withinBounds(x, y, 1 + (eyenum * 6), 4 + (eyenum * 6), 3, 6)){
			x -= 1 + (eyenum * 6);
			y -= 3;
			switch(dir){
			case DIR_NO_DIR:
			case DIR_RIGHT:
				if(this->eye[y][x])
					return RGB565(255, 255, 255);
				break;
			case DIR_LEFT:
				if(this->eye[y][3 - x])
					return RGB565(255, 255, 255);
				break;
			case DIR_DOWN:
				if(this->eye[x][y])
					return RGB565(255, 255, 255);
				break;
			case DIR_UP:
				if(this->eye[x][3 - y])
					return RGB565(255, 255, 255);
				break;
			}

		}
	}


	return 0;
}

void Ghost::setJailed(bool jailed){
	this->jailed = jailed;
};

bool Ghost::isJailed(){
	return this->jailed;
};

void Ghost::_draw(VideoInterface* vi){
	uint16_t color1;
	uint16_t color2;
	for(int y = 0; y < this->width; y++){
		for(int x = 0; x < this->width; x++){
			color1 = getColor(this->last_frame, this->prev_dir, x, y);
			color2 = getColor(this->curr_frame, this->curr_dir, (this->prev_x - this->x) + x, (this->prev_y - this->y) + y);
			if(color1 != color2)
				vi->drawPixel(this->prev_x + x - 2, this->prev_y + y - 2, 0);
		}
	}

	for(int y = 0; y < this->width; y++){
		for(int x = 0; x < this->width; x++){
			color1 = getColor(this->curr_frame, this->curr_dir, x, y);
			if(color1 != NULL)
				vi->drawPixel(this->x + x - 2, this->y + y - 2, color1);
		}
	}
};

void Ghost::_update(int elapsedTime){
	if(curr_dir == DIR_NO_DIR){
		curr_dir = DIR_RIGHT;
	}

	this->last_frame = this->curr_frame;

	if(this->curr_dir != DIR_NO_DIR){
		curr_frame = curr_frame ? 0 : 1;
	}
	this->redraw = 1;
};
