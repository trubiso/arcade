#pragma once
#include <functional>

struct SnakeNode {
  SnakeNode *next;
  unsigned x, y;
};

enum SnakeDirection {
  UP,
  LEFT,
  DOWN,
  RIGHT
};

class Snake {
private:
  SnakeNode *first;
  SnakeNode *last;
  unsigned length;

public:
  Snake() : first(nullptr), last(nullptr), length(0) {};
  ~Snake();

  void add_node(unsigned x, unsigned y);
  void remove_tail();
  void move_snake(SnakeDirection direction, unsigned max_x, unsigned max_y, std::function<bool(unsigned, unsigned)> check_food);
  void print(SnakeDirection last_direction) const;
  bool intersects_with_coords(unsigned x, unsigned y) const;
  bool intersects_with_self();
};
