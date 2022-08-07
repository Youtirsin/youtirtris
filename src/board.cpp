#include "board.h"
#include <tuple>

Board::Board() {
  init();
}

void Board::init() {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      board[i][j] = POS_NOT_PUT;
    }
  }
}

void Board::store_shape(Shape *shape) {
  int x, y;
  std::tie(x, y) = shape->get_pos();
  for (int i = 0; i < SHAPE_TEMP_SIZE; ++i) {
    for (int j = 0; j < SHAPE_TEMP_SIZE; ++j) {
      if (x + i < 0 || y + j < 0) { continue; }
      if (shape->get_block_state(i, j) != POS_NOT_PUT) {
        board[x + i][y + j] = POS_PUT;
      }
    }
  }
}

bool Board::is_game_over() {
  for (int i = 0; i < BOARD_WIDTH; ++i) {
    if (board[0][i] == POS_PUT) { return true; }
  }
  return false;
}

void Board::delete_line(int y) {
  for (int i = y; i > 0; --i) {
    for (int j = 0; j < BOARD_WIDTH; ++j) {
      board[i][j] = board[i - 1][j];
    }
  }
  for (int i = 0; i < BOARD_WIDTH; ++i) {
    board[0][i] = POS_NOT_PUT;
  }
}

void Board::delete_all_lines() {
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
    int j = 0;
    for (; j < BOARD_WIDTH; ++j) {
      if (board[i][j] == POS_NOT_PUT) { break; }
    }
    if (j == BOARD_WIDTH) { delete_line(i); }
  }
}

bool Board::is_movable(Shape *shape, int mx, int my) {
  int x, y;
  std::tie(x, y) = shape->get_pos();
  x += mx;
  y += my;

  for (int i = 0; i < SHAPE_TEMP_SIZE; ++i) {
    for (int j = 0; j < SHAPE_TEMP_SIZE; ++j) {
      // out of borders
      if (x + i < 0 || x + i >= BOARD_HEIGHT || y + j < 0 || y + j >= BOARD_WIDTH) {
        if (shape->get_block_state(i, j) != 0) { return false; }
      } else {
      // check collision between the shape and the blocks on the board
        if (is_put(x + i, y + j) && shape->get_block_state(i, j) != 0) {
          return false;
        }
      }
    }
  }
  return true;
}
