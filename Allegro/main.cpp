#include "Base.h"
#include "Player.h"

extern ALLEGRO_SAMPLE *music;

int main(int argc, char **argv)
{
	GameState state(640, 480, "resources/bg.bmp");

	AddPlayer(50, 350, "resources/", 3, 5);
	
	AddSprite("sprite1.png", 0);
	AddSprite("sprite2.png", 0);
	AddSprite("sprite3.png", 0);
	AddSprite("jump.png", 0);

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

	while (true)
	{
		if (state.Update() == -1)
			break;

		//if (i % 50 == 0)
		//	printf("Loop: %i\n", i);
	}

	return 0;
}