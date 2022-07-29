#ifndef GAME_H
#define GAME_H
#pragma once
// C++
#include <iostream>
#include <vector>
// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
// RunRect Headers
#include "Player.h"
#include "Ground.h"


using namespace std;

class Game{
	
private:
	SDL_Window *win;
	SDL_Renderer *ren;
	bool isRunning;
	int fps;
	int width, height;
	int count;
	int cameraY;
	int gameSpeed;
	int startGameSpeed;
	int distance;
	bool end;
	bool started;
	int score;
	
	
	
	SDL_Rect overlay;
	SDL_Rect score_board;
	
	SDL_Event event;
	
	SDL_Color bgColor = {61, 64, 91};
	SDL_Color textColor = {255, 255, 255};
	vector<SDL_Color> colors;
	
	SDL_Color playerColor = {237, 242, 244};
	
	Player p;
	
	vector<Ground> ground;
	
	TTF_Font *font_s_24;
	TTF_Font *font_s_60;
	TTF_Font *font_s_90;
	TTF_Font *font_s_16;

	void update();
	void handleEvent();
	void draw();
	void run();
	int random(int a, int b){
		return a + ( rand() % ( b - a + 1 ) );
	}
	
	
	
	void renderText(SDL_Renderer *ren, TTF_Font *font, int x, int y, string text, SDL_Color color){
		
		SDL_Surface *tmp = NULL;
		SDL_Texture *texture = NULL;
		
		free(tmp);
		
		tmp = TTF_RenderText_Blended(font, text.c_str(), color);
		
		texture = SDL_CreateTextureFromSurface(ren, tmp);
		
		SDL_Rect rect = {x, y, tmp->w, tmp->h};
		
		SDL_FreeSurface(tmp);
		
		SDL_RenderCopy(ren, texture, NULL, &rect);
		
	}
	void renderTextCenter(SDL_Renderer *ren, TTF_Font *font, int x, int y, string text, SDL_Color color){
		SDL_Surface *tmp = NULL;
		SDL_Texture *texture = NULL;
		
		free(tmp);
		
		tmp = TTF_RenderText_Blended(font, text.c_str(), color);
		
		texture = SDL_CreateTextureFromSurface(ren, tmp);
		
		SDL_Rect rect = {x - (tmp->w / 2), y, tmp->w, tmp->h};
		
		SDL_FreeSurface(tmp);
		SDL_RenderCopy(ren, texture, NULL, &rect);
	}
	
	void reset();
	
	void renderText(SDL_Renderer *ren, SDL_Texture *texture, SDL_Rect rect){
		SDL_RenderCopy(ren, texture, NULL, &rect);
	}
	
public:
	Game();
	void setup();
	void start();
	void clear();

};




#endif
