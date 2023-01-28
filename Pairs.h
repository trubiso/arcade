#pragma once
#include <ncurses.h>

enum Pairs {
  Regular = 1,
  Inverse = 2
};

void init_custom_pairs();

inline void pair_turn_on(Pairs pair) { attron(COLOR_PAIR(pair)); }
inline void pair_turn_off(Pairs pair) { attroff(COLOR_PAIR(pair)); }

