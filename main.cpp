#include <SFML/Graphics.hpp>
#include "ParticleSystem.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "Particles");
    sf::RectangleShape rectangle, rectangle2, nexus;

    ParticleSystem particles(1000);
    sf::Clock clock;

    sf::Vector2i screenDimensions(800, 600);
    sf::Vector2i blockDimensions(10, 10);

    sf::View view1(sf::FloatRect(0, 0, 800, 600));
    sf::View view2(sf::FloatRect(800, 0, 800, 600));

    sf::View standard = window.getView();
    unsigned int size = 100;
    sf::View minimap(sf::FloatRect(0, 0, 800, 600));
    //sf::View minimap(sf::FloatRect(view1.getCenter().x, view1.getCenter().y, size, window.getSize().y*size/window.getSize().x));
    //minimap.setViewport(sf::FloatRect(1.f-(1.f*minimap.getSize().x)/window.getSize().x-0.02f, 1.f-(1.f*minimap.getSize().y)/window.getSize().y-0.02f, (1.f*minimap.getSize().x)/window.getSize().x, (1.f*minimap.getSize().y)/window.getSize().y));
    minimap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
    minimap.zoom(2.f);
    //view1.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

    // joueur 2 (côté droit de l'écran)
    //view2.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));


    rectangle.setOutlineThickness(3);
    rectangle.setOutlineColor(sf::Color(0, 0, 0, 255));
    rectangle.setSize({50.f, 50.f});
    rectangle.setPosition({400.f, 300.f});
    rectangle.setFillColor(sf::Color::Red);

    rectangle2.setOutlineThickness(3);
    rectangle2.setOutlineColor(sf::Color(0, 0, 0, 255));
    rectangle2.setSize({500.f, 500.f});
    rectangle2.setPosition({800.f, 0.f});
    rectangle2.setFillColor(sf::Color::Blue);

    int x = rand()%(800-800*2)+800;
    int y = rand()%(600-0)+0;
    nexus.setSize({100.f, 100.f});
     std::cout << x << " , " << y << std::endl;
    nexus.setPosition({400.f, 300.f});

    sf::Vector2f mouse;
    //view1.setCenter(rectangle.getPosition());

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                rectangle.move(-7, 0);
                mouse = {rectangle.getPosition().x+(rectangle.getSize().x/2), rectangle.getPosition().y+(rectangle.getSize().y/2)};

                view1.setCenter(rectangle.getPosition());
                std::cout << rectangle.getPosition().x << " , " << rectangle.getPosition().y << std::endl;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                mouse = {rectangle.getPosition().x+(rectangle.getSize().x/2), rectangle.getPosition().y+(rectangle.getSize().y/2)};
                rectangle.move(+7,0);
                view1.setCenter(rectangle.getPosition());
                std::cout << rectangle.getPosition().x << " , " << rectangle.getPosition().y << std::endl;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                mouse = {rectangle.getPosition().x+(rectangle.getSize().x/2), rectangle.getPosition().y+(rectangle.getSize().y/2)};
                rectangle.move(0,-7);
                view1.setCenter(rectangle.getPosition());
                std::cout << rectangle.getPosition().x << " , " << rectangle.getPosition().y << std::endl;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                mouse = {rectangle.getPosition().x+(rectangle.getSize().x/2), rectangle.getPosition().y+(rectangle.getSize().y/2)};
                rectangle.move(0,+7);
                view1.setCenter(rectangle.getPosition());
                std::cout << rectangle.getPosition().x << " , " << rectangle.getPosition().y << std::endl;
            }
        }

        particles.setEmitter(mouse);
        //particles.setEmitter(window.mapPixelToCoords((sf::Vector2i)mouse));

        sf::Time elapsed = clock.restart();
        particles.update(elapsed);


        window.clear();
        window.setView(view1);

        for(int i = 0;i<nexus.getSize().x/blockDimensions.x; i++){
            for(int j = 0;j<nexus.getSize().y/blockDimensions.y;j++){
                sf::VertexArray vArray(sf::PrimitiveType::Quads, 4);
                vArray[0].position = sf::Vector2f(i*blockDimensions.x+nexus.getPosition().x, j*blockDimensions.y+nexus.getPosition().y);
                vArray[1].position = sf::Vector2f(i*blockDimensions.x+blockDimensions.x+nexus.getPosition().x, j*blockDimensions.y+nexus.getPosition().y);
                vArray[2].position = sf::Vector2f(i*blockDimensions.x+blockDimensions.x+nexus.getPosition().x, j*blockDimensions.y+blockDimensions.y+nexus.getPosition().y);
                vArray[3].position = sf::Vector2f(i*blockDimensions.x+nexus.getPosition().x, j*blockDimensions.y+blockDimensions.y+nexus.getPosition().y);

                for(int k=0;k<4;k++){
                    int red = rand() % 255;
                    int green = rand() % 255;
                    int blue = rand() % 255;

                    vArray[k].color = sf::Color(red, green, blue);
                }
                window.draw(vArray);
            }
        }


        //window.clear();

        window.setView(standard);
        window.draw(particles);
        window.draw(rectangle);

        //window.draw(rectangle2);
        //window.setView(view2);
        //window.draw(rectangle2);

        window.setView(minimap);
        window.draw(particles);
        window.draw(rectangle);

        window.display();
    }

    return 0;
}
