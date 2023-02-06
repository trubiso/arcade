#include "Snake.h"
#include <vector>
#include <utility>
#include <algorithm>

void Snake::add_node(unsigned x, unsigned y) {
  auto node = new SnakeNode{nullptr, x, y};
  if (this->last != nullptr)
    this->last->next = node;
  else
    this->first = node;
  this->last = node;
  this->length++;
}

void Snake::remove_tail() {
  if (this->first == nullptr) return; // this shouldn't happen!
  auto old_first = this->first;
  this->first = this->first->next;
  delete old_first;
  this->length--;
}

void Snake::move_snake(SnakeDirection direction, unsigned max_x, unsigned max_y, std::function<bool(unsigned, unsigned)> check_food) {
  if (this->last == nullptr) return;
  auto new_x = this->last->x;
  auto new_y = this->last->y;
  switch (direction) {
    case SnakeDirection::UP:
      if (new_y == 0) new_y = max_y;
      else new_y--;
      break;
    case SnakeDirection::LEFT:
      if (new_x == 0) new_x = max_x;
      else new_x--;
      break;
    case SnakeDirection::DOWN:
      if (new_y == max_y) new_y = 0;
      else new_y++;
      break;
    case SnakeDirection::RIGHT:
      if (new_x == max_x) new_x = 0;
      else new_x++;
      break;
  }

  bool is_food = check_food(new_x, new_y);
  add_node(new_x, new_y);
  if (!is_food) remove_tail();
}

void Snake::print(WINDOW *win, SnakeDirection last_direction, unsigned x_off, unsigned y_off) const {
  auto element = this->first;
  while (element->next != nullptr) {
    mvwaddwstr(win, element->y + y_off, element->x + x_off, L"█");
    element = element->next;
  }
  char last_char = '^';
  switch (last_direction) {
    case SnakeDirection::UP: last_char = '^'; break;
    case SnakeDirection::LEFT: last_char = '<'; break;
    case SnakeDirection::DOWN: last_char = 'V'; break;
    case SnakeDirection::RIGHT: last_char = '>'; break;
  }
  mvwprintw(win, element->y + y_off, element->x + x_off, "%c", last_char);
}

bool Snake::intersects_with_coords(unsigned x, unsigned y) const {
  // TODO: generalize applying function on every elem in snake
  auto element = this->first;
  while (element->next != nullptr) {
    if (x == element->x && y == element->y) return true;
    element = element->next;
  }
  if (x == element->x && y == element->y) return true;
  return false;
}

bool Snake::intersects_with_self() {
  if (this->last == nullptr) return false; // ?
  auto x = this->last->x;
  auto y = this->last->y;
  auto element = this->first;
  while (element->next != nullptr) { // intentionally avoids last element
    if (x == element->x && y == element->y) return true;
    element = element->next;
  }
  return false;
}

Snake::~Snake() {
  auto element = this->first;
  while (element->next != nullptr) {
    auto current = element;
    element = element->next;
    delete current;
  }
  delete element;
}
