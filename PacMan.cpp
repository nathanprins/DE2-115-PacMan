/*
 * PacMan.cpp
 *
 *  Created on: 23 May 2018
 *      Author: natha
 */

#include "PacMan.h"

PacMan::PacMan(int x, int y) : Entity(x, y) {
	this->width = 12;
	this->height = 12;
	this->curr_dir = DIR_NO_DIR;
	this->velocity = 50;
};


uint16_t PacMan::getColor(int frame, e_dir_t dir, int x, int y){
	if(x < 0 || x > this->width - 1)
		return NULL;
	if(y < 0 || y > this->height - 1)
		return NULL;

	switch(dir){
	case DIR_NO_DIR:
	case DIR_RIGHT:
		return this->bmp[frame][y][x] ? PACMAN_COLOR : NULL;
	case DIR_LEFT:
		return this->bmp[frame][y][this->width - 1 - x] ? PACMAN_COLOR : NULL;
	case DIR_DOWN:
		return this->bmp[frame][x][y] ? PACMAN_COLOR : NULL;
	case DIR_UP:
		return this->bmp[frame][x][this->height - 1 - y] ? PACMAN_COLOR : NULL;
	}
	return NULL;
}

static bool isBetween(int value, int low, int high){
	return (value >= low && value <= high);
}

void PacMan::_draw(VideoInterface* vi){
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

void PacMan::_update(int elapsedTime){
	this->last_frame = this->curr_frame;

	if(this->curr_dir != DIR_NO_DIR){
		if(this->frame_dir){
			if(this->curr_frame < 2){
				this->curr_frame++;
			}else{
				this->curr_frame--;
				this->frame_dir = 0;
			}
		}else{
			if(this->curr_frame > 0){
				this->curr_frame--;
			}else{
				this->curr_frame++;
				this->frame_dir = 1;
			}
		}
	}
	this->redraw = 1;
};
