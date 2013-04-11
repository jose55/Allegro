#ifndef ANIMATION_H
#define ANIMATION_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>

class Animate
{
	std::vector<ALLEGRO_BITMAP*> sprite_array;

	Animate(int player_num);
	
	int AddAnimation(char* ...);

	int num_frames, player_num;

	~Animate();
};

#endif