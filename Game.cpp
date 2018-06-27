/*
 * PacMan.cpp
 *
 *  Created on: 2 May 2018
 *      Author: natha
 */

#include "Game.h"

Game::Game(ControllerInterface* control, VideoInterface* video) : ci(control), vi(video){
	vi->clear(0);

	setInSquare(&player, 10, 15);
};

void Game::update(int elapsedTime){
<<<<<<< HEAD
<<<<<<< HEAD
	switch(state){
//		case GAME_INIT: {
//			printf("Game: Initializing\n\r");
//			// Count pacdots in on map
//			for(int h = 0; h < 21; h++){
//				for(int v = 0; v < 27; v++){
//					if(map[v][h] == pd)
//						max_pds++;
//				}
//			}
//			printf("Max PDS: %d \n\r", max_pds);
//			state = LEVEL_START;
//			break;
//		}
		case LEVEL_START: {
			printf("Game: Level started\n\r");

			setInSquare(&player, 10, 20);

			state = LEVEL_FIRST_DRAW;
			break;
		}
		case LEVEL_RUN: {
			button_t button = ci->getActiveButton();

			e_dir_t next = buttonToDir(button);
			if(next != DIR_NO_DIR){
				printf("press");
				player.setNextDir(next);
			}
=======
	if(state == LEVEL_RUN){

		int up, down, left, right;
		distanceToWalls(&player, &up, &down, &left, &right);

		switch(ci->getActiveButton()){
			case BUTTON_UP: if(up) player.setDir(DIR_UP); break;
			case BUTTON_DOWN: if(down) player.setDir(DIR_DOWN); break;
			case BUTTON_LEFT: if(left) player.setDir(DIR_LEFT); break;
			case BUTTON_RIGHT: if(right) player.setDir(DIR_RIGHT); break;
			default: break;
		}
>>>>>>> parent of fc53817... Added working score count
=======
	if(state == LEVEL_RUN){
		button_t button = ci->getActiveButton();

		e_dir_t next = buttonToDir(button);
		if(next != DIR_NO_DIR)
			player.setNextDir(next);
>>>>>>> parent of 7c1199f... Added gamestates

		updateMovement(&player, elapsedTime);

<<<<<<< HEAD
<<<<<<< HEAD
			int xs = player.getX() / 8.0;
			int ys = player.getY() / 8.0;
			if(map[ys][xs] == pd){
				cur_score += PAC_DOT_POINTS;
				cur_pds++;
				map[ys][xs] = ed;
			}
//			if(cur_pds >= max_pds){
//				state = LEVEL_RESET;
//			}
			break;
=======
		int xs = player.getX() / 8.0;
		int ys = player.getY() / 8.0;
		if(map[ys][xs] == pd){
			points += 100;
			printf("Points: %d \n", points);
			map[ys][xs] = em;
>>>>>>> parent of fc53817... Added working score count
=======
		int xs = player.getX() / 8.0;
		int ys = player.getY() / 8.0;
		if(map[ys][xs] == pd){
			score += PAC_DOT_POINTS;
			map[ys][xs] = em;
>>>>>>> parent of 7c1199f... Added gamestates
		}
	}
};

void Game::setInSquare(Entity* en, int xs, int ys){
	en->setPos(xs*8, ys*8);
};

void Game::distanceToWalls(Entity* en, int* up, int* down, int* left, int* right){
	int x = en->getX();
	int y = en->getY();
	int xSq = en->getX() / 8.0;
	int ySq = en->getY() / 8.0;

	int upSq = 0, downSq = 0, leftSq = 0, rightSq = 0;
	if(x % 8 == 0){
		while(walkable(map[ySq - upSq - 1][xSq])) 	 upSq++;
		while(walkable(map[ySq + downSq + 1][xSq]))  downSq++;
	}
	if(y % 8 == 0){
		while(walkable(map[ySq][xSq - leftSq - 1]))  leftSq++;
		while(walkable(map[ySq][xSq + rightSq + 1])) rightSq++;
	}

	int xPixel = (xSq * 8) - x;
	int yPixel = (ySq * 8) - y;

	*up 	= (upSq * 8) - yPixel;
	*down 	= (downSq * 8) + yPixel;
	*left 	= (leftSq * 8) - xPixel;
	*right 	= (rightSq * 8) + xPixel;
};

void Game::updateMovement(Entity* en, int elapsedTime){
	en->update(elapsedTime);

	int up, down, left, right;
	distanceToWalls(en, &up, &down, &left, &right);

	float timeFraction = (float)elapsedTime / 1000;
	int walk = roundf(timeFraction * en->getVelocity());

	switch(en->getDir()){
		case DIR_UP: 	en->setPos(en->getX(), en->getY() - SHORTEST(walk, up)); break;
		case DIR_DOWN: 	en->setPos(en->getX(), en->getY() + SHORTEST(walk, down)); break;
		case DIR_LEFT: 	en->setPos(en->getX() - SHORTEST(walk, left), en->getY()); break;
		case DIR_RIGHT: en->setPos(en->getX() + SHORTEST(walk, right), en->getY()); break;
		default: break;
	};
};

bool Game::walkable(map_item_t item){
	return (item == em || item == pd);
};

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> parent of 1c28ea3... Save before revert
bool Game::getCharPixel(char c, int x, int y){
	if(x < 0 || x > 7)
		return false;
	if(y < 0 || y > 7)
		return false;

	if(c >= 'A' && c <= 'Z'){
		return bmp_letters[c - 'A'][y][x];
	}
	if(c >= '0' && c <= '9'){
		return bmp_numbers[c - '0'][y][x];
	}
	if(c == '-'){
		const bool dash[7][7] = {
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0}
		};
		return dash[y][x];
=======
void Game::draw(){
	switch(state){
		case LEVEL_START:
			vi->setOffset(MAP_OFFSET_X, MAP_OFFSET_Y);
			drawMap();
			vi->resetOffset();
			state = LEVEL_RUN;
			break;
		case LEVEL_RUN:
			vi->setOffset(MAP_OFFSET_X, MAP_OFFSET_Y);
			player.draw(vi);
			vi->resetOffset();
			break;
>>>>>>> parent of fc53817... Added working score count
	}
	if(c == '!'){
		const bool excl[7][7] = {
			{0,0,0,1,1,1,0},
			{0,0,0,1,1,1,0},
			{0,0,1,1,1,0,0},
			{0,0,1,1,0,0,0},
			{0,0,1,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,0,0,0,0,0}
		};
		return excl[y][x];
=======
void Game::draw(){
	switch(state){
		case LEVEL_START:
			setInSquare(&player, 10, 20);
			drawMap();
			drawScoreText();
			drawScore();
			state = LEVEL_RUN;
			break;
		case LEVEL_RUN:
			vi->setOffset(MAP_OFFSET_X, MAP_OFFSET_Y);
			player.draw(vi);
			vi->resetOffset();

			if(score != old_score)
				drawScore();
			break;
>>>>>>> parent of 7c1199f... Added gamestates
	}
};

<<<<<<< HEAD
<<<<<<< HEAD
void Game::drawChar(int x, int y, char c){
=======
void Game::drawChar(int x, int y, const bool bmp[7][7]){
>>>>>>> parent of 7c1199f... Added gamestates
	for(int py = 0; py < 7; py++){
		for(int px = 0; px < 7; px++){
			if(bmp[py][px]){
				vi->drawPixel(x + px, y + py);
			}
		}
	}
};

void Game::drawText(int x, int y, char *text){
	int place = 0;

	char c = text[place];
	while(c){
		if(c >= 'A' && c <= 'Z'){
			drawChar((place * 8) + x, y, bmp_letters[c - 'A']);
		}
		if(c >= '0' && c <= '9'){
			drawChar((place * 8) + x, y, bmp_numbers[c - '0']);
		}
		if(c == '-'){
			const bool dash[7][7] = {
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{1,1,1,1,1,1,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0}
			};
			drawChar((place * 8) + x, y, dash);
		}
		if(c == '!'){
			const bool dash[7][7] = {
				{0,0,0,1,1,1,0},
				{0,0,0,1,1,1,0},
				{0,0,1,1,1,0,0},
				{0,0,1,1,0,0,0},
				{0,0,1,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,1,0,0,0,0,0}
			};
			drawChar((place * 8) + x, y, dash);
		}

		c = text[++place];
	}
	printf("Len: %d \n\r", place);
};

void Game::drawScoreText(){
	vi->setOffset(SCORE_OFFSET_X, SCORE_OFFSET_Y);
	vi->setColor(SCORE_TEXT_COLOR);

	drawText(0, 0, "HI-SCORE");
	drawText(8 , 32, "1UP");
//	drawText(8 , 32 * 2, "2UP");

	vi->resetOffset();
};

void Game::drawScore(){
	vi->setOffset(SCORE_OFFSET_X, SCORE_OFFSET_Y);
	vi->setColor(SCORE_COLOR);

	char text[8] = { 0 };

	sprintf(text, "%*d", 7, score);

	if(score > high_score){
		high_score = score;
	}

	vi->drawRect(0, 16, 7 * 8, 7, 0);
	drawText(0, 16, text);

	vi->drawRect(0, 48, 7 * 8, 7, 0);
	drawText(0, 48, text);

	old_score = score;

	vi->resetOffset();
};

=======
>>>>>>> parent of fc53817... Added working score count
void Game::drawMap(){
	for(int v = 0; v < 27; v++){
		for(int h = 0; h < 21; h++){
			if(simpleMap){ // for testing
				if(!walkable(map[v][h]))
					vi->drawRect(H(0), V(0), 8, 8, RGB565(0, 74, 241));
			}else{
				switch(map[v][h]){
					case pd:
						vi->drawRect(H(3), V(3), 2, 2, RGB565(255, 165, 0));
						break;
					case c1:
						vi->drawLine(H(4), V(2), H(7), V(2), RGB565(0, 74, 241));
						vi->drawLine(H(2), V(4), H(2), V(7), RGB565(0, 74, 241));
						vi->drawPixel(H(3), V(3), RGB565(0, 74, 241));
						vi->drawLine(H(6), V(5), H(7), V(5), RGB565(0, 74, 241));
						vi->drawLine(H(5), V(6), H(5), V(7), RGB565(0, 74, 241));
						break;
					case c2:
						vi->drawLine(H(0), V(2), H(3), V(2), RGB565(0, 74, 241));
						vi->drawLine(H(5), V(4), H(5), V(7), RGB565(0, 74, 241));
						vi->drawPixel(H(4), V(3), RGB565(0, 74, 241));
						vi->drawLine(H(0), V(5), H(1), V(5), RGB565(0, 74, 241));
						vi->drawLine(H(2), V(5), H(2), V(7), RGB565(0, 74, 241));
						break;
					case c3:
						vi->drawLine(H(2), V(0), H(2), V(3), RGB565(0, 74, 241));
						vi->drawLine(H(4), V(5), H(7), V(5), RGB565(0, 74, 241));
						vi->drawPixel(H(3), V(4), RGB565(0, 74, 241));
						vi->drawLine(H(5), V(0), H(5), V(1), RGB565(0, 74, 241));
						vi->drawLine(H(6), V(2), H(7), V(2), RGB565(0, 74, 241));
						break;
					case c4:
						vi->drawLine(H(5), V(0), H(5), V(3), RGB565(0, 74, 241));
						vi->drawLine(H(0), V(5), H(3), V(5), RGB565(0, 74, 241));
						vi->drawPixel(H(4), V(4), RGB565(0, 74, 241));
						vi->drawLine(H(2), V(0), H(2), V(1), RGB565(0, 74, 241));
						vi->drawLine(H(0), V(2), H(1), V(2), RGB565(0, 74, 241));
						break;
					case ph:
						vi->drawLine(H(0), V(2), H(7), V(2), RGB565(0, 74, 241));
						vi->drawLine(H(0), V(5), H(7), V(5), RGB565(0, 74, 241));
						break;
					case pv:
						vi->drawLine(H(2), V(0), H(2), V(7), RGB565(0, 74, 241));
						vi->drawLine(H(5), V(0), H(5), V(7), RGB565(0, 74, 241));
						break;
					case tu:
						vi->drawLine(H(0), V(5), H(7), V(5), RGB565(0, 74, 241));
						vi->drawLine(H(0), V(2), H(1), V(2), RGB565(0, 74, 241));
						vi->drawLine(H(6), V(2), H(7), V(2), RGB565(0, 74, 241));
						vi->drawLine(H(2), V(0), H(2), V(1), RGB565(0, 74, 241));
						vi->drawLine(H(5), V(0), H(5), V(1), RGB565(0, 74, 241));
						break;
					case td:
						vi->drawLine(H(0), V(2), H(7), V(2), RGB565(0, 74, 241));
						vi->drawLine(H(0), V(5), H(1), V(5), RGB565(0, 74, 241));
						vi->drawLine(H(6), V(5), H(7), V(5), RGB565(0, 74, 241));
						vi->drawLine(H(2), V(6), H(2), V(7), RGB565(0, 74, 241));
						vi->drawLine(H(5), V(6), H(5), V(7), RGB565(0, 74, 241));
						break;
					case tl:
						vi->drawLine(H(5), V(0), H(5), V(7), RGB565(0, 74, 241));
						vi->drawLine(H(2), V(0), H(2), V(1), RGB565(0, 74, 241));
						vi->drawLine(H(0), V(2), H(1), V(2), RGB565(0, 74, 241));
						vi->drawLine(H(0), V(5), H(1), V(5), RGB565(0, 74, 241));
						vi->drawLine(H(2), V(6), H(2), V(7), RGB565(0, 74, 241));
						break;
					case tr:
						vi->drawLine(H(2), V(0), H(2), V(7), RGB565(0, 74, 241));
						vi->drawLine(H(5), V(0), H(5), V(1), RGB565(0, 74, 241));
						vi->drawLine(H(6), V(2), H(7), V(2), RGB565(0, 74, 241));
						vi->drawLine(H(6), V(5), H(7), V(5), RGB565(0, 74, 241));
						vi->drawLine(H(5), V(6), H(5), V(7), RGB565(0, 74, 241));
						break;
					case cu:
						vi->drawLine(H(2), V(0), H(2), V(3), RGB565(0, 74, 241));
						vi->drawLine(H(5), V(0), H(5), V(3), RGB565(0, 74, 241));
						vi->drawLine(H(3), V(4), H(4), V(4), RGB565(0, 74, 241));
						break;
					case cd:
						vi->drawLine(H(2), V(4), H(2), V(7), RGB565(0, 74, 241));
						vi->drawLine(H(5), V(4), H(5), V(7), RGB565(0, 74, 241));
						vi->drawLine(H(3), V(3), H(4), V(3), RGB565(0, 74, 241));
						break;
					case cl:
						vi->drawLine(H(0), V(2), H(3), V(2), RGB565(0, 74, 241));
						vi->drawLine(H(0), V(5), H(3), V(5), RGB565(0, 74, 241));
						vi->drawLine(H(4), V(3), H(4), V(4), RGB565(0, 74, 241));
						break;
					case cr:
						vi->drawLine(H(4), V(2), H(7), V(2), RGB565(0, 74, 241));
						vi->drawLine(H(4), V(5), H(7), V(5), RGB565(0, 74, 241));
						vi->drawLine(H(3), V(3), H(3), V(4), RGB565(0, 74, 241));
						break;
					default: break;
				}
			}

		}
	}
};

