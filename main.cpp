
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "balls.h"


int main(int argc, char const** argv)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML window",
                            sf::Style::Close | sf::Style::Titlebar);
    Player player;
    
    Ammunition amo;
    
    Borders level;
    
    
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    //text
    sf::Text name("Bouncing Balls!", font, 50);
    name.setFillColor(sf::Color::Green);
    
    sf::Text score("Balls: " + std::to_string(amo.getSize()), font, 30);
    score.setPosition(400.0, 15.0);
    score.setFillColor(sf::Color::Magenta);
    
    sf::Text endGame("Game Over. Your score: " + std::to_string(amo.getSize()), font, 60);
    endGame.setPosition(100.0, 350.0);
    endGame.setFillColor(sf::Color::Red);
    
    
    //helper variables
    int hit = 0;
    int position = 0;
    int shot_timer = 1000;
    bool game_over = false;
    
    
    // Start the game loop
    while (window.isOpen())
    {
        
        if (!game_over) {
            //not hit
            hit = -1;
            
            // Process events
            sf::Event evnt;
            while (window.pollEvent(evnt))
            {
                // Escape pressed: exit
                if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            if (shot_timer >= 1000) {
                position++;
                amo.fire(position);
                shot_timer = 0;
            }
            
            //bullets continue to move
            amo.moveBullets();
            //movement
            player.move_player(sf::Mouse::getPosition(window));
            //player2.move(move_timer);
            
            //hitting the player
            hit = player.hit();
            //player.update(hit);
            if (hit >= 0) {
                player.damaged();
                game_over = true;
            }
            
            if (position >= 7) {
                position = 0;
            }
            
            score.setString("Balls: " + std::to_string(amo.getSize()));
            endGame.setString("Game Over. Your score: " + std::to_string(amo.getSize()));
            
            shot_timer++;
            
            // Clear screen
            window.clear();
            
            // Draw the sprite
            level.draw(window);
            player.draw(window);
            amo.draw(window);
            
            // Draw the string
            window.draw(name);
            window.draw(score);
            
            // Update the window
            window.display();
        } else {
            
            sf::Event evnt;
            while (window.pollEvent(evnt))
            {
                // Escape pressed: exit
                if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            sf::Text button_text("Play Again", font, 40);
            button_text.setPosition(150.0, 500.0);
            button_text.setFillColor(sf::Color::White);
            sf::RectangleShape button(sf::Vector2f(250.0f, 70.0f));
            button.setPosition(140.0, 490.0);
            button.setFillColor(sf::Color::Transparent);
            button.setOutlineThickness(3.0f);
            button.setOutlineColor(sf::Color::White);
            if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                button.setFillColor(sf::Color(255, 255, 255, 128));
                button_text.setFillColor(sf::Color(0, 0, 0, 255));
            } else {
                button.setFillColor(sf::Color::Transparent);
                button_text.setFillColor(sf::Color::White);
            }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                game_over = false;
                player.reset();
                amo.reset();
            }
            
            // Clear screen
            window.clear();
            
            // Draw the sprite
            level.draw(window);
            player.draw(window);
            amo.draw(window);
            
            
            // Draw the string
            window.draw(name);
            window.draw(score);
            window.draw(endGame);
            window.draw(button);
            window.draw(button_text);
            
            // Update the window
            window.display();
        }
        
    }
    return EXIT_SUCCESS;
}

