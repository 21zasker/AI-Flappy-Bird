#pragma once

const float FLAP_SPEED = -4;
const float GRAVITY = 0.25f;

const float BIRD_WIDTH = 56;
const float BIRD_HEIGHT = 48;
const int GAP_SIZE = 115;
const int PIPE_LIMIT = 80; // Pipes won't move to the top or the bottom passed that limit
const int PIPE_WIDTH = 64;
const int PIPE_HEIGHT = 64;

const int GROUND_Y = 720; // Y - coordinate where the ground starts
const int SCREEN_HEIGHT = 768;
const int SCREEN_WIDTH = 768;

const int POPULATION_SIZE = 10;
const int INPUT_NEURONS = 3;
const int HIDDEN_NEURONS = 4;
const int OUTPUT_NEURONS = 1;