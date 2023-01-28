#pragma once
#include <ncurses.h>
#include <utility>
#include <vector>
#include <string>
#include <functional>

typedef std::function<bool(void)> ChooserCallback;

class Chooser {
  private:
    std::vector<std::pair<std::string, ChooserCallback>> items;
    unsigned selected_index = 0;

  public:
    Chooser();

    void add_item(std::string name, ChooserCallback callback);

    void print_items(WINDOW *win) const;
    void prompt_user(WINDOW *win, std::string prompt);

    inline void print_items() const { this->print_items(stdscr); }
    inline void prompt_user(std::string prompt) { this->prompt_user(stdscr, prompt); }

    inline unsigned get_item_count() const { return this->items.size(); }
    inline unsigned max_index() const { return this->get_item_count() - 1; }
};
