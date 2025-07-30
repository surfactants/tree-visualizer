////////////////////////////////////////////////////////////
// PRIMORDIAL
// ----------
// Provides a variety of basic math functions (and also wrapText in this distribution for some reason)
//
// Written by surfactants (https://github.com/surfactants)
//
// Please note that this header defines PI in the global namespace.
//
// LICENSE
// -------
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>

#include <cmath>
#include <math.h>

constexpr static float PI { 3.14159265359 };

/// roundFloat ///
/// \brief Rounds a float to the nearest integer
///
int roundFloat(float f);

/// scalarDistance ///
/// \brief Returns the scalar distance between two Vector2<T> (Pythagorean theorem).
///
template <typename T>
T scalarDistance(const sf::Vector2<T> v, const sf::Vector2<T> w)
{
    const T a = std::abs(w.x - v.x);
    const T b = std::abs(w.y - v.y);
    return static_cast<T>(std::sqrt(pow(a, 2) + pow(b, 2)));
}

/// vectorDistance ///
/// \brief Distance between two Vector2<T> (simple subtraction).
///
template <typename T>
sf::Vector2<T> vectorDistance(const sf::Vector2<T> v, const sf::Vector2<T> w)
{
    return sf::Vector2<T>(w.x - v.x, w.y - v.y);
}

/// sign ///
/// \brief Tests the sign of val. Returns +1 if positive, -1 if negative, and 0 if val is 0.
///
template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

/// calculateMoveVector ///
/// \brief
///
sf::Vector2f calculateMoveVector(float angle, float velocity);

/// wrapText ///
/// \brief Introduces newline characters to a text object to fit it within the passed width.
///
void wrapText(sf::Text& text, int width);

void centerText(sf::Text& text);

float calculateAngle(const sf::Vector2f& v, const sf::Vector2f& w);

/////////////////////////////////////////////////////////////
/// \brief
///
sf::Color randomColor(const unsigned int alpha);
sf::Color randomColor();
