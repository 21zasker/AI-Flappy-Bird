# AI Flappy Bird
## Overview
This project demonstrates how evolutionary algorithms and neural networks can be used to train an AI agent in a game environment. In this case, the AI's goal is to navigate through a series of pipes while avoiding collisions with them and the ground in a classic Flappy Bird game. The game and AI are developed using C++ and SFML.

## Features
* A neural network powers the AI's decision-making process to make the bird flap or not.
* A genetic algorithm evolves the AI agents by selecting the best-performing ones and mutating their neural network weights.
* Pipes are generated and moved across the screen with varying heights.

## Architecture
### Neural Network
1. **Input Layer:**
   Receives data such as:
   - The bird's vertical speed
   - Distance between the gap and the bird's height
   - Pipes movement direction (Up or Down).
2. **Hidden Layer:** Processes the input data with weights and activation functions.
3. **Output Layer:** Determines whether the bird should flap or not.

### Genetic Algorithm
1. **Selection:** Chooses the top-performing AI agents based on their performance scores.
2. **Crossover:** Combines the weights of the top agents to create new offspring.
3. **Mutation:** Introduces random changes to some weights to ensure diversity in the population.

## Functions
- `updateBird(std::vector<Pipes> pipes)`: Updates the bird's position, checks for collisions, and makes decisions based on the neural network.
- `init_neural_network()`: Sets up the neural network layers.
- `random_weights(std::mt19937_64 &random_engine)`: Initializes the weights for the neural network.
- `flap_AI(std::vector<Pipes> pipes)`: Determines if the bird should flap based on neural network output.
- `evolve(std::mt19937_64 &random_engine, &bird1, &bird2)`: Evolves the weights of the neural network using the best-performing birds.

## Dependencies
- SFML
- C++ Standard Library

## Showcase
<img src="https://github.com/21zasker/AI-Flappy-Bird/blob/main/Showcase/AI%20Flappy%20Bird%20GIF.gif" width="25%" alt="Showcase">

## Note
This project is intended to demonstrate the application of AI techniques in game development. Further optimizations and enhancements can be made to improve the AI's performance and the game's functionality.
