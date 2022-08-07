#ifndef MY_RANDOM_H
#define MY_RANDOM_H

#include <iostream>

// return random number in [start, end)
int random(int start, int end) {
  static bool flag = false;
  if (!flag) {
    flag = true;
    srand(static_cast<unsigned int>(time(0)));
  }
  return rand() % (end - start) + start;
}

#endif