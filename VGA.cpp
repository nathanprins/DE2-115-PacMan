/*
 * VGA.cpp
 *
 *  Created on: 21 May 2018
 *      Author: natha
 */

#include "VGA.h"

VGA::VGA(short* pixel_buffer, int width, int height, int scale) : VideoInterface(width, height, scale) {
	this->pbuffer = pixel_buffer;
};

void VGA::drawPixel(int x, int y){
	volatile short* pbuff = this->pbuffer;

	int offset = (y << 9) + x;
	*(pbuff + offset) = (short)this->color;
};
