#include "Graphics.h"

SpriteArray::SpriteArray(char* directory)
{
	sprite_directory = directory;
}

SpriteArray::~SpriteArray()
{
}

int SpriteArray::AddSprite(char *filename)
{
	char* dir;
	strcpy(dir, sprite_directory);
	strcat(dir, filename);
	
	sprite = al_load_bitmap(dir);

	if (sprite == NULL)
	{
		fprintf(stderr, "failed to load sprite!\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Sprite Error", "Error initializing sprite", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}

	spriteVector.push_back(sprite);
}