#include <tree.hpp>
#include <iostream>

//////////////////////////////////////////////
Tree_Display::Tree_Display(sf::Font& nfont, sf::RenderWindow& window)
: font{ &nfont }
{

    float xp = 0.76f * window.getSize().x,
          yp = 0.10f * window.getSize().y,
          xs = 0.19f * window.getSize().x,
          ys = 0.80f * window.getSize().y;

    frame.setPosition(sf::Vector2f(xp, yp));
    frame.setSize(sf::Vector2f(xs, ys));
    frame.setFillColor(sf::Color::Green);

    title.setFont(*font);
    title.setPosition(sf::Vector2f(xp, yp));
    title.setString("...");
    title.setFillColor(sf::Color::Black);

    text.setFont(*font);
    text.setPosition(sf::Vector2f(xp, yp + 64.f));
    text.setString("...");
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

    //wrap
}

void Tree_Display::unset()
{
    title.setString("...");
    text.setString("select a node to learn more");
}

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
    frame.setFillColor(sf::Color(90, 10, 30));
    frame.setPosition(16.f, 16.f);

    if(nodes.count(0)){
        root = new Node(font, nodes.at(0), nodes);
    }
    else{
        std::cout << "no root node found!";
        return;
    }

    root->placeChildren(sf::Vector2f(0.f, 0.f));
    root->connectChildren();

    display = Tree_Display(font, *window);
}

void Tree::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(title, states);
    target.draw(display, states);

    target.setView(view);
    target.draw(frame, states);
    target.draw(*root, states);
}

void Tree::update()
{
    sf::Vector2f mpos = window->mapPixelToCoords(sf::Mouse::getPosition(*window), view);

    root->checkMouse(mpos);
}

void Tree::checkMouse(sf::Event& event){
    bool dragCheck = (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Middle));

    if(dragging){
        if(!dragCheck){
            dragging = false;
        }
        else{
            drag();
        }
    }
    else{
        if(dragCheck){
            dragging = true;
            drag_pos = sf::Vector2f(sf::Mouse::getPosition());
        }
        else if(event.type == sf::Event::MouseButtonReleased){
            if(event.mouseButton.button == sf::Mouse::Left){
                Node* clicked = root->checkClick();
                if(clicked != nullptr){
                    display.set(std::to_string(clicked->id), clicked->data);
                }
                else display.unset();
            }
        }
        else if(event.type == sf::Event::MouseWheelScrolled){
            zoom(event.mouseWheelScroll.delta);
        }
    }
}

void Tree::zoom(float delta){
    if(delta > 0) delta = -0.2f;
    else if(delta < 0) delta = 0.2f;
    else return;

    float target = zoom_level + delta;
    float factor = target / zoom_level;
    view.zoom(factor);
    zoom_level = factor;
}

void Tree::drag(){
    sf::Vector2f mpos(sf::Mouse::getPosition());
        //window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
    view.move(drag_pos - mpos);
    drag_pos = mpos;
}
