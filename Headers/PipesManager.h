#pragma once
#include "Pipes.h"
#include "GeneralUtilities.hpp"
#include <random>

class PipesManager
{
public:
	 PipesManager(): y_distribution(PIPE_LIMIT, GROUND_Y - GAP_SIZE - PIPE_LIMIT)
    {
        frameCounter = 310;
        maxFrames = 310;
		greenColor = false;
    }

	void generate_pipes(std::mt19937_64& i_random_engine);
	void draw_pipes(sf::RenderWindow& window);
	void reset_pipes();
	void update_pipes();

	std::vector<Pipes> get_pipes()
    {
        return pipes;
    }

private:

	std::uniform_int_distribution<> y_distribution;
	std::vector<Pipes> pipes;

	int frameCounter;
    int maxFrames;
	bool greenColor;
};