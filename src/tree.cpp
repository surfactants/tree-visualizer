#include <tree.hpp>
#include <iostream>

//////////////////////////////////////////////
Tree::Tree(sf::Font& font, std::map<unsigned short int, Node_Data> nodes, sf::RenderWindow& nwindow)
: window{ &nwindow }
{
    title.setString("tree");
    title.setFont(font);

    zoom_level = 1.f;

    float xp = 0.05f,
          yp = 0.1f,
          xs = 0.7f,
          ys = 0.8f;

    view.setViewport(sf::FloatRect(xp,yp,xs,ys));
    view.setSize(sf::Vector2f(window->getSize().x*xs, window->getSize().y*ys));
    view.setCenter(sf::Vector2f(0.f, 0.f));

    sf::Vector2f fsize(4096.f, 4096.f);

    frame.setSize(fsize);
    frame.setOrigin(fsize / 2.f);
    frame.setFillColor(sf::Color(40, 20, 30));
    frame.setPosition(16.f, 16.f);

    if (nodes.count(0)) {
        root = new Node(font, nodes.at(0), nodes);
    }
    else {
        std::cout << "no root node found!";
        return;
    }

    root->placeChildren(sf::Vector2f(0.f, 0.f));
    root->connectChildren();

    display = Tree_Display(font, *window);
}

void Tree::update()
{
    sf::Vector2f mpos = window->mapPixelToCoords(sf::Mouse::getPosition(*window), view);

    root->greedyCheck(mpos);
}

void Tree::checkMouse(sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled) {
        zoom(event.mouseWheelScroll.delta);
        return;
    }

    bool dragCheck = (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Middle));

    if (dragging) {
        if (!dragCheck) {
            dragging = false;
        }
        else {
            drag();
        }
    }
    else {
        if (dragCheck) {
            dragging = true;
            drag_pos = sf::Vector2f(sf::Mouse::getPosition());
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                Node* clicked = root->checkClick();
                if (clicked != nullptr) {
                    display.set(std::to_string(clicked->id), clicked->data);
                }
                else display.unset();
            }
        }
    }
}

void Tree::setFrameColor(const sf::Color& cf)
{
    frame.setFillColor(cf);
}

void Tree::setTitleColor(const sf::Color& ct)
{
    title.setFillColor(ct);
}

void Tree::setNodeFillColor(const sf::Color& c)
{
    Node::fill_color = c;
    root->setFillColor();
}

void Tree::setNodeTextColor(const sf::Color& c)
{
    Node::text_color = c;
    root->setTextColor();
}

void Tree::setNodeHiFillColor(const sf::Color& hc)
{
    Node::hi_fill_color = hc;
    root->setHiFillColor();
}

void Tree::setNodeHiTextColor(const sf::Color& hc)
{
    Node::hi_text_color = hc;
    root->setHiTextColor();
}

void Tree::setNodeSelFillColor(const sf::Color& sc)
{
    Node::sel_fill_color = sc;
    root->setSelFillColor();
}

void Tree::setNodeSelTextColor(const sf::Color& sc)
{
    Node::sel_fill_color = sc;
    root->setSelTextColor();
}

void Tree::setLineColor(const sf::Color& c)
{
    Node::line_color = c;
    root->setLineColor();
}

void Tree::setDisplayFrameColor(const sf::Color& c)
{
    display.frame.setFillColor(c);
}

void Tree::setDisplayTextColor(const sf::Color& c)
{
    display.title.setFillColor(c);
    display.text.setFillColor(c);
}

void Tree::zoom(float delta) {
    if (delta > 0) {
        delta = -0.2f;
    }
    else if (delta < 0) {
        delta = 0.2f;
    }
    else {
        return;
    }

    float target = zoom_level + delta;
    float factor = target / zoom_level;
    view.zoom(factor);
    zoom_level = factor;
}

void Tree::drag() {
    sf::Vector2f mpos(sf::Mouse::getPosition());
        //window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
    view.move((drag_pos - mpos) * 1.25f);
    drag_pos = mpos;
}

void Tree::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(title, states);
    target.draw(display, states);

    target.setView(view);
    target.draw(frame, states);
    target.draw(*root, states);
}
