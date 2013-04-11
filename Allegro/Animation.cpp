#include "Animation.h"

Animate::Animate(int player_num)
{
	Animate::player_num = player_num;
}

int Animate::AddAnimation(char* ...)
{
	va_list images;
	va_start(images, num_frames);
	for (int i = 0; i < num_frames; ++i)
	{
		sprite_array.push_back(va_arg(images, ALLEGRO_BITMAP*));
	}
	va_end(images);
}