/*
 * Entity.cpp
 *
 *  Created on: 23 May 2018
 *      Author: natha
 */

#include "Entity.h"

Entity::Entity(int x, int y) : x(x), y(y) {

};

void Entity::update(int elapsedTime){
	this->prev_dir = this->curr_dir;
	this->prev_x = this->x;
	this->prev_y = this->y;
	this->_update(elapsedTime);
};

void Entity::draw(VideoInterface* vi){
	if(this->redraw){
		this->_draw(vi);
		this->redraw = 0;
	}
}

void Entity::setDir(e_dir_t dir){
	this->curr_dir = dir;
	this->redraw = 1;
};

void Entity::setPos(int x, int y){
	this->x = x;
	this->y = y;
	this->redraw = 1;
};

int Entity::getVelocity(){
	return velocity;
};

int Entity::getX(){
	return x;
};

int Entity::getY(){
	return y;
};

e_dir_t Entity::getDir(){
	return curr_dir;
};
