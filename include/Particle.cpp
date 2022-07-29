#include "Particle.h"

Particle::Particle(int x, int y){
	
	this->x = x;
	this->y = y - this->random(0, 20);
	
	this->alpha = 250;
	
	int size = this->random(5, 18);
	
	this->colors.push_back({255, 183, 3});
	this->colors.push_back({251, 133, 0});
	
	this->rect = {this->x, this->y, size, size};
	this->shadow = {this->x+50, this->y+100, size, size};
	
	this->color = this->colors[random(0, 1)];
	
	
	
}

void Particle::update(int flow){
	
	this->x -= flow;
	
	this->alpha -= 10;
	
	this->rect.x = this->x;
	this->rect.y = this->y;
	
	this->shadow.x = this->x + 50;
	this->shadow.y = this->y + 100;
}

void Particle::draw(SDL_Renderer *ren){
	
	SDL_SetRenderDrawColor(ren, this->color.r, this->color.g, this->color.b, this->alpha);
	SDL_RenderFillRect(ren, &this->rect);
	
}

void Particle::dropShadow(SDL_Renderer *ren){
	
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 10);
	
	SDL_RenderFillRect(ren, &this->shadow);
}

bool Particle::hidden(){
	
	if (this->alpha < 0){
		
		return true;
		
	}
	
	return false;
}