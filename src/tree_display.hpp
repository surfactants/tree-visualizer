#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Tree_Display : public sf::Drawable {
public:
    Tree_Display() = default;
    Tree_Display(sf::Font& nfont, sf::RenderWindow& window);

    void set(std::string ntitle, std::string ntext);
    void unset();

    sf::Font* font;

    sf::RectangleShape frame;
    sf::Text title;
    sf::Text text;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
