#include "shape.h"
#include "my_random.h"

Shape::Shape() {
  type      = random(0, SHAPE_CNT);
  rotation  = random(0, SHAPE_ROTATE_CNT);
  x         = 0;
  y         = 0;
}