#include "Chooser.h"
#include "Pairs.h"
#include "Snake/main.h"
#include <ncurses.h>

int main(void) {
  initscr();
  start_color();
  if (!has_colors()) return -1;
  init_custom_pairs();
  noecho();
  timeout(200);
  keypad(stdscr, true);
  setlocale(LC_ALL, "");
  curs_set(0);

  bool should_close = false;

  Chooser chooser{};
  chooser.add_item("Snake", [&]() { snake_main(); return false; });
  chooser.add_item("Tetris", [&]() { return false; });
  chooser.add_item("Breakout", [&]() { return false; });
  // TODO: options. options = timeout, perhaps color pairs?
  chooser.add_item("Exit", [&]() {
    should_close = true;
    return true;
  });
 
  while (!should_close) {
    chooser.prompt_user("Choose a game");
  }

  endwin();
}
