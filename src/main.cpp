#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({1200, 900}), "Window game test");
    sf::Texture texture;

    if (!texture.loadFromFile("../../assets/pexel.png"))
    {
        std::cout << "problem with image loading" << std::endl;
        return 1 ;
    }
    sf::Sprite sprite(texture);

    // afficher sprite 250px vers la droite et vers le bas
    sprite.setPosition({250.f, 250.f});

    //run program as long the window is open
    while(window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);

        // end current frame
        window.display();
    }

    return 0 ;
}

/*

*/