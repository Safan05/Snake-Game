#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
const int Width = 800;
const int Height = 600;
const int Grid = 20;  // block size
const int maxSize = 100;
int num = 4;
int speed = 1;
int score = 0;
float delay = 0.1f;
char dir;
using namespace sf;

struct Snake {
    int x;
    int y;
} snake[maxSize];

struct Food {
    int x;
    int y;
} fruit;
void gameloop(RenderWindow& window) {
    // draw snake until max size;
    for (int i = num-1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    if (dir == 'd') snake[0].y += speed;
    if (dir == 'l') snake[0].x -= speed;
    if (dir == 'r') snake[0].x += speed;
    if (dir == 'u') snake[0].y -= speed;
    // check eating fruit
    if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
        num++;
        score++;
        if ((score % 7 == 0) && delay > 0.03f) {
            delay -= 0.01f;  
        }
        fruit.x = rand() % (Width / Grid);
        fruit.y = rand() % (Height / Grid);
    }
    // Check wall collisions
    if (snake[0].x < 0) {
        snake[0].x = (Width / Grid)-1;
        dir = 'l';
    }
    if (snake[0].x >= Width / Grid) {
        snake[0].x =  0;
        dir = 'r';
    }
    if (snake[0].y < 0) {
        snake[0].y = (Height / Grid)-1;
        dir = 'u';
    }
    if (snake[0].y >= Height / Grid) {
        snake[0].y = 0;
        dir = 'd';
    }
    // Check self collision
    for (int i = 1; i < num; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            int z = 9;
    }
}
int main() {
    sf::RenderWindow window(sf::VideoMode(Width, Height), "Snake Game");
    // r --> right , l--> left , u--> up , d--> down
    dir = 'r';
    Clock clk;
    float timer = 0;
    Texture t1, t2;
    fruit.x = rand() % (Width/Grid);
    fruit.y = rand() % (Height/Grid);
    if (!t1.loadFromFile("white.png")) {
        std::cerr << "Error loading white.png. Make sure it's in the same directory.\n";
        return -1;
    }
    if (!t2.loadFromFile("green.png")) {
        std::cerr << "Error loading green.png. Make sure it's in the same directory.\n";
        return -1;
    }

    Sprite food(t1);
    Sprite player(t2);
    int startX = 15;
    for (int i = 0; i < num; i++) {
        snake[i].x = startX - i;
        snake[i].y = 10;
    }

    while (window.isOpen()) {    
        Event event;
        float time = clk.getElapsedTime().asSeconds();
        clk.restart();
        timer += time;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 'r') dir = 'l';
        if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 'l') dir = 'r';
        if (Keyboard::isKeyPressed(Keyboard::Up) && dir != 'd') dir = 'u';
        if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 'u') dir = 'd';

        if (timer > delay) {
            gameloop(window);
            timer = 0;
        }
        window.clear(sf::Color::Black);
        for (int i = 0; i < num; i++)
        {
            player.setPosition(snake[i].x * Grid, snake[i].y * Grid);  
            window.draw(player);
        }
        food.setPosition(fruit.x*Grid,fruit.y*Grid);
        window.draw(food);
        window.display();
    }

    return 0;
}
