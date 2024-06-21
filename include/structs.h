#pragma once

// Vector2i structure for 2D coordinates
struct Vector2i {
  int x, y;

  bool operator==(const Vector2i &) const;
  bool operator!=(const Vector2i &) const;
};
