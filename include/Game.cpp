#include "Game.h"

Game::Game() : p(150, 200, this->playerColor){
	
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	this->win = SDL_CreateWindow("RunRect By Abthahi Ahmed Rifat", 200, 0, 1024, 640, 0);
	this->ren = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_TARGETTEXTURE);

}

void Game::setup(){
	this->isRunning = true;
	
	SDL_GetRendererOutputSize(this->ren, &this->width, &this->height);
	
	this->fps = 60;
	
	//	Color Initialization
	this->colors.push_back({58, 134, 255});
	this->colors.push_back({131, 56, 236});
	this->colors.push_back({255, 190, 11});
	this->colors.push_back({42, 157, 143});
	this->colors.push_back({233, 196, 106});
	this->colors.push_back({231, 111, 81});
	this->colors.push_back({239, 71, 111});
	this->colors.push_back({6, 214, 160});
	this->colors.push_back({17, 138, 178});
	this->colors.push_back({118, 120, 237});
	// End
	
	this->ground.push_back(Ground(100, 400, this->colors[this->random(0, 4)]));
	this->ground.push_back(Ground(520, 400, this->colors[this->random(5, 6)]));
	this->ground.push_back(Ground(980, 450, this->colors[this->random(6, 9)]));

	
	this->count = 0;
	
	this->gameSpeed = 7;
	this->startGameSpeed = 7;
	this->distance = 0;
	
	this->cameraY = 0;
	
	this->font_s_16 = TTF_OpenFont("fonts/Saira-Regular.ttf", 16);
	this->font_s_24 = TTF_OpenFont("fonts/Saira-Regular.ttf", 24);
	this->font_s_60 = TTF_OpenFont("fonts/Saira-Regular.ttf", 60);
	this->font_s_90 = TTF_OpenFont("fonts/Saira-Regular.ttf", 90);

	if (!this->font_s_24 || !this->font_s_60 || !this->font_s_90){
		cout<<"Error in font loading...! : "<<TTF_GetError()<<endl;
		exit(1);
	}
	
	
	
	
	
	this->score = 0;
	
	SDL_SetRenderDrawBlendMode(this->ren, SDL_BLENDMODE_BLEND);
	
	this->overlay = {0,0, width, height};
	this->score_board = {0,0, 300, 50};
	
	this->end = false;
	this->started = false;
}
void Game::start(){
	this->run();
}


void Game::reset(){
	
	this->p = Player(150, 200, this->playerColor);
	
	this->score = 0;
	this->ground.clear();
	this->ground.push_back(Ground(100, 400, this->colors[this->random(0, 4)]));
	this->ground.push_back(Ground(520, 400, this->colors[this->random(5, 6)]));
	this->ground.push_back(Ground(980, 450, this->colors[this->random(6, 9)]));
	
	this->count = 0;
	
	this->gameSpeed = 7;
	this->startGameSpeed = 7;
	this->distance = 0;
	
	this->end = false;
}

void Game::run(){
	while(this->isRunning){
		this->handleEvent();
		SDL_SetRenderDrawColor(this->ren, this->bgColor.r, this->bgColor.g, this->bgColor.b, 255);
		SDL_RenderClear(this->ren);
		
		if (started){
			this->update();
		}
		
		
		this->draw();
		SDL_RenderPresent(this->ren);
		
		SDL_Delay(1000/this->fps);
	}
}
void Game::handleEvent(){
	if (!end){
		SDL_PollEvent(&this->event);
	}else{
		SDL_WaitEvent(&this->event);
	}
	if(this->event.type == SDL_QUIT){
		this->isRunning = false;
	}
	
	else if(this->event.type == SDL_KEYDOWN){
		
		switch(this->event.key.keysym.sym){
			
			case SDLK_SPACE:
				this->p.jump();
				break;
			case SDLK_ESCAPE:
				this->isRunning = false;
				break;
			case SDLK_RETURN:
				if (end){
					this->reset();
				}
				else if(!started){
					started = true;
				}
				break;
		}
	}
}
void Game::draw(){
	
	// Shadow
	
	this->p.dropShadow(this->ren);
	
	for (unsigned int i=0; i< this->ground.size(); i++){
		
		this->ground[i].dropShadow(this->ren);
		
		this->ground[i].draw(this->ren);
	}
	this->p.draw(this->ren);

	
	SDL_SetRenderDrawColor(this->ren, this->colors[6].r, this->colors[6].g, this->colors[6].b, 255);
	SDL_RenderFillRect(this->ren, &this->score_board);
	
	this->renderText(this->ren, this->font_s_24, 10, 5, "Score : " + to_string(this->score), this->textColor);
	
	if (this->end){

		
		SDL_SetRenderDrawColor(this->ren, 0,0,0,130);
		SDL_RenderFillRect(this->ren, &this->overlay);
		
		
		this->renderTextCenter(this->ren, this->font_s_16, width/2, height / 2 + 80, "Press Enter to play again or ESC to exit.", this->textColor);
		
		this->renderTextCenter(this->ren, this->font_s_24, width/2, height / 2 + 20, "Your score : " + std::to_string(this->score), this->textColor);
		
		this->renderTextCenter(this->ren, this->font_s_90, width/2, height / 2 - 90, "GAME OVER!", this->textColor);
		
		
	}
	
	if (!started){
		
		SDL_SetRenderDrawColor(this->ren, 0,0,0,130);
		SDL_RenderFillRect(this->ren, &this->overlay);
		
		
		this->renderTextCenter(this->ren, this->font_s_16, width/2, height / 2 + 80, "Press Enter to start game or ESC to exit.", this->textColor);
		
		this->renderTextCenter(this->ren, this->font_s_24, width/2, height / 2 + 20, "Created By Abthahi Ahmed Rifat", this->textColor);
		
		this->renderTextCenter(this->ren, this->font_s_90, width/2, height / 2 - 90, "RunRect.", this->colors[5]);		
		
	}
	
	
}
void Game::update(){

	

	if (!this->p.end(this->height)){
	
		this->count += 2;
		
		if (this->count >= this->random(120, 290)){
			
			this->ground.push_back(Ground(this->width, this->random(360, 470), this->colors[this->random(0, 9)]));
			
			this->count = 0;
			this->distance += 1;
		}
		
		this->gameSpeed = this->startGameSpeed + (this->distance / 20);
		
		
		this->p.update(gameSpeed);
		for (unsigned int i=0; i< this->ground.size(); i++){
			
			this->p.collide(this->ren, this->ground[i]);
			
			this->ground[i].update(this->gameSpeed, this->cameraY);
			
			if(this->ground[i].done()){
				this->ground.erase(this->ground.begin()+i);
			}
		}
		
		
		this->score += ((this->distance / 20) + 1);
	
	}else{
		this->end = true;
	}

	
	
}
void Game::clear(){
	
	SDL_DestroyWindow(this->win);
	SDL_DestroyRenderer(this->ren);
	
	TTF_CloseFont(this->font_s_16);
	TTF_CloseFont(this->font_s_24);
	TTF_CloseFont(this->font_s_60);
	TTF_CloseFont(this->font_s_90);
	
	TTF_Quit();
	SDL_Quit();

}