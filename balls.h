//
//  balls.h
//  bouncing_balls
//
//  Created by Ben Wozniak on 5/30/20.
//  Copyright © 2020 Ben Wozniak. All rights reserved.
//

#ifndef Helpers_h
#define Helpers_h
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>


float EPSILON = 0.0001;
float shot_speed = 0.2;
float move_speed = 0.4;
int up = 1;
int down = 3;
int left = 4;
int right = 2;
int none = 0;




class Borders {
public:
    
    Borders() {
        sf::RectangleShape farLeft(sf::Vector2f(5.0f, 700.0f));
        farLeft.setFillColor(sf::Color::White);
        farLeft.setPosition(60.0f, 60.0f);
        walls.push_back(farLeft);
        
        sf::RectangleShape bottom(sf::Vector2f(750.0f, 5.0f));
        bottom.setFillColor(sf::Color::White);
        bottom.setPosition(60.0f, 760.0f);
        walls.push_back(bottom);
        
        sf::RectangleShape farRight(sf::Vector2f(5.0f, 700.0f));
        farRight.setFillColor(sf::Color::White);
        farRight.setPosition(810.0f, 60.0f);
        walls.push_back(farRight);
        
        sf::RectangleShape top(sf::Vector2f(750.0f, 5.0f));
        top.setFillColor(sf::Color::White);
        top.setPosition(60.0f, 60.0f);
        walls.push_back(top);
        
        
    }
    
    
    int getSize() {
        return walls.size();
    }
    
    
    bool collide(sf::FloatRect main) {
        for (auto i:walls) {
            if (main.intersects(i.getGlobalBounds())) {
                return true;
            }
        }
        return false;
    }
    
    
    void draw(sf::RenderWindow &window) {
        for (auto i:walls) {
            window.draw(i);
        }
    }
    
private:
    std::vector<sf::RectangleShape> walls;
};



class Bullets {
public:
    Bullets() {
        bullet.setRadius(3.0f);
        bullet.setOrigin(3.0f, 3.0f);
        bullet.setFillColor(sf::Color::Cyan);
        direction = sf::Vector2f(0, 0);
        bounced = false;
    }
    
    void fire(sf::Vector2f position) {
        direction = position;
        bullet.setPosition(800.0, 70.0);
    }
    
    sf::Vector2f perpDirection() {
        return sf::Vector2f(direction.x, -direction.y);
    }
    
    void move() {
        //   direction = sf::Vector2f(1.0, 1.0);
        bullet.move(direction);
    }
    
    bool getBounced() {
        return bounced;
    }
    
    void bounce() {
        sf::RectangleShape left(sf::Vector2f(1.0, 1.0));
        left.setPosition(bullet.getPosition().x - 4, bullet.getPosition().y);
        
        sf::RectangleShape right(sf::Vector2f(1.0, 1.0));
        right.setPosition(bullet.getPosition().x + 4, bullet.getPosition().y);
        
        sf::RectangleShape top(sf::Vector2f(1.0, 1.0));
        top.setPosition(bullet.getPosition().x, bullet.getPosition().y - 4);
        
        sf::RectangleShape bottom(sf::Vector2f(1.0, 1.0));
        bottom.setPosition(bullet.getPosition().x, bullet.getPosition().y + 4);
        
        if (walls.collide(left.getGlobalBounds()) || walls.collide(right.getGlobalBounds())) {
            direction = sf::Vector2f(direction.x * -1, direction.y);
        } else if (walls.collide(top.getGlobalBounds()) || walls.collide(bottom.getGlobalBounds())) {
            direction = sf::Vector2f(direction.x, direction.y * -1);
        }
        //bounced = true;
    }
    
    sf::FloatRect getBounds() {
        return bullet.getGlobalBounds();
    }
    
    bool will_hit(sf::RectangleShape target) {
        sf::Vector2f size = target.getSize();
        sf::Vector2f goal = target.getPosition();
        sf::Vector2f position = bullet.getPosition();
        sf::Vector2f tradectory = sf::Vector2f(goal.x - position.x, goal.y - position.y);
        float distance = sqrt((tradectory.x * tradectory.x) + (tradectory.y * tradectory.y));
        float scale = distance / sqrt((direction.x * direction.x) + (direction.y * direction.y));
        sf::Vector2f end = sf::Vector2f(position.x + (direction.x * scale), position.y + (direction.y * scale));
        sf::CircleShape endShape(3.0);
        endShape.setOrigin(3.0, 3.0);
        endShape.setPosition(end);
        if (target.getGlobalBounds().intersects(endShape.getGlobalBounds())) {
            return true;
        }
        
        goal = sf::Vector2f(goal.x - (size.x / 2), goal.y - (size.y / 2));
        position = bullet.getPosition();
        tradectory = sf::Vector2f(goal.x - position.x, goal.y - position.y);
        distance = sqrt((tradectory.x * tradectory.x) + (tradectory.y * tradectory.y));
        scale = distance / sqrt((direction.x * direction.x) + (direction.y * direction.y));
        end = sf::Vector2f(position.x + (direction.x * scale), position.y + (direction.y * scale));
        endShape.setPosition(end);
        if (target.getGlobalBounds().intersects(endShape.getGlobalBounds())) {
            return true;
        }
        
        goal = sf::Vector2f(goal.x + (size.x / 2), goal.y - (size.y / 2));
        position = bullet.getPosition();
        tradectory = sf::Vector2f(goal.x - position.x, goal.y - position.y);
        distance = sqrt((tradectory.x * tradectory.x) + (tradectory.y * tradectory.y));
        scale = distance / sqrt((direction.x * direction.x) + (direction.y * direction.y));
        end = sf::Vector2f(position.x + (direction.x * scale), position.y + (direction.y * scale));
        endShape.setPosition(end);
        if (target.getGlobalBounds().intersects(endShape.getGlobalBounds())) {
            return true;
        }
        
        goal = sf::Vector2f(goal.x - (size.x / 2), goal.y + (size.y / 2));
        position = bullet.getPosition();
        tradectory = sf::Vector2f(goal.x - position.x, goal.y - position.y);
        distance = sqrt((tradectory.x * tradectory.x) + (tradectory.y * tradectory.y));
        scale = distance / sqrt((direction.x * direction.x) + (direction.y * direction.y));
        end = sf::Vector2f(position.x + (direction.x * scale), position.y + (direction.y * scale));
        endShape.setPosition(end);
        if (target.getGlobalBounds().intersects(endShape.getGlobalBounds())) {
            return true;
        }
        
        goal = sf::Vector2f(goal.x + (size.x / 2), goal.y + (size.y / 2));
        position = bullet.getPosition();
        tradectory = sf::Vector2f(goal.x - position.x, goal.y - position.y);
        distance = sqrt((tradectory.x * tradectory.x) + (tradectory.y * tradectory.y));
        scale = distance / sqrt((direction.x * direction.x) + (direction.y * direction.y));
        end = sf::Vector2f(position.x + (direction.x * scale), position.y + (direction.y * scale));
        endShape.setPosition(end);
        if (target.getGlobalBounds().intersects(endShape.getGlobalBounds())) {
            return true;
        }
        
        return false;
    }
    
    void draw(sf::RenderWindow &window) {
        window.draw(bullet);
    }
    
    
private:
    Borders walls;
    sf::CircleShape bullet;
    sf::Vector2f direction;
    bool bounced;
};







class Ammunition {
public:
    Ammunition() {
        
    }
    
    void reset() {
        while (amo.size() > 0) {
            amo.pop_back();
        }
    }
    
    void fire(int position) {
        Bullets shot;
        sf::Vector2f direction;
        // takes position, sets to angle, converts angle to radians
        float angle = ((position * 10.0) + 10.0) * (3.1415926535 / 180.0);
        float hypotenuse = shot_speed;
        direction.y = hypotenuse * cos(angle) * -1;
        direction.x = hypotenuse * sin(angle) * -1;
        shot.fire(direction);
        amo.push_back(shot);
    }
    
    void moveBullets() {
        for (int i = 0; i < amo.size(); i++) {
            if (!walls.collide(amo[i].getBounds())) {
                amo[i].move();
            } else {
                if (!amo[i].getBounced()) {
                    amo[i].bounce();
                    amo[i].move();
                } else {
                    update(i);
                }
            }
        }
    }
    
    bool will_hit(sf::RectangleShape target) {
        for (int i = 0; i < amo.size(); i++) {
            if (amo[i].will_hit(target)) {
                return true;
            }
        }
        return false;
    }
    
    void draw(sf::RenderWindow &window) {
        for (auto i:amo) {
            i.draw(window);
        }
    }
    
    int collide(sf::FloatRect main) {
        for (int i = 0; i < amo.size(); i++) {
            if (main.intersects(amo[i].getBounds())) {
                return i;
            }
        }
        return -1;
    }
    
    void update(int position) {
        if (position >= 0) {
            amo.erase(amo.begin() + position);
        }
    }
    
    int getSize() {
        return amo.size();
    }
    
private:
    static std::vector<Bullets> amo;
    Borders walls;
};

std::vector<Bullets> Ammunition::amo = {};





class Player {
public:
    
    
    void reset() {
        player.setSize(sf::Vector2f(30.0f, 30.0f));
        player.setFillColor(sf::Color::Blue);
        player.setOrigin(15.0f, 15.0f);
        player.setPosition(100.0f, 100.0f);
    }
    
    Player() {
        reset();
    }
    
    void move_player(sf::Vector2i location) {
        sf::Vector2f position = static_cast<sf::Vector2f>(location);
        sf::Vector2f Location = player.getPosition();
        
        //checks if mouse is inside border
        if (position.x > (60.0 + 5.0 + (player.getSize().x / 2.0)) && position.x < (810.0 - (player.getSize().x / 2.0))) {
            Location.x = position.x;
        }
        if (position.y > (60.0 + 5.0 + (player.getSize().y / 2.0)) && position.y < (760.0 - (player.getSize().y / 2.0))) {
            Location.y = position.y;
        }
        player.setPosition(Location);
    }
    
    
    int hit() {
        return weapons.collide(player.getGlobalBounds());
    }
    
    void damaged() {
        player.setFillColor(sf::Color::Red);
    }
    
    
    void Unhit() {
        player.setFillColor(sf::Color::Blue);
    }
    
    void update(int position) {
        weapons.update(position);
    }
    
    
    sf::FloatRect getBounds() {
        return player.getGlobalBounds();
    }
    
    sf::Vector2f getLocation() {
        return player.getPosition();
    }
    
    void draw(sf::RenderWindow &window) {
        window.draw(player);
        weapons.draw(window);
    }
    
private:
    sf::RectangleShape player;
    Ammunition weapons;
};






#endif /* Helpers_h */
