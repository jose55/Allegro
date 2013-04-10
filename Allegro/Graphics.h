#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>

class SpriteArray
{
  public:
	SpriteArray(char* directory);
	~SpriteArray();
	std::vector<ALLEGRO_BITMAP*> spriteVector;

	ALLEGRO_BITMAP *sprite;

	char* sprite_directory;

	int AddSprite(char* filename);
};

#endif