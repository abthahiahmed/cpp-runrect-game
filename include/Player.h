#ifndef PLAYER_H
#define PLAYER_H
#pragma once


#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "Ground.h"
#include "Particle.h"

using namespace std;

class Player{
	
private:
	

	int vx,vy;
	SDL_Rect rect, shadow;
	SDL_Color color;
	int size;
	int gravity;
	int prevY;
	bool isJumping;
	bool isColide;
	bool isBottom;
	vector<Particle> dust;
	
public:
	int x;
	int y;
	Player(int x, int y, SDL_Color color);
	void update(int flow);
	void draw(SDL_Renderer *ren);
	void collide(SDL_Renderer *ren, Ground g);
	void setY(int y);
	void jump();
	bool end(int s);
	void dropShadow(SDL_Renderer *ren);

};




#endif