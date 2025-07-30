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

#include <node_info_display.hpp>

#include <primordial.hpp>

//////////////////////////////////////////////
Node_Info_Display::Node_Info_Display(sf::Font& font)
{
    frame.setFillColor(sf::Color(216, 216, 216));

    title.setFont(font);
    title.setFillColor(sf::Color::Black);

    text.setFont(font);
    text.setFillColor(sf::Color::Black);

    unset();
}

void Node_Info_Display::setPosition(const sf::Vector2f& pos)
{
    frame.setPosition(pos);

    const static sf::Vector2f title_offset(12.f, 4.f);
    title.setPosition(pos + title_offset);

    const static sf::Vector2f text_offset = title_offset + sf::Vector2f(0.f, 48.f);
    text.setPosition(pos + text_offset);
}

void Node_Info_Display::setSize(const sf::Vector2f& size)
{
    frame.setSize(size);
}

void Node_Info_Display::set(std::string ntitle, std::string ntext)
{
    title.setString(ntitle);
    text.setString(ntext);

    wrapText(text, frame.getSize().x - 24.f);
}

void Node_Info_Display::unset()
{
    title.setString("...");
    text.setString("select a node to learn more");
}

void Node_Info_Display::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    target.draw(title, states);
    target.draw(text, states);
}
