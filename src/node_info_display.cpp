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
