#ifndef SCREEN_H
#define SCREEN_H

#include <Windows.h>

#include <iostream>
#include <vector>

class Screen {
 public:
  bool init(int width, int height);

  void resize(int width, int height);

  void render(std::vector<std::vector<char>> &screenData);

  ~Screen();
  
 private:
  HANDLE consoleHandle;
  char *buffer  = nullptr;
  bool inited   = false;
  size_t width  = 0;
  size_t height = 0;
};

#endif