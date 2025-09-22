#include <gtest/gtest.h>
#include "snake.h"

TEST(SnakeGameTest, NextHeadRight) {
    SnakeGame game(10);
    auto current = std::make_pair(2, 2);
    EXPECT_EQ(game.getNextHead(current, Direction::RIGHT), std::make_pair(2, 3));
}

TEST(SnakeGameTest, NextHeadLeft) {
    SnakeGame game(10);
    auto current = std::make_pair(2, 2);
    EXPECT_EQ(game.getNextHead(current, Direction::LEFT), std::make_pair(2, 1));
}

TEST(SnakeGameTest, NextHeadUp) {
    SnakeGame game(10);
    auto current = std::make_pair(2, 2);
    EXPECT_EQ(game.getNextHead(current, Direction::UP), std::make_pair(1, 2));
}

TEST(SnakeGameTest, NextHeadDown) {
    SnakeGame game(10);
    auto current = std::make_pair(2, 2);
    EXPECT_EQ(game.getNextHead(current, Direction::DOWN), std::make_pair(3, 2));
}

/** 
 * g++ -o my_tests snake_test.cpp -lgtest -lgtest_main -pthread;
 * This command is a two-part shell command. Let's break it down.

  The first part is the compilation:
  g++ -o my_tests hello_gtest.cpp -lgtest -lgtest_main -pthread


   * g++: This invokes the GNU C++ compiler.
   * -o my_tests: This tells the compiler to create an executable file named
     my_tests.
   * hello_gtest.cpp: This is the C++ source file containing your tests.
   * -lgtest: This links the Google Test library, which provides the core testing
     framework.
   * -lgtest_main: This links a pre-compiled main function provided by Google
     Test, which saves you from writing your own main() to run the tests.
   * -pthread: This links the POSIX threads library, which is required by Google
     Test for its operation.
 * 
*/
