#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <deque>
#include <map>
#include <termios.h>
#include <unistd.h>
#include <algorithm>

enum class Direction { UP, DOWN, LEFT, RIGHT };

class SnakeGame {
public:
    SnakeGame(int size = 10);

    void run();
    void handleInput();
    std::pair<int,int> getNextHead(std::pair<int,int> current, Direction dir);

private:
    void render();
    void placeFood();
    bool checkCollision(std::pair<int,int> head);

    int boardSize;
    Direction direction;
    std::deque<std::pair<int,int>> snake;
    std::pair<int,int> food;
};

// ---------------- Implementation ----------------

using namespace std;
using namespace std::chrono_literals;

SnakeGame::SnakeGame(int size) : boardSize(size), direction(Direction::RIGHT) {
    snake.push_back({0, 0});
    placeFood();
}

void SnakeGame::placeFood() {
    food = {rand() % boardSize, rand() % boardSize};
}

pair<int,int> SnakeGame::getNextHead(pair<int,int> current, Direction dir) {
    switch (dir) {
        case Direction::RIGHT: return {current.first, (current.second + 1) % boardSize};
        case Direction::LEFT:  return {current.first, current.second == 0 ? boardSize-1 : current.second-1};
        case Direction::DOWN:  return {(current.first + 1) % boardSize, current.second};
        case Direction::UP:    return {current.first == 0 ? boardSize-1 : current.first-1, current.second};
    }
    return current;
}

bool SnakeGame::checkCollision(pair<int,int> head) {
    return find(snake.begin(), snake.end(), head) != snake.end();
}

void SnakeGame::render() {
    cout << "\033[H"; // move cursor to top
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (i == food.first && j == food.second) cout << "🍎";
            else if (find(snake.begin(), snake.end(), make_pair(i,j)) != snake.end()) cout << "🐍";
            else cout << "⬜";
        }
        cout << endl;
    }
    cout << "Length of snake: " << snake.size() << endl;
}

void SnakeGame::handleInput() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    map<char, Direction> keymap = {
        {'d', Direction::RIGHT},
        {'a', Direction::LEFT},
        {'w', Direction::UP},
        {'s', Direction::DOWN}
    };

    while (true) {
        char input = getchar();
        if (input == 'q') exit(0);
        if (keymap.find(input) != keymap.end()) {
            direction = keymap[input];
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void SnakeGame::run() {
    system("clear");
    pair<int,int> head = {0,1};

    while (true) {
        head = getNextHead(head, direction);

        if (checkCollision(head)) {
            system("clear");
            cout << "Game Over" << endl;
            exit(0);
        } else if (head == food) {
            snake.push_back(head);
            placeFood();
        } else {
            snake.push_back(head);
            snake.pop_front();
        }

        render();
        this_thread::sleep_for(500ms);
    }
}

#endif
