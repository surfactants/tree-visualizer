////////////////////////////////////////////////////////////
// PRIMORDIAL
// ----------
// Provides a variety of basic math functions (and text operations/randomColor in this distribution).
// Written by surfactants (https://github.com/surfactants).
//
// LICENSE: zlib (https://www.zlib.net/zlib_license.html)
// -------
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include <primordial.hpp>

#include <prng.hpp>

void centerText(sf::Text& text)
{
    sf::FloatRect trect = text.getLocalBounds();
    text.setOrigin(trect.left + (trect.width / 2.f), trect.top + (trect.height / 2.f));
}

float calculateAngle(const sf::Vector2f& v, const sf::Vector2f& w)
{
    float theta;

    //defines a right triangle between two points
    float opp = w.y - v.y;
    float adj = w.x - v.x;

    //calculates theta in radians
    theta = atan(opp/adj);

    //converts theta to degrees
    theta *= 180/PI;

    //converts theta for use with SFML
    if (adj>0) {
        theta += 90;
    }
    else if (adj<0) {
        theta += 270;
    }

    return theta;
}

sf::Vector2f calculateMoveVector(sf::Vector2f start, sf::Vector2f end, float speed)
{
    sf::Vector2f v = calculateMoveVector(calculateAngle(start, end), speed);
    return v;
}

sf::Vector2f calculateMoveVector(float angle, float velocity)
{
    sf::Vector2f v;

    angle -= 90;
    angle *= (PI/180); //converts angle to radians

    v.x = velocity * cos(angle);
    v.y = velocity * sin(angle);

    return v;
}

int roundFloat(float f)
{
    return static_cast<int>(f + 0.5f);
}

void wrapText(sf::Text& text, int width)
{
    std::string toWrap = text.getString();
    std::string wrapped;

    unsigned int epos = 1;

    while(epos < toWrap.length()) {
        int factor = text.getCharacterSize() * 1.5 - text.findCharacterPos(0).x;
        if (text.findCharacterPos(epos).x + factor > width) {
            while(toWrap.at(--epos) != ' '); //finds and deletes last space character
            wrapped += toWrap.substr(0, epos) + "\n";
            toWrap.erase(0, ++epos);
            epos = 0;
        }
        epos++;
    }

    wrapped += toWrap;
    text.setString(wrapped);
}

sf::Color randomColor(const unsigned int alpha) {
    const unsigned int r = prng::number(0, 255);
    const unsigned int g = prng::number(0,255);
    const unsigned int b = prng::number(0,255);
    return sf::Color(r, g, b, alpha);
}

sf::Color randomColor() {
    return randomColor(255);
}
