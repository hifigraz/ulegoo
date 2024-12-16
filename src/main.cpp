#include "include/ulegoo.hpp"

// this is an example project

int main() {
  setup_ulegoo();
  enable();

  while (true) {
    move_forward();
    delay(500);
    rotate_left();
    delay(1000);
    move_backward();
    delay(500);
    break; // this is just to break the loop
  }

  stop();
  disable();
}
