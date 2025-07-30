////////////////////////////////////////////////////////////
// SHELL
// ----------
// External abstraction layer for SFML programs.
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

#include <shell.hpp>

#include <database.hpp>
#include <primordial.hpp>

Shell::Shell()
    : window { sf::VideoMode(), "treeviz", sf::Style::Fullscreen, sf::ContextSettings(0, 0, 4) }
{
    font.loadFromFile("adventpro-bold.ttf");

    view.setSize(sf::Vector2f(window.getSize()));
    view.setCenter(sf::Vector2f(window.getSize()) / 2.f);

    Database database;

    std::map<unsigned short int, Node_Data> nodes = database.getNodes();

    float xp = 0.05f,
          yp = 0.1f,
          xs = 0.7f,
          ys = 0.8f;
    sf::View tree_view;
    tree_view.setViewport(sf::FloatRect(xp,yp,xs,ys));
    tree_view.setSize(sf::Vector2f(window.getSize().x*xs, window.getSize().y*ys));
    tree_view.setCenter(sf::Vector2f(0.f, 0.f));

    tree = Tree_Visualizer(font, nodes, tree_view);

    xp = 0.77f * window.getSize().x;
    yp = 0.10f * window.getSize().y;
    xs = 0.21f * window.getSize().x;
    ys = 0.80f * window.getSize().y;

    tree.setDisplayPosition(sf::Vector2f(xp, yp));
    tree.setDisplaySize(sf::Vector2f(xs, ys));
}

void Shell::run()
{
    while(window.isOpen()) {
        update();
        input();
        draw();
    }
}

void Shell::update()
{
    const sf::Vector2i mpos = sf::Mouse::getPosition();
    const sf::Vector2f tree_mpos = window.mapPixelToCoords(mpos, tree.view);
    tree.update(tree_mpos);
}

void Shell::input()
{
    while(window.pollEvent(event)) {
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            else if (event.key.code == sf::Keyboard::R) {
                randomColors();
            }
        }
        else {
            tree.checkMouse(event);
        }
    }
}

void Shell::randomColors()
{
    tree.setNodeFillColor(randomColor());
    tree.setNodeTextColor(randomColor());

    tree.setNodeHiFillColor(randomColor());
    tree.setNodeHiTextColor(randomColor());

    tree.setNodeSelFillColor(randomColor());
    tree.setNodeSelTextColor(randomColor());

    tree.setLineColor(randomColor());

    tree.setFrameColor(randomColor());
    tree.setTitleColor(randomColor());

    tree.setDisplayFrameColor(randomColor());
    tree.setDisplayTextColor(randomColor());
}

void Shell::draw()
{
    window.clear();
        window.setView(view);
        window.draw(tree);
    window.display();
}
