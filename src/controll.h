#ifndef CONTROLL_H
#define CONTROLL_H

#include <Windows.h>

class UserControll {
 public:
  bool move_left() { return GetAsyncKeyState(moveLeftKey) & 0x8000; }
  bool move_right() { return GetAsyncKeyState(moveRightKey) & 0x8000; }
  bool drop() { return GetAsyncKeyState(dropKey) & 0x8000; }
  bool rotate() { return GetAsyncKeyState(rotateKey) & 0x8000; }
 private:
  int moveLeftKey   = 'A';
  int moveRightKey  = 'D';
  int dropKey       = 'S';
  int rotateKey     = 'W';
};

#endif