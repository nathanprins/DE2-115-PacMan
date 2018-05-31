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

void VGA::_internalDrawPixel(int x, int y, uint16_t color){
	volatile short* pbuff = this->pbuffer;

	int offset = (y << 9) + x;
	*(pbuff + offset) = (short)color;
};
