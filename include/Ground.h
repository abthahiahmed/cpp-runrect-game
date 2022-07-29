#pragma once
#ifndef GROUND_H
#define GROUND_H

#include <iostream>
#include <SDL2/SDL.h>

class Ground{
	SDL_Rect rect, shadow;
public:
	int x,y;
	int w,h;
	SDL_Color color;
	Ground(int x, int y, SDL_Color color);
	void update(int gamespeed, int cameraY);
	void draw(SDL_Renderer *ren);
	void dropShadow(SDL_Renderer *ren);
	bool done();
};


#endif