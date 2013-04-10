#include "Player.h"
#include "Graphics.h"
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

std::vector<Player> pVector;
ALLEGRO_BITMAP *sprite;

int Player::FaceLeft()
{
	Player::FacingLeft = true;
	Player::FacingRight = false;
	return 0;
}
int Player::FaceRight()
{
	Player::FacingLeft = false;
	Player::FacingRight = true;
	return 0;
}

Player::Player()
{
	frameCount = 0;
	curFrame = 0;
	moving = false;
}

Player::~Player()
{
	//al_destroy_bitmap(bitmap);
}

int AddSprite(char *filename, int playernum)
{
	std::string path = pVector[playernum].sprite_directory;
	path.append(filename);
	sprite = al_load_bitmap(path.c_str());

	if (sprite == NULL)
	{
		printf(path.c_str());
		fprintf(stderr, "failed to load sprite!\n");
		al_show_native_message_box(al_get_current_display(), "Error", "Sprite Error", "Error initializing sprite", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	pVector[playernum].spriteVector.push_back(sprite);

	return 0;
}

int AddPlayer(int x, int y, char* directory, int max_frames, int frame_delay)
{
	Player newPlayer;

	newPlayer.xpos = x;
	newPlayer.ypos = y;

	newPlayer.maxFrame = max_frames;
	newPlayer.frameDelay = frame_delay;

	newPlayer.sprite_directory = directory;

	//newPlayer.bitmap = al_load_bitmap(file_location);

	//if (newPlayer.bitmap == nullptr)
	//{
	//	al_show_native_message_box(al_get_current_display(), "Error", "Image Error", "Failed to load image!", "Ok", ALLEGRO_MESSAGEBOX_ERROR);
	//}

	pVector.push_back(newPlayer);

	return 0;
}