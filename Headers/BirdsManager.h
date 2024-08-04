#pragma once
#include "FlapBot.h"
#include "Pipes.h"
#include "GeneralUtilities.hpp"
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

class BirdsManager
{
public:
    BirdsManager(std::mt19937_64 &random_engine)
    {
        current_generation = 0;
        birds.resize(POPULATION_SIZE);
        for (FlapBot &bird : birds)
        {
            bird.random_weights(random_engine);
        }
    }

    bool all_dead_birds();
    void update_birds(std::vector<Pipes> pipes);
    void draw_birds(sf::RenderWindow &window);
    void sort_birds();
    void evolve_birds(std::mt19937_64 &random_engine);
    void next_generation();

    int get_max_score();

    std::vector<FlapBot> get_birds()
    {
        return birds;
    }

private:
    std::vector<FlapBot> birds;
    int current_generation;
};