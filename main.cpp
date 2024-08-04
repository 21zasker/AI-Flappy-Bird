#include <SFML/Graphics.hpp>
#include "Headers/BirdsManager.h"
#include "Headers/Scene.h"
#include "Headers/PipesManager.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird AI - SFML", sf::Style::Close);

    // Frames
    window.setFramerateLimit(60);

    // Random engine
    std::random_device rd;
    std::mt19937_64 random_engine(rd());

    // Background and ground tiles
    Scene scene;
    scene.generate_scene();

    // Pipes
    PipesManager pipes_manager;

    // Birds
    BirdsManager birds_manager(random_engine);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!birds_manager.all_dead_birds())
        {
            birds_manager.update_birds(pipes_manager.get_pipes());
            pipes_manager.generate_pipes(random_engine);
            pipes_manager.update_pipes();
        }
        else
        {
            birds_manager.next_generation();
            birds_manager.sort_birds();
            birds_manager.evolve_birds(random_engine);
            pipes_manager.reset_pipes();
        }

        // Window render
        window.clear();
        scene.draw_scene(window);
        pipes_manager.draw_pipes(window);
        birds_manager.draw_birds(window);
        scene.draw_score(birds_manager.get_max_score(), window);
        window.display();
    }

    return 0;
}