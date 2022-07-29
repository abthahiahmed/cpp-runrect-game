#include "Player.h"

Player::Player(int x, int y, SDL_Color color){
	
	this->x = x;
	this->y = y;
	
	this->size = 50;
	this->color = color;
	this->gravity = 1.8;
	
	this->isJumping = false;
	this->isBottom = true;
	
	this->vx = 0;
	this->vy = 0;
	this->rect.x = this->x;
	this->rect.y = this->y;
	this->rect.w = this->size;
	this->rect.h = this->size;
	
	this->shadow.x = this->x + 50;
	this->shadow.y = this->y + 100;
	this->shadow.w = this->size;
	this->shadow.h = this->size;
	
	
	
}

void Player::update(int flow){

		
	this->rect.x = this->x;
	this->rect.y = this->y;
	
	this->shadow.x = this->x + 50;
	this->shadow.y = this->y + 100;
	
	this->y += this->vy;
	
	if(this->isJumping){
		this->vy = -20; // Velocity to Upper
		this->vy *= 0.96; // Friction
	}else{
		this->prevY = this->y;
		this->vy += this->gravity;
	}
	
//	if (!this->isBottom){
		this->dust.push_back(Particle(this->rect.x + 5, this->rect.y + this->size - 10));
//	}
	
	for (unsigned int i=0;i < this->dust.size(); i++){
		
		this->dust[i].update(flow);
		if (this->dust[i].hidden()){
			this->dust.erase(this->dust.begin() + i);
		}
		
	}
	
	if(this->y <= this->prevY - 90){
		this->isJumping = false;
	}

	
	
}
void Player::draw(SDL_Renderer *ren){
	
	SDL_SetRenderDrawColor(ren, this->color.r, this->color.g, this->color.b, 255);
	SDL_RenderFillRect(ren, &this->rect);
	
	for (unsigned int i=0;i < this->dust.size(); i++){
		this->dust[i].draw(ren);
	}
	
	
	
	
	
	
}
void Player::dropShadow(SDL_Renderer *ren){
	
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 20);
	SDL_RenderFillRect(ren, &this->shadow);

}

void Player::setY(int y){
	
	this->y = y;
	
}

void Player::collide(SDL_Renderer *ren, Ground g){
	
	int x1 = this->x;
	int y1 = this->y;
	int w1 = this->size;
	int h1 = this->size;
	
	int x2 = g.x;
	int y2 = g.y;
	int w2 = g.w;
	int h2 = g.h;	
	
	if( (x1 <= x2 + w2) and (x1 + w1 >= x2) and (y1 <= y2 + h2) and (y1 + h1 >= y2)  ){
		
		
		int playerBottom = y1 + h1;
		int playerRight = x1 + w1;
		
		int objBottom = y2 + h2;
		int objRight = x2 + w2;
		
		
		int c_bottom = objBottom - y1;
		int c_top = playerBottom - y2;
		int c_left = playerRight - x2;
		int c_right = objRight - x1;
		
		
		
		if (c_top < c_bottom && c_top < c_left && c_top < c_right){
			if (!this->isJumping) this->vy = 0;
			this->y = y2 - this->size;
			this->isBottom = true;
		}else{
			this->isBottom = false;
		}
		
		if (c_bottom < c_top && c_bottom < c_left && c_bottom < c_right){
			this->isJumping = false;
			this->vy += this->gravity;
			this->y = y2 + h2;
			
			
		}		
		if (c_left < c_top && c_left < c_right && c_left < c_bottom){
			this->x = x2 - this->size;
		}		
		
		
	}
	
	
}
void Player::jump(){
	
	if(!this->isJumping && this->isBottom){
		this->isJumping = true;
		this->isBottom = false;
	}
}

bool Player::end(int s){
	
	if ((this->y + this->size) > s){
		
		this->dust.clear();
		
		return true;
	}
	return false;

	
}