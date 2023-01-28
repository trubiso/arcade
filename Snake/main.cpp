#include "Snake.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

const unsigned MAX_X = 20;
const unsigned MAX_Y = 10;

void generate_random_food(Snake &snake, unsigned &food_x, unsigned &food_y) {
  auto x = rand() % MAX_X;
  auto y = rand() % MAX_Y;
  while (snake.intersects_with_coords(x, y)) {
    x = rand() % MAX_X;
    y = rand() % MAX_Y;
  }
  food_x = x;
  food_y = y;
  // TODO: solve potential infinite loop
}

int snake_main() {
  srand(time(NULL));

  Snake snake{};
  snake.add_node(3, 3);

  unsigned food_x = 0;
  unsigned food_y = 0;
  auto check_food = [&](unsigned x, unsigned y) {
    if (x != food_x || y != food_y) return false;
    generate_random_food(snake, food_x, food_y);
    return true;
  };

  auto direction = SnakeDirection::RIGHT;

  bool should_close = false;
  while (!should_close) {
    // TODO: be efficient
    clear();
    snake.print(direction);
    mvprintw(food_y, food_x, "@");
    if (snake.intersects_with_self()) {
      timeout(-1);
      getch();
      timeout(200);
      // TODO: game over screen, highscores, etc
      break;
    }
    auto input = getch();
    switch (input) {
      case KEY_UP:    if (direction != SnakeDirection::DOWN)  direction = SnakeDirection::UP;    break;
      case KEY_LEFT:  if (direction != SnakeDirection::RIGHT) direction = SnakeDirection::LEFT;  break;
      case KEY_DOWN:  if (direction != SnakeDirection::UP)    direction = SnakeDirection::DOWN;  break;
      case KEY_RIGHT: if (direction != SnakeDirection::LEFT)  direction = SnakeDirection::RIGHT; break;

      case 'q': return 0;
    }
    snake.move_snake(direction, MAX_X, MAX_Y, check_food);
  }
  return 0;  
}
