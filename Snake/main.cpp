#include "Snake.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <cmath>

const unsigned MAX_X = 20;
const unsigned MAX_Y = 10;
const unsigned MAX_TICKS_MAX = 3000;

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
  WINDOW *win = newwin(MAX_Y + 3, MAX_X + 3, 2, 1);
	wtimeout(win, 0);
  keypad(win, true);
  clear();

  Snake snake{};
  snake.add_node(3, 3);

	int food_pieces_eaten = 0;
  unsigned food_x = 0;
  unsigned food_y = 0;

	unsigned max_ticks = MAX_TICKS_MAX;
  unsigned ticks = max_ticks;
	auto check_food = [&](unsigned x, unsigned y) {
    if (x != food_x || y != food_y) return false;
		food_pieces_eaten++;
		max_ticks = (unsigned)((float)MAX_TICKS_MAX / (std::log10(std::sqrt((float)food_pieces_eaten) + 1) + 1));
    generate_random_food(snake, food_x, food_y);
    return true;
  };

  auto direction = SnakeDirection::RIGHT;
	std::queue<SnakeDirection> movements{};

  bool should_close = false;
	while (!should_close) {
    // TODO: be efficient
    snake.print(win, direction, 1, 1);
    mvwprintw(win, food_y + 1, food_x + 1, "@");
    refresh();
    auto input = wgetch(win);
    switch (input) { 
      case KEY_UP:    if ((!movements.size() && direction != SnakeDirection::DOWN) || (movements.size() && movements.back() != SnakeDirection::DOWN))  movements.push(SnakeDirection::UP);    break;
      case KEY_LEFT:  if ((!movements.size() && direction != SnakeDirection::RIGHT) || (movements.size() && movements.back() != SnakeDirection::RIGHT)) movements.push(SnakeDirection::LEFT);  break;
      case KEY_DOWN:  if ((!movements.size() && direction != SnakeDirection::UP) || (movements.size() && movements.back() != SnakeDirection::UP))    movements.push(SnakeDirection::DOWN);  break;
      case KEY_RIGHT: if ((!movements.size() && direction != SnakeDirection::LEFT) || (movements.size() && movements.back() != SnakeDirection::LEFT))  movements.push(SnakeDirection::RIGHT); break;

      case 'q': return 0;
    }
		if (++ticks > max_ticks) {
			wclear(win);
    	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
			if (movements.size()) {
				direction = movements.front();
				movements.pop();
			}
    	snake.move_snake(direction, MAX_X, MAX_Y, check_food);
			if (snake.intersects_with_self()) {
      	timeout(-1);
      	wgetch(win);
      	timeout(200);
      	// TODO: game over screen, highscores, etc
      	break;
    	}
			ticks -= max_ticks;
		}
  }

  delwin(win);

  return 0;
}
