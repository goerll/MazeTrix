#include "../include/structs.h"

bool Vector2i::operator==(const Vector2i &other) const {
  return (x == other.x && y == other.y);
}

bool Vector2i::operator!=(const Vector2i &other) const {
  return (x != other.x || y != other.y);
}
