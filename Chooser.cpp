#include "Chooser.h"
#include "Pairs.h"
#include <ncurses.h>

Chooser::Chooser() : items() {
  this->selected_index = 0u;
}

void Chooser::add_item(std::string name, ChooserCallback callback) {
  this->items.push_back({name, callback});
}

void Chooser::print_items(WINDOW *win) const {
  for (unsigned i = 0u; i < this->get_item_count(); i++) {
    bool is_selected = i == this->selected_index;
    auto item_name = this->items[i].first;
    auto attribute = is_selected ? Pairs::Inverse : Pairs::Regular;
    pair_turn_on(attribute);
    wprintw(win, "%s %s\n", is_selected ? "*" : " ", item_name.c_str());
    pair_turn_off(attribute);
  }

}

void Chooser::prompt_user(WINDOW *win, std::string prompt) {
  bool should_close = false;
  while (!should_close) {
    clear();
    wprintw(win, "%s\n", prompt.c_str());
    this->print_items(win);
    auto ch = wgetch(win);
    switch (ch) {
      case KEY_UP:
        if (this->selected_index != 0) this->selected_index--;
        else this->selected_index = this->max_index();
        break;
      case KEY_DOWN:
        if (this->selected_index < this->max_index()) this->selected_index++;
        else this->selected_index = 0;
        break;
      case '\n': // TODO: be elegant
        should_close = this->items[this->selected_index].second();
        break;
      default:
        break;
    }
  }
}
