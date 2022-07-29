#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

class Particle {
	int x, y;
	int alpha;
	SDL_Rect rect;
	SDL_Rect shadow;
	
	SDL_Color color;
	vector<SDL_Color> colors;
	int random(int a, int b){
		return a + ( rand() % ( b - a + 1 ) );
	}
public:
	Particle(int x, int y);
	void update(int flow);
	void draw(SDL_Renderer *ren);
	bool hidden();
	void dropShadow(SDL_Renderer *ren);
	
};



#endif