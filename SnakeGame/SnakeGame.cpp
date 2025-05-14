#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
const int Width = 800;
const int Height = 600;
const int Grid = 20;  // block size
const int maxSize = 100;
int num = 10;
char dir;
using namespace sf;

struct Snake {
    int x;
    int y;
} snake[maxSize];

struct food {
    int x;
    int y;
} fruit;
void gameloop(RenderWindow& window) {
    // draw snake until max size;
    for (int i = num-1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    if (dir == 'd') snake[0].y += 1;
    if (dir == 'l') snake[0].x -= 1;
    if (dir == 'r') snake[0].x += 1;
    if (dir == 'u') snake[0].y -= 1;
    // check eating fruit
    if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
        num++;
        fruit.x = rand() % Width; 
        fruit.y = rand() % Height;
    }
    // Check wall collisions
    if (snake[0].x < 0 || snake[0].x >= Width / Grid || snake[0].y < 0 || snake[0].y >= Height / Grid)
        window.close();  // or reset game

    // Check self collision
    for (int i = 1; i < num; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            window.close();  // or reset game
    }
}
int main() {
    sf::RenderWindow window(sf::VideoMode(Width, Height), "Snake Game");
    // r --> right , l--> left , u--> up , d--> down
    dir = 'r';
    Clock clk;
    float timer = 0, delay = 0.1f;
    Texture t1, t2;
   // t1.loadFromFile("images/white.png");
    if (!t2.loadFromFile("green.png")) {
        std::cerr << "Error loading green.png. Make sure it's in the same directory.\n";
        return -1;
    }

  //  Sprite sprite1(t1);
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
        window.display();
    }

    return 0;
}
