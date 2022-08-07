#include "screen.h"

bool Screen::init(int width_, int height_) {
  if (inited) {
    std::cout << "already had inited\n";
    return false;
  }
  inited = true;
  width = width_;
  height = height_;
  consoleHandle = CreateConsoleScreenBuffer(
      GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
  if (consoleHandle == INVALID_HANDLE_VALUE) {
    std::cout << "error creating screen buffer handle\n";
    return false;
  }
  if (!SetConsoleActiveScreenBuffer(consoleHandle)) {
    std::cout << "error activing screen buffer handle\n";
    return false;
  }
  resize(width, height);
  return true;
}

void Screen::resize(int width_, int height_) {
  width = width_;
  height = height_;
  if (buffer != nullptr) { delete[] buffer; }
  buffer = new char[height * (width + 2)];
  memset(buffer, 0, sizeof(buffer));
}

void Screen::render(std::vector<std::vector<char>> &screenData) {
  if (screenData.size() * (screenData[0].size() + 2) != height * (width + 2)) {
    std::cout << "size of screen data does not match the buffer\n";
    return;
  }
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      buffer[i * (width + 2) + j] = screenData[i][j];
    }
    buffer[i * (width + 2) + width] = '\n';
    buffer[i * (width + 2) + width + 1] = '\r';
  }
  DWORD byteWritten;
  WriteConsoleOutputCharacter(consoleHandle, buffer, height * (width + 2), {0, 0}, &byteWritten);
}

Screen::~Screen() {
  CloseHandle(consoleHandle);
  delete[] buffer;
}
