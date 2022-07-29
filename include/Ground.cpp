#include "Ground.h"

Ground::Ground(int x, int y, SDL_Color color){
	
	this->x = x;
	this->y = y;
	this->w = 350;
	this->h = 50;
	this->color = color;
	this->rect = {this->x, this->y, this->w, this->h};
	this->shadow = {this->x + 50, this->y + 100, this->w, this->h};
	
}
void Ground::update(int gamespeed, int cameraY){
	
	this->rect = {this->x, this->y, this->w, this->h};
	this->shadow = {this->x + 50, this->y + 100, this->w, this->h};
	
	this->x -= gamespeed;
}

void Ground::draw(SDL_Renderer *ren){
	
	SDL_SetRenderDrawColor(ren, this->color.r, this->color.g, this->color.b, 255);
	SDL_RenderFillRect(ren, &this->rect);
	
}
void Ground::dropShadow(SDL_Renderer *ren){
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 20);
	SDL_RenderFillRect(ren, &this->shadow);
}
bool Ground::done(){
	
	if(this->x < -(this->w + 10)){
		return true;
	}
	return false;
}