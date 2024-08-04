#pragma once
#include "textureManager.h"

class Pipes
{
public:
	Pipes(float i_x, float i_y, bool i_greenColor)
    {
        x = i_x;
        y = i_y;
        move_direction = (rand() % 2 == 1) ? Up : Down;
		greenColor = i_greenColor;

    }

	enum MoveDirection
    {
        Up,
        Down
    };
    MoveDirection move_direction;

	// Functions
	void draw(sf::RenderWindow& window);
	void update();

	float get_x(){
        return x;
    }

    float get_y(){
        return y;
    }

private:
	
	sf::Sprite pipe_sprite;
    TextureManager txtManager;
    float x, y;
	bool greenColor;
};