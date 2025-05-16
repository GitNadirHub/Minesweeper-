#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <string>

struct cell
{
    int val = 0;
    bool visible = 0;
    bool flagged = 0;
};

extern std::string state;

extern sf::RenderWindow window;