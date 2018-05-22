/*
 * VideoInterface.cpp
 *
 *  Created on: 21 May 2018
 *      Author: natha
 */

#include "VideoInterface.h"

VideoInterface::VideoInterface(int width, int height, int scale){
	this->width = width;
	this->height = height;
	this->scale = scale;
	this->viLA = BRESENHAM;
};

void VideoInterface::setColor(uint16_t color){
	this->color = color;
};

void VideoInterface::clear(uint16_t color){
	uint16_t tcol = this->color;
	this->setColor(color);
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			this->drawPixel(x, y);
		}
	}
	this->setColor(tcol);
};

void VideoInterface::setLineAlg(enum viLineAlg viLA){
	this->viLA = viLA;
};

void VideoInterface::drawLine(int x0, int y0, int x1, int y1){
	if(this->viLA == DDA) this->_drawLineDDA(x0, y0, x1, y1);
	if(this->viLA == BRESENHAM) this->_drawLineBRESENHAM(x0, y0, x1, y1);
};

void VideoInterface::_drawLineDDA(int x0, int y0, int x1, int y1){
	float x, y, dx, dy, step;

	dx = (float)abs(x1 - x0);
	dy = (float)abs(y1 - y0);

	step = (dx >= dy) ? dx : dy;

	dx = dx / step;
	dy = dy / step;

	x = x0;
	y = y0;

	for(int i = 0; i < step; i++){
		this->drawPixel(round(x), round(y));
		x += dx;
		y += dy;
	}
};

void VideoInterface::_drawLineBRESENHAM(int x0, int y0, int x1, int y1){
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x1 - x0;
	dy = y1 - y0;
	dx1 = fabs(dx);
	dy1 = fabs(dy);
	px = 2*dy1 - dx1;
	py = 2*dx1 - dy1;
	if(dy1 <= dx1 ){
		if(dx >= 0){
			x = x0;
			y = y0;
			xe = x1;
		}else{
			x = x1;
			y = y1;
			xe = x0;
		}
		this->drawPixel(x, y);
		for(i = 0; x < xe; i++){
			x += 1;
			if(px < 0){
				px += 2*dy1;
			}else{
				if((dx < 0 && dy < 0)||(dx > 0 && dy > 0)){
					y += 1;
				}else{
					y -= 1;
				}
				px = px + 2*(dy1 - dx1);
			}
			this->drawPixel(x, y);
		}
	}else{
		if(dy >= 0){
			x = x0;
			y = y0;
			ye = y1;
		}else{
			x = x1;
			y = y1;
			ye = y0;
		}
		this->drawPixel(x, y);
		for(i = 0;y < ye; i++){
			y += 1;
			if(py <= 0){
				py = py + 2*dx1;
			}else{
				if((dx < 0 && dy < 0)||(dx > 0 && dy > 0)){
					x += 1;
				}else{
					x -= 1;
				}
				py = py + 2*(dx1 - dy1);
			}
			this->drawPixel(x, y);
		}
	}
};
