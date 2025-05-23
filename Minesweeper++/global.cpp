#include "global.h"
#include <sstream>

stateString state = Ongoing;
levelString level = Beginner;

std::string fillNumericString(int value)
{
    std::stringstream ss;
    ss << std::setw(3) << std::setfill('0') << value;
    return ss.str();
}