/*
 * PacMan.cpp
 *
 *  Created on: 2 May 2018
 *      Author: natha
 */

#include "Game.h"


Game::Game(ControllerInterface* control, VideoInterface* video) : ci(control), vi(video){
	vi->clear(0);
};

static e_dir_t buttonToDir(button_t button){
	switch(button){
		case BUTTON_UP: 	return DIR_UP;
		case BUTTON_DOWN: 	return DIR_DOWN;
		case BUTTON_LEFT: 	return DIR_LEFT;
		case BUTTON_RIGHT: 	return DIR_RIGHT;
		default: 			return DIR_NO_DIR;
	}
}

static double distanceBetweenEntities(Entity *en1, Entity *en2){
	double x1 = (double)en1->getX();
	double y1 = (double)en1->getY();
	double x2 = (double)en2->getX();
	double y2 = (double)en2->getY();
	double ans = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	printf("Distance: %f \n\r", ans);
	return ans;
}

void Game::update(int elapsedTime){
	button_t button = ci->getActiveButton();

	if(button == BUTTON_RESET){
		state = LEVEL_RESET;
	}
	switch(state){
		case GAME_INIT: {
			printf("Game: Initializing\n\r");
			// Count pacdots in on map
			for(int h = 0; h < 21; h++){
				for(int v = 0; v < 27; v++){
					if(map[v][h] == pd)
						max_pds++;
				}
			}
			printf("Max PacDot count in maze: %d \n\r", max_pds);

			state = HOMESCREEN_INIT; // FIRST DRAW
			break;
		}
		case HOMESCREEN: {
			if(button == BUTTON_ENTER){
				state = LEVEL_START;
			}
//			state = LEVEL_START;
			break;
		}
		case LEVEL_START: {
			printf("Game: Level started\n\r");

			// Spawn in field
			setInSquare(&player, 10, 20);
			unJail(&ghosts[0]);

			// Jailed
			jail(&ghosts[1]);
			jail(&ghosts[2]);
			jail(&ghosts[3]);

			old_hscore = 0; // redraw
			time = 0;

			state = LEVEL_FIRST_DRAW;
			break;
		}
		case LEVEL_RUN: {
			time += elapsedTime;

			e_dir_t next = buttonToDir(button);
			if(next != DIR_NO_DIR){
				printf("press '%d' \n\r", next);
				player.setNextDir(next);
			}

			updateMovement(&player, elapsedTime);

			for(int g = 0; g < 4; g++){
				if(distanceBetweenEntities(&player, &ghosts[g]) < 10.0){
					state = LEVEL_DIED;
				}
				if(!ghosts[g].isJailed())
					randomWalkAlgorithm(&ghosts[g]);
				updateMovement(&ghosts[g], elapsedTime);
			}

			for(int g = 1; g < 4; g++){
				if(time > (10000 * g) && ghosts[g].isJailed()) // each 10 seconds release new ghost
					unJail(&ghosts[g]);
			}


			int xs = player.getX() / 8.0;
			int ys = player.getY() / 8.0;
			if(map[ys][xs] == pd){
				cur_score += PAC_DOT_POINTS;
				cur_pds++;
				map[ys][xs] = ed;
			}
			if(cur_pds >= max_pds){
				state = LEVEL_RESET;
			}
			break;
		}
		case LEVEL_DIED: {
			printf("Died \n\r");
			cur_score = 0;
			state = LEVEL_RESET;
			break;
		}
		case LEVEL_RESET: {
			printf("Game: Level reset\n\r");
			for(int h = 0; h < 21; h++){
				for(int v = 0; v < 27; v++){
					if(map[v][h] == ed)
						map[v][h] = pd;
				}
			}
			cur_pds = 0;
			player.setCurrDir(DIR_NO_DIR);
			updateMovement(&player, 0);
			state = LEVEL_START;
			break;
		}
	}
};

static void resetAvailable(e_dir_t *a){
	for(int i = 0; i < 4; i++)
		a[i] = DIR_NO_DIR;
};
static void appendAvailable(e_dir_t *a, e_dir_t dir){
	for(int i = 0; i < 4; i++){
		if(a[i] == DIR_NO_DIR){
			a[i] = dir;
			return;
		}
	}
};
static e_dir_t chooseFromAvailable(e_dir_t *a){
	int count = 0;
	for(int i = 0; i < 4; i++){
		if(a[i] != DIR_NO_DIR){
			count++;
		}
	}
	if(count == 0)
		return DIR_NO_DIR;

	return a[rand() % count];
};

void Game::randomWalkAlgorithm(Ghost *g){
	int xSq = g->getX() / 8.0;
	int ySq = g->getY() / 8.0;

	e_dir_t avail[4];
	if(g->getCurrDir() == DIR_NO_DIR){
		resetAvailable(avail);
		if(walkable(map[ySq - 1][xSq]))
			appendAvailable(avail, DIR_UP);
		if(walkable(map[ySq][xSq + 1]))
			appendAvailable(avail, DIR_RIGHT);
		if(walkable(map[ySq + 1][xSq]))
			appendAvailable(avail, DIR_DOWN);
		if(walkable(map[ySq][xSq - 1]))
			appendAvailable(avail, DIR_LEFT);

		g->setNextDir(chooseFromAvailable(avail));
	}

	e_dir_t going = g->getCurrDir();
	e_dir_t ignore;

	int x_offset = 0;
	int y_offset = 0;
	switch(going){
	case DIR_UP:
		if(walkable(map[ySq - 1][xSq]))
			y_offset = -1;
		ignore = DIR_DOWN;
		break;
	case DIR_RIGHT:
		if(walkable(map[ySq][xSq + 1]))
			x_offset = 1;
		ignore = DIR_LEFT;
		break;
	case DIR_DOWN:
		if(walkable(map[ySq + 1][xSq]))
			y_offset = 1;
		ignore = DIR_UP;
		break;
	case DIR_LEFT:
		if(walkable(map[ySq][xSq - 1]))
			x_offset = -1;
		ignore = DIR_RIGHT;
		break;
	}

	resetAvailable(avail);

	if(ignore != DIR_UP 	&& walkable(map[ySq + y_offset - 1][xSq + x_offset]))
		appendAvailable(avail, DIR_UP);

	if(ignore != DIR_RIGHT 	&& walkable(map[ySq + y_offset][xSq + x_offset + 1]))
		appendAvailable(avail, DIR_RIGHT);

	if(ignore != DIR_DOWN 	&& walkable(map[ySq + y_offset + 1][xSq + x_offset]))
		appendAvailable(avail, DIR_DOWN);

	if(ignore != DIR_LEFT	&& walkable(map[ySq + y_offset][xSq + x_offset - 1]))
		appendAvailable(avail, DIR_LEFT);

	g->setNextDir(chooseFromAvailable(avail));
};


void Game::draw(){
	switch(state){
		case HOMESCREEN_INIT: {
			drawHomescreen();
			state = HOMESCREEN;
			break;
		}
		case HOMESCREEN: {

			break;
		}
		case LEVEL_FIRST_DRAW: {
			printf("Game: First draw\n\r");
			vi->clear(0);
			drawMap();
			drawScoreText();
			drawScore();
			state = LEVEL_RUN;
			break;
		}
		case LEVEL_RUN: {
			vi->setOffset(MAP_OFFSET_X, MAP_OFFSET_Y);
			player.draw(vi);

			for(int g = 0; g < 4; g++){
				int xSq = ghosts[g].getX() / 8.0;
				int ySq = ghosts[g].getY() / 8.0;
				for(int mapy = -2; mapy < 3; mapy++){
					for(int mapx = -2; mapx < 3; mapx++){
						if(map[ySq + mapy][xSq + mapx] == pd){
							vi->drawRect(((xSq + mapx) * 8) + 3, ((ySq + mapy) * 8) + 3, 2, 2, PAC_DOT_COLOR);
						}
					}
				}
				ghosts[g].draw(vi);
			}

			vi->resetOffset();

			if(cur_score != old_score)
				drawScore();

			break;
		}
	}
};

void Game::unJail(Ghost *g){
	g->setJailed(false);
	setInSquare(g, 10, 10);
}
void Game::jail(Ghost *g){
	g->setJailed(true);
	setInSquare(g, 10, 13);
}

void Game::drawHomescreen(){
	vi->setColor(RGB565(255, 165, 0));
	drawText(70, 100, "PRESS ENTER TO START!");
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

bool Game::distanceToEntry(Entity* en, int* distance){
	int x = en->getX();
	int y = en->getY();
	int xSq = en->getX() / 8.0;
	int ySq = en->getY() / 8.0;

	e_dir_t curr_dir = en->getCurrDir();
	e_dir_t next_dir = en->getNextDir();

	int walk_x = 0, walk_y = 0;
	int check_x = 0, check_y = 0;

	switch(curr_dir){
	case DIR_UP: 	walk_y = -1; break;
	case DIR_DOWN: 	walk_y = 1; break;
	case DIR_LEFT: 	walk_x = -1; break;
	case DIR_RIGHT: walk_x = 1; break;
	default: return false;
	}

	switch(next_dir){
	case DIR_UP: 	check_y = -1; break;
	case DIR_DOWN: 	check_y = 1; break;
	case DIR_LEFT: 	check_x = -1; break;
	case DIR_RIGHT: check_x = 1; break;
	default: return false;
	}

	while(walkable(map[ySq][xSq])){ // walk current direction per square
		if(walkable(map[ySq + check_y][xSq + check_x])){ // check per walkable square if it's walkable in the direction we wish to go
			switch(next_dir){
			case DIR_UP:
			case DIR_DOWN:
				*distance = abs((xSq * 8) - x);
				break;
			case DIR_LEFT:
			case DIR_RIGHT:
				*distance = abs((ySq * 8) - y);
				break;
			default: return false;
			}
			return true;
		}
		xSq += walk_x;
		ySq += walk_y;
	}

	return false;
}


void Game::updateMovement(Entity* en, int elapsedTime){
	en->update(elapsedTime);

	// Calculate maximum travelable distance
	float timeFraction = (float)elapsedTime / 1000;
	int walk = roundf(timeFraction * en->getVelocity());

	int up, down, left, right;
	distanceToWalls(en, &up, &down, &left, &right);

	if(en->getNextDir() != en->getCurrDir()){
		e_dir_t next = en->getNextDir();

		// Check if next direction is valid through maximum distance in that direction
		bool valid = false;
		switch(next){
		case DIR_UP: valid = up > 0; break;
		case DIR_DOWN: valid = down > 0; break;
		case DIR_LEFT: valid = left > 0; break;
		case DIR_RIGHT: valid = right > 0; break;
		default: break;
		}

		if(valid){
			// If distance in next direction isn't zero then there is a free path
			en->setCurrDir(next);
		}else{
			// Or if the distance to the next available entry is less then the walk distance
			// then trim the walk distance so the character is exactly in front on next update
			int distance;
			if(distanceToEntry(en, &distance)){
				if(walk > distance){
					walk = distance;
				}
			}
		}
	}

	// Update place
	switch(en->getCurrDir()){
		case DIR_UP: 	en->setPos(en->getX(), en->getY() - SHORTEST(walk, up)); break;
		case DIR_DOWN: 	en->setPos(en->getX(), en->getY() + SHORTEST(walk, down)); break;
		case DIR_LEFT: 	en->setPos(en->getX() - SHORTEST(walk, left), en->getY()); break;
		case DIR_RIGHT: en->setPos(en->getX() + SHORTEST(walk, right), en->getY()); break;
		default: break;
	};
};

bool Game::walkable(map_item_t item){
	return (item < walk_tag);
};

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
	}
	return false;
};

void Game::drawChar(int x, int y, char c){
	for(int py = 0; py < 7; py++){
		for(int px = 0; px < 7; px++){
			if(getCharPixel(c, px, py)){
				vi->drawPixel(x + px, y + py);
			}
		}
	}
};

void Game::drawText(int x, int y, char *text){
	int place = 0;

	char c = text[place];
	while(c){
		drawChar((place * 8) + x, y, c);

		c = text[++place];
	}
};

void Game::drawTextDifference(int x, int y, char *t1, char *t2){
	int place = 0;

	char c1 = t1[place];
	char c2 = t2[place];
	while(c1){
//		if(c1 != c2){
			bool p1, p2;
			for(int py = 0; py < 7; py++){
				for(int px = 0; px < 7; px++){
					p1 = getCharPixel(c1, px, py);
					p2 = getCharPixel(c2, px, py);
					if(p1 && !p2)
						vi->drawPixel((x + (place * 8) + px), (y + py), 0);
					if(p2)
						vi->drawPixel((x + (place * 8) + px), (y + py));
				}
			}
//		}

		place++;
		c1 = t1[place];
		c2 = t2[place];
	}
};

void Game::drawScoreText(){
	vi->setOffset(SCORE_OFFSET_X, SCORE_OFFSET_Y);
	vi->setColor(SCORE_TEXT_COLOR);

	drawText(0, 0, "HI-SCORE");
	drawText(8 , 32, "1UP");

	vi->resetOffset();
};

void Game::drawScore(){
	vi->setOffset(SCORE_OFFSET_X, SCORE_OFFSET_Y);
	vi->setColor(SCORE_COLOR);

	char text_old[8] = { 0 };
	char text_new[8] = { 0 };

	if(cur_score > cur_hscore){
		cur_hscore = cur_score;
	}

	if(cur_hscore != old_hscore){
		sprintf(text_old, "%*d", 7, old_hscore);
		sprintf(text_new, "%*d", 7, cur_hscore);
		drawTextDifference(0, 16, text_old, text_new);
		old_hscore = cur_hscore;
	}

	if(cur_score != old_score){
		sprintf(text_old, "%*d", 7, old_score);
		sprintf(text_new, "%*d", 7, cur_score);
		drawTextDifference(0, 48, text_old, text_new);
		old_score = cur_score;
	}

	vi->resetOffset();
};

void Game::drawMap(){
	vi->setOffset(MAP_OFFSET_X, MAP_OFFSET_Y);
	for(int v = 0; v < 27; v++){
		for(int h = 0; h < 21; h++){
			if(simpleMap){ // for testing
				if(!walkable(map[v][h]))
					vi->drawRect(H(0), V(0), 8, 8, WALL_COLOR);
			}else{
				switch(map[v][h]){
					case pd:
						vi->drawRect(H(3), V(3), 2, 2, PAC_DOT_COLOR);
						break;
					case c1:
						vi->drawLine(H(4), V(2), H(7), V(2), WALL_COLOR);
						vi->drawLine(H(2), V(4), H(2), V(7), WALL_COLOR);
						vi->drawPixel(H(3), V(3), WALL_COLOR);
						vi->drawLine(H(6), V(5), H(7), V(5), WALL_COLOR);
						vi->drawLine(H(5), V(6), H(5), V(7), WALL_COLOR);
						break;
					case c2:
						vi->drawLine(H(0), V(2), H(3), V(2), WALL_COLOR);
						vi->drawLine(H(5), V(4), H(5), V(7), WALL_COLOR);
						vi->drawPixel(H(4), V(3), WALL_COLOR);
						vi->drawLine(H(0), V(5), H(1), V(5), WALL_COLOR);
						vi->drawLine(H(2), V(5), H(2), V(7), WALL_COLOR);
						break;
					case c3:
						vi->drawLine(H(2), V(0), H(2), V(3), WALL_COLOR);
						vi->drawLine(H(4), V(5), H(7), V(5), WALL_COLOR);
						vi->drawPixel(H(3), V(4), WALL_COLOR);
						vi->drawLine(H(5), V(0), H(5), V(1), WALL_COLOR);
						vi->drawLine(H(6), V(2), H(7), V(2), WALL_COLOR);
						break;
					case c4:
						vi->drawLine(H(5), V(0), H(5), V(3), WALL_COLOR);
						vi->drawLine(H(0), V(5), H(3), V(5), WALL_COLOR);
						vi->drawPixel(H(4), V(4), WALL_COLOR);
						vi->drawLine(H(2), V(0), H(2), V(1), WALL_COLOR);
						vi->drawLine(H(0), V(2), H(1), V(2), WALL_COLOR);
						break;
					case ph:
						vi->drawLine(H(0), V(2), H(7), V(2), WALL_COLOR);
						vi->drawLine(H(0), V(5), H(7), V(5), WALL_COLOR);
						break;
					case pv:
						vi->drawLine(H(2), V(0), H(2), V(7), WALL_COLOR);
						vi->drawLine(H(5), V(0), H(5), V(7), WALL_COLOR);
						break;
					case tu:
						vi->drawLine(H(0), V(5), H(7), V(5), WALL_COLOR);
						vi->drawLine(H(0), V(2), H(1), V(2), WALL_COLOR);
						vi->drawLine(H(6), V(2), H(7), V(2), WALL_COLOR);
						vi->drawLine(H(2), V(0), H(2), V(1), WALL_COLOR);
						vi->drawLine(H(5), V(0), H(5), V(1), WALL_COLOR);
						break;
					case td:
						vi->drawLine(H(0), V(2), H(7), V(2), WALL_COLOR);
						vi->drawLine(H(0), V(5), H(1), V(5), WALL_COLOR);
						vi->drawLine(H(6), V(5), H(7), V(5), WALL_COLOR);
						vi->drawLine(H(2), V(6), H(2), V(7), WALL_COLOR);
						vi->drawLine(H(5), V(6), H(5), V(7), WALL_COLOR);
						break;
					case tl:
						vi->drawLine(H(5), V(0), H(5), V(7), WALL_COLOR);
						vi->drawLine(H(2), V(0), H(2), V(1), WALL_COLOR);
						vi->drawLine(H(0), V(2), H(1), V(2), WALL_COLOR);
						vi->drawLine(H(0), V(5), H(1), V(5), WALL_COLOR);
						vi->drawLine(H(2), V(6), H(2), V(7), WALL_COLOR);
						break;
					case tr:
						vi->drawLine(H(2), V(0), H(2), V(7), WALL_COLOR);
						vi->drawLine(H(5), V(0), H(5), V(1), WALL_COLOR);
						vi->drawLine(H(6), V(2), H(7), V(2), WALL_COLOR);
						vi->drawLine(H(6), V(5), H(7), V(5), WALL_COLOR);
						vi->drawLine(H(5), V(6), H(5), V(7), WALL_COLOR);
						break;
					case cu:
						vi->drawLine(H(2), V(0), H(2), V(3), WALL_COLOR);
						vi->drawLine(H(5), V(0), H(5), V(3), WALL_COLOR);
						vi->drawLine(H(3), V(4), H(4), V(4), WALL_COLOR);
						break;
					case cd:
						vi->drawLine(H(2), V(4), H(2), V(7), WALL_COLOR);
						vi->drawLine(H(5), V(4), H(5), V(7), WALL_COLOR);
						vi->drawLine(H(3), V(3), H(4), V(3), WALL_COLOR);
						break;
					case cl:
						vi->drawLine(H(0), V(2), H(3), V(2), WALL_COLOR);
						vi->drawLine(H(0), V(5), H(3), V(5), WALL_COLOR);
						vi->drawLine(H(4), V(3), H(4), V(4), WALL_COLOR);
						break;
					case cr:
						vi->drawLine(H(4), V(2), H(7), V(2), WALL_COLOR);
						vi->drawLine(H(4), V(5), H(7), V(5), WALL_COLOR);
						vi->drawLine(H(3), V(3), H(3), V(4), WALL_COLOR);
						break;
					case gc:
						vi->drawLine(H(-3), V(4), H(10), V(4), WALL_COLOR);
						break;
					default: break;
				}
			}

		}
	}
	vi->resetOffset();
};

