#include "htable.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void init_curses(void);
void cleanup(void);
void print_menu_item(WINDOW *w, const char *name);
void print_app_title(const char *title);
void mainloop(void);
void sigwinch_handler(int);
WINDOW *main_w, *foot_w;
int main (int argc, char **argv)
{
  init_curses();
  table_t table = htable_create_table(20);
  mainloop();
  cleanup();
  return 0;
}
void init_curses(void)
{
  initscr();
  keypad(stdscr, 1);
  cbreak();
  noecho();
  start_color();
  signal(SIGWINCH, &sigwinch_handler);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);

  main_w = newwin(LINES-5, COLS-2, 1, 1);
  foot_w = newwin(2, COLS-2, LINES-3, 1);
  box(stdscr, 0, 0);
  print_app_title("HASH TABLE");
  mvwhline(foot_w, 0, 0, ACS_HLINE, COLS);
  waddstr(main_w, "Hello, Curses");
  wmove(foot_w, 1, 0);
  print_menu_item(foot_w, "Create list");
  print_menu_item(foot_w, "Quit");

  refresh();
  wrefresh(foot_w);
  wrefresh(main_w);
  atexit(&cleanup); // <- is the & necessary?
}
void cleanup(void)
{
  endwin();
}
void print_app_title(const char *title)
{
  move (0, COLS/2 - strlen(title)/2 - 4);
  addstr("| ");
  attron(COLOR_PAIR(2));
  printw("%s", title);
  attroff(COLOR_PAIR(2));
  addstr(" |");
}
void print_menu_item(WINDOW *w, const char *name)
{
  waddstr(w, " | ");
  wattron(w, COLOR_PAIR(1));
  waddch(w, name[0]);
  wattroff(w, COLOR_PAIR(1));
  wprintw(w, "%s |", name+1);
}
void mainloop(void)
{
  int c;

  while ((c = getch()) != 'q') {
    switch(c) {
      case 'j':
        mvwhline(main_w, 0, 0, ' ', COLS);
        waddstr(main_w, "pressed j");
        wrefresh(main_w);
        break;
      case 'k':
        mvwhline(main_w, 0, 0, ' ', COLS);
        waddstr(main_w, "pressed k");
        wrefresh(main_w);
        break;
      default:
        mvwhline(main_w, 0, 0, ' ', COLS);
        wprintw(main_w, "press: %d\n", c);
        wrefresh(main_w);
    }
  }
}
void sigwinch_handler(int i)
{
  clear();
  endwin();
  refresh();
  wresize(main_w, LINES-5, COLS-2);
  wresize(foot_w, 2, COLS-2);
  mvwin(foot_w, LINES-3, 1);
  box(stdscr, 0, 0);
  print_app_title("HASH TABLE");
  mvwhline(foot_w, 0, 0, ACS_HLINE, COLS);
  wmove(foot_w, 1, 0);
  print_menu_item(foot_w, "Create list");
  print_menu_item(foot_w, "Quit");

  refresh();
  wrefresh(foot_w);
  wrefresh(main_w);
  getch();
}
