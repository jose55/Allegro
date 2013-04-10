#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>

class Player
{
  public:
	ALLEGRO_BITMAP *bitmap;
	float xpos, ypos, xvel, yvel;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	bool moving;

	Player();
	~Player();

	std::vector<ALLEGRO_BITMAP*> spriteVector;

	bool FacingLeft, FacingRight;
	int FaceLeft();
	int FaceRight();

	std::string sprite_directory;

};

int AddPlayer(int x, int y, char* directory, int max_frames, int frame_delay);
int AddSprite(char* filename, int playernum);

extern std::vector<Player> pVector;

#endif