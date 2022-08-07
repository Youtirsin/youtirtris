#ifndef GAME_H
#define GAME_H

#include <Windows.h>

#include <iostream>
#include <vector>
#include <thread>
#include <functional>

#include "board.h"
#include "shape.h"

#include "screen.h"
#include "controll.h"

const int DROP_DELAY      = 600;
const int CONTROLL_DELAY  = 200;
const int FRAME_DELAY     = 10;

class Game {
 public:
  Game();

  void init();

  void run();

  ~Game();

 private:
  Screen *screen          = nullptr;
  UserControll *controll  = nullptr;

  Board *board            = nullptr;
  Shape *shape            = nullptr;
  Shape *nextShape        = nullptr;

  bool gameOver           = false;
  std::vector<std::vector<char>> screenData;

  void clear_screen();

  void user_controll();

  void board_logic();

  void game_render();

  void next_shape();

  void init_shape_pos(Shape *shape);

  void draw_board();
  
  void draw_shape();
};

#endif
