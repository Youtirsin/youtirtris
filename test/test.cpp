#include "../src/Controll.h"

#include <iostream>
using namespace std;

int main() {
  UserControll *controll = new UserControll();
  while (true) {
    if (controll->move_right()) {
      cout << "down\r";
    } else {
      cout << "    \rup\r";
    }
  }
  return 0;
}
