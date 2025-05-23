#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <string>


struct cell
{
    int val = 0;
    bool visible = 0;
    bool flagged = 0;
};

enum stateString
{
    Ongoing, Win, Loss
};

enum levelString
{
    Beginner, Intermediate, Hard, Evil
};

extern stateString state;
extern levelString level;

extern sf::RenderWindow window;

const int extraH = 160;

extern std::string fillNumericString(int value);