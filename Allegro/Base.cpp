#include "Base.h"
#include "Player.h"

//derp

bool key[5] = {false, false, false, false, false};
ALLEGRO_BITMAP *background;
ALLEGRO_SAMPLE *music;

#define XMAXSPEED 5
#define XSPEEDUP 0.33
#define XSLOWDOWNMULT 1.15

#define YJUMPHEIGHT -15
#define JUMPSPEED 7
#define YGRAVITY .2
#define GROUNDHEIGHT 387
#define MAXFALLSPEED 6

GameState::GameState(int width, int height, char* bg_location)
{
	if (al_init() == false)
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Allegro Error", "Error initializing allegro", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}

	//al_set_new_display_flags(ALLEGRO_OPENGL);

	display = al_create_display(width, height);

	if (display == false)
	{
		fprintf(stderr, "failed to create display!\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Display Error", "Error creating display", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}

	timer = al_create_timer(1.0 / FPS);
	if (timer == false)
	{
		fprintf(stderr, "failed to create timer!\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Timer Error", "Error creating timer", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}
	
	event_queue = al_create_event_queue();
	if (event_queue == false)
	{
		fprintf(stderr, "failed to create event queue!\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Event Queue Error", "Error creating event queue", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}
	
	if (al_install_keyboard() == false)
	{
		fprintf(stderr, "failed to install keyboard\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Keyboard Error", "Error installing keyboard", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}

	if (al_init_image_addon() == false)
	{
		fprintf(stderr, "failed to install image addon\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Image Error", "Error installing image addon", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}

	if (al_install_audio() == false)
	{
		fprintf(stderr, "failed to install audio addon\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Audio Error", "Error installing Audio addon", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}
	
	if (al_init_acodec_addon() == false)
	{
		fprintf(stderr, "failed to install audio codec addon\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Audio Error", "Error installing Audio codec addon", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}

	if (al_reserve_samples(1) == false)
	{
		fprintf(stderr, "failed to reserve samples\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Sample Error", "Error reserving audio samples", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}

	background = al_load_bitmap(bg_location);
	if (background == nullptr)
	{
		fprintf(stderr, "failed to load background\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Background Error", "Error Loading background image", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}

	music = al_load_sample("resources/smb.ogg");
	if (music == nullptr)
	{
		fprintf(stderr, "failed to load music\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Music Error", "Error Loading Music", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
}

GameState::~GameState()
{
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
}

void GameState::Render()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_bitmap(background, 0, 0, NULL);

	for (unsigned int i = 0; i < pVector.size(); i++)
	{
		if (pVector[0].inair == false)
		al_draw_bitmap(pVector[0].spriteVector[pVector[0].curFrame], pVector[0].xpos, pVector[0].ypos, pVector[0].FacingLeft == true?ALLEGRO_FLIP_HORIZONTAL:NULL);
		else
		al_draw_bitmap(pVector[0].spriteVector[3], pVector[0].xpos, pVector[0].ypos, pVector[0].FacingLeft == true?ALLEGRO_FLIP_HORIZONTAL:NULL);
	}
	al_flip_display();
}

int GameState::Update()
{
	return CheckEvents();
}

int GameState::CheckEvents()
{
	ALLEGRO_EVENT ev;
	al_wait_for_event(event_queue, &ev);
	
	if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		GameLogic(ev);
	}
	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		return -1;
	}
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		if (CheckKeyboard(ev) == -1)
			return -1;
	}
	
	if (redraw == true && al_event_queue_is_empty(event_queue))
	{
		redraw = false;
		GameState::Render();
	}
	
	return 0;
}

//CheckKeyboard returns -1 if close is pressed
//CheckKeyboard updates the "key[4]" bool to return correct keystates
int GameState::CheckKeyboard(ALLEGRO_EVENT ev)
{
	//printf("Checking Keyboard:\n");
	if(ev.type == ALLEGRO_EVENT_KEY_DOWN) 
	{
         switch(ev.keyboard.keycode) 
		 {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
 
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
                break;
 
            case ALLEGRO_KEY_LEFT: 
                key[KEY_LEFT] = true;
                break;
 
            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = true;
                break;

			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;
         }
	}
	else if(ev.type == ALLEGRO_EVENT_KEY_UP) 
	{
		switch(ev.keyboard.keycode)
		{
			case ALLEGRO_KEY_UP:
                key[KEY_UP] = false;
                break;
 
            case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = false;
                break;
 
            case ALLEGRO_KEY_LEFT: 
                key[KEY_LEFT] = false;
                break;
 
            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = false;
                break;

			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;
 
			case ALLEGRO_KEY_ESCAPE:
				return -1;
                break;
		}
	}
	return 0;
}

int GameState::GameLogic(ALLEGRO_EVENT ev)
{
	if (key[KEY_UP])
	{
		pVector[0].ypos--;
		printf("ypos is now %f\n", pVector[0].ypos);
	}
	if (key[KEY_DOWN])
	{
		pVector[0].ypos++;
		printf("ypos is now %f\n", pVector[0].ypos);
	}

		if (key[KEY_SPACE])
		{
			if (pVector[0].inair == false)
			{
				pVector[0].moving = false;
				pVector[0].yvel = -JUMPSPEED;
				pVector[0].inair = true;
			}
			else
			{
				if (pVector[0].yvel >= MAXFALLSPEED)
				{
					pVector[0].yvel = MAXFALLSPEED;
				}
				pVector[0].yvel += YGRAVITY;

				pVector[0].ypos += pVector[0].yvel;

				if (pVector[0].ypos >= GROUNDHEIGHT)
				{
					pVector[0].inair = false;
					pVector[0].ypos = GROUNDHEIGHT;
				}
			}
		
		}

	if (key[KEY_LEFT])
	{
		if (pVector[0].xvel <= -XMAXSPEED)
			pVector[0].xvel = -XMAXSPEED;
		else
			pVector[0].xvel -= XSPEEDUP;

		pVector[0].xpos += pVector[0].xvel;
		pVector[0].FaceLeft();
		if (pVector[0].inair == false)
			pVector[0].moving = true;
		else
			pVector[0].curFrame = 0;
	}
	else if (key[KEY_RIGHT])
	{
		if (pVector[0].xvel >= XMAXSPEED)
			pVector[0].xvel = XMAXSPEED;
		else
		pVector[0].xvel += XSPEEDUP;

		pVector[0].xpos += pVector[0].xvel;

		pVector[0].FaceRight();
		if (pVector[0].inair == false)
			pVector[0].moving = true;
		else
			pVector[0].curFrame = 0;
	}
	else
	{
		pVector[0].moving = false;
		pVector[0].curFrame = 0;
		pVector[0].frameCount = 0;
		pVector[0].xvel /= XSLOWDOWNMULT;
		if (pVector[0].xvel < 0.2 && pVector[0].xvel > -0.2)
			pVector[0].xvel = 0;
		pVector[0].xpos += pVector[0].xvel;
	}

	if (pVector[0].inair && key[KEY_SPACE] == false)
	{
		if (pVector[0].yvel >= MAXFALLSPEED)
		{
			pVector[0].yvel = MAXFALLSPEED;
		}

		pVector[0].yvel += (2 * YGRAVITY);

		pVector[0].ypos += pVector[0].yvel;

		if (pVector[0].ypos >= GROUNDHEIGHT)
		{
			pVector[0].inair = false;
			pVector[0].ypos = GROUNDHEIGHT;
		}
	}

	for (unsigned int i = 0; i < pVector.size(); i++)
	{
		if (pVector[i].moving)
		if (++pVector[i].frameCount >= pVector[i].frameDelay)
		{
			if (++pVector[i].curFrame >= pVector[i].maxFrame)
				pVector[i].curFrame = 0;
			pVector[i].frameCount = 0;
		}
	}
	redraw = true;

	return 0;
}

/*
int GameState::LoadContent()
{

}*/