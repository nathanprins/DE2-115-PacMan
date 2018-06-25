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
	this->dir = DIR_NO_DIR;
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
	for(int y = 0; y < this->width; y++){
		for(int x = 0; x < this->width; x++){
			if(!(isBetween(prev_x + x, this->x, this->x + this->width)&&
			   isBetween(prev_y + y, this->y, this->y + this->height)) ||
			   (this->bmp[this->lastFrame][y][x] && !this->bmp[this->frame][(this->y - prev_y) + y][(this->x - prev_x) + x])){

				if(this->prev_dir == DIR_RIGHT || this->prev_dir == DIR_NO_DIR)
					vi->drawPixel(this->prev_x + x - 2, this->prev_y + y - 2, 0);
				if(this->prev_dir == DIR_LEFT)
					vi->drawPixel(this->prev_x + (this->width - 1 - x) - 2, this->prev_y + y - 2, 0);
				if(this->prev_dir == DIR_DOWN)
					vi->drawPixel(this->prev_x + y - 2, this->prev_y + x - 2, 0);
				if(this->prev_dir == DIR_UP)
					vi->drawPixel(this->prev_x + y - 2, this->prev_y + (this->height - 1 - x) - 2, 0);
			}
		}
	}

	for(int y = 0; y < this->width; y++){
		for(int x = 0; x < this->width; x++){
			if(this->bmp[this->frame][y][x]){
				if(this->dir == DIR_RIGHT || this->dir == DIR_NO_DIR)
					vi->drawPixel(this->x + x - 2, this->y + y - 2, PACMAN_COLOR);
				if(this->dir == DIR_LEFT)
					vi->drawPixel(this->x + (this->width - 1 - x) - 2, this->y + y - 2, PACMAN_COLOR);
				if(this->dir == DIR_DOWN)
					vi->drawPixel(this->x + y - 2, this->y + x - 2, PACMAN_COLOR);
				if(this->dir == DIR_UP)
					vi->drawPixel(this->x + y - 2, this->y + (this->height - 1 - x) - 2, PACMAN_COLOR);
			}
		}
	}
};

void PacMan::_update(int elapsedTime){
	this->lastFrame = this->frame;

	if(this->dir != DIR_NO_DIR){
		if(this->frameDir){
			if(this->frame < 2){
				this->frame++;
			}else{
				this->frame--;
				this->frameDir = 0;
			}
		}else{
			if(this->frame > 0){
				this->frame--;
			}else{
				this->frame++;
				this->frameDir = 1;
			}
		}
	}
	this->redraw = 1;
};
