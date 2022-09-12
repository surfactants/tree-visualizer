#include <tree_display.hpp>
#include <primordial.hpp>

//////////////////////////////////////////////
Tree_Display::Tree_Display(sf::Font& nfont, sf::RenderWindow& window)
: font{ &nfont }
{

    float xp = 0.77f * window.getSize().x,
          yp = 0.10f * window.getSize().y,
          xs = 0.21f * window.getSize().x,
          ys = 0.80f * window.getSize().y;

    frame.setPosition(sf::Vector2f(xp, yp));
    frame.setSize(sf::Vector2f(xs, ys));
    frame.setFillColor(sf::Color(216, 216, 216));

    xp += 12.f;
    yp += 4.f;

    title.setFont(*font);
    title.setPosition(sf::Vector2f(xp, yp));
    title.setFillColor(sf::Color::Black);

    yp += 48.f;

    text.setFont(*font);
    text.setPosition(sf::Vector2f(xp, yp));
    text.setFillColor(sf::Color::Black);

    unset();
}

void Tree_Display::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    target.draw(title, states);
    target.draw(text, states);
}

void Tree_Display::set(std::string ntitle, std::string ntext)
{
    title.setString(ntitle);
    text.setString(ntext);

    wrapText(text, frame.getSize().x - 24.f);
}

void Tree_Display::unset()
{
    title.setString("...");
    text.setString("select a node to learn more");
}
