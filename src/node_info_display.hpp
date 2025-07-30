////////////////////////////////////////////////////////////
// NODE_INFO_DISPLAY
// ----------
// Provides an info panel for displaying information from Tree_Visualizer::Node types.
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

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Node_Info_Display : public sf::Drawable {
public:
    Node_Info_Display() = default;
    Node_Info_Display(sf::Font& font);

    void set(std::string ntitle, std::string ntext);
    void unset();

    void setPosition(const sf::Vector2f& pos);
    void setSize(const sf::Vector2f& size);

    sf::RectangleShape frame;
    sf::Text title;
    sf::Text text;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
