#include <SFML/Graphics.hpp>
#include "ParticleSystem.hpp"
#include <iostream>

int main(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "Particles");
    sf::RectangleShape rectangle, rectangle2;

    ParticleSystem particles(1000);
    sf::Clock clock;



    sf::View view1(sf::FloatRect(0, 0, 800, 600));
    sf::View view2(sf::FloatRect(800, 0, 800, 600));

    //sf::View standard = window.getView();
    unsigned int size = 100;
    sf::View minimap(sf::FloatRect(view2.getCenter().x, view2.getCenter().y, size, window.getSize().y*size/window.getSize().x));
    minimap.setViewport(sf::FloatRect(1.f-(1.f*minimap.getSize().x)/window.getSize().x-0.02f, 1.f-(1.f*minimap.getSize().y)/window.getSize().y-0.02f, (1.f*minimap.getSize().x)/window.getSize().x, (1.f*minimap.getSize().y)/window.getSize().y));
    minimap.zoom(4.f);

view1.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

// joueur 2 (côté droit de l'écran)
view2.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));


    rectangle.setOutlineThickness(3);
    rectangle.setOutlineColor(sf::Color(0, 0, 0, 255));
    rectangle.setSize({50.f, 50.f});
    rectangle.setPosition({500.f, 500.f});
    rectangle.setFillColor(sf::Color::Red);

    rectangle2.setOutlineThickness(3);
    rectangle2.setOutlineColor(sf::Color(0, 0, 0, 255));
    rectangle2.setSize({500.f, 500.f});
    rectangle2.setPosition({800.f, 0.f});
    rectangle2.setFillColor(sf::Color::Blue);

    sf::Vector2f mouse;

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                rectangle.move(-7, 0);
                //view1.setCenter(rectangle.getPosition());
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    mouse = {rectangle.getPosition().x+(rectangle.getSize().x/2), rectangle.getPosition().y+(rectangle.getSize().y/2)};
                rectangle.move(+7,0);
                view1.setCenter(rectangle.getPosition());
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                rectangle.move(0,-7);
                //view1.setCenter(rectangle.getPosition());
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                rectangle.move(0,+7);
                //view1.setCenter(rectangle.getPosition());
            }
        }




        particles.setEmitter(mouse);
        //particles.setEmitter(window.mapPixelToCoords((sf::Vector2i)mouse));

        sf::Time elapsed = clock.restart();
        particles.update(elapsed);


        window.clear();
        //window.setView(standard);
        window.setView(view1);
        window.draw(rectangle);
        window.draw(particles);

        window.setView(view2);
        window.draw(rectangle2);

        window.setView(minimap);
        window.draw(rectangle2);
        //window.draw(particles);
        window.display();
    }

    return 0;
}
