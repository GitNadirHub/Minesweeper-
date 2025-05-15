#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>

struct cell
{
    int val = 0;
    bool visible = 0;
    bool flagged = 0;
};



extern sf::RenderWindow window;