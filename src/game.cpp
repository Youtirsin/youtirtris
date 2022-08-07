#include "game.h"

Game::Game(): 
  screenData(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH))
  {}

void Game::init() {
  screen    = new Screen();
  controll  = new UserControll();

  board     = new Board();
  shape     = new Shape();
  nextShape = new Shape();

  screen->init(BOARD_WIDTH, BOARD_HEIGHT);
  init_shape_pos(shape);
}

void Game::clear_screen() {
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
    for (int j = 0; j < BOARD_WIDTH; ++j) {
      screenData[i][j] = '0';
    }
  }
}

void Game::user_controll() {
  // TODO: user controller
  bool active = false;
  while (!gameOver) {
    active = false;
    if (controll->move_left()) {
      active = true;
      if (board->is_movable(shape, 0, -1)) {
        shape->move(0, -1);
      }
    } else if (controll->move_right()) {
      active = true;
      if (board->is_movable(shape, 0, 1)) {
        shape->move(0, 1);
      }
    } else if (controll->rotate()) {
      active = true;
      shape->rotate();
    } else if (controll->drop()) {
      active = true;
      if (board->is_movable(shape, 1, 0)) {
        shape->move(1, 0);
      }
    }
    if (active) {
      std::this_thread::sleep_for(std::chrono::milliseconds(CONTROLL_DELAY));
    }
  }
}

void Game::board_logic() {
  while (!gameOver) {
    std::this_thread::sleep_for(std::chrono::milliseconds(DROP_DELAY));
    if (board->is_movable(shape, 1, 0)) {
      shape->move(1, 0);
    } else {
      board->store_shape(shape);
      board->delete_all_lines();
      if (board->is_game_over()) { gameOver = true; }
      next_shape();
    }
  }
}

void Game::game_render() {
  while (!gameOver) {
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY));
    clear_screen();
    draw_board();
    draw_shape();
    screen->render(screenData);
  }
}

void Game::run() {
  std::thread(std::bind(&Game::user_controll, this)).detach();
  std::thread(std::bind(&Game::game_render, this)).detach();
  board_logic();
}

void Game::next_shape() {
  delete shape;
  shape = nextShape;
  init_shape_pos(shape);
  nextShape = new Shape();
}

void Game::init_shape_pos(Shape *shape) {
  int x, y;
  std::tie(x, y) = shape->get_init_pos();
  shape->set_pos(x, BOARD_WIDTH / 2 + y);
}

void Game::draw_board() {
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
    for (int j = 0; j < BOARD_WIDTH; ++j) {
      screenData[i][j] = board->get_block(i, j) + '0';
    }
  }
}

void Game::draw_shape() {
  int x, y;
  std::tie(x, y) = shape->get_pos();
  for (int i = 0; i < SHAPE_TEMP_SIZE; ++i) {
    for (int j = 0; j < SHAPE_TEMP_SIZE; ++j) {
      if (x + i < 0 || y + j < 0) { continue; }
      if (shape->get_block_state(i, j) != 0) {
        screenData[x + i][y + j] = '1';
      }
    }
  }
}

Game::~Game() {
  delete screen;
  delete controll;
  delete board;
  delete shape;
  delete nextShape;
  screen    = nullptr;
  controll  = nullptr;
  board     = nullptr;
  shape     = nullptr;
  nextShape = nullptr;
}