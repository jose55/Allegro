#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <math.h>

#define FPS 60

enum Keys{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE};
extern bool key[5];

class GameState
{
public:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;

    bool redraw;

	GameState(int width, int height, char *bg_location);
	~GameState();

	void Render();
	int Update();
	int CheckEvents();
	int CheckKeyboard(ALLEGRO_EVENT ev);
	int GameLogic(ALLEGRO_EVENT ev);
};

#endif