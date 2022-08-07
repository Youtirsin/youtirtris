#ifndef BOARD_H
#define BOARD_H

#include "shape.h"

const int BOARD_WIDTH    = 10;
const int BOARD_HEIGHT   = 20;

// game board
class Board {
 public:
  Board();

  // store the shape where it is
  void store_shape(Shape *shape);

  // check whether game is over
  bool is_game_over();

  // find deletable lines and delete them
  void delete_all_lines();

  // check the shape is movable with the relative movement
  bool is_movable(Shape *shape, int mx, int my);

  // get the block state
  bool is_put(int x, int y) { return board[x][y] == POS_PUT; }

  int get_block(int x, int y) const { return board[x][y]; }

 private:
  // enum states for the board blocks
  enum { POS_NOT_PUT, POS_PUT };

  // the board data
  char board[BOARD_HEIGHT][BOARD_WIDTH];

  // initialization
  void init();

  // delete the yth line
  void delete_line(int y);
};

#endif