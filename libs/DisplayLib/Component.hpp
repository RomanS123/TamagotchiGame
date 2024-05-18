#include <cstdint>
#include <iostream>
#pragma once

/*ll the UI components derive from this class to
 provide unified interface to work with
*/
template <typename Renderer>
class Component {
  uint32_t relative_x = 0;
  uint32_t relative_y = 0;
  uint32_t width = 0;
  uint32_t height = 0;

 public:
  Component() {}
  void SetSize(uint32_t w, uint32_t h) {
    width = w;
    height = h;
  }

  void SetPosition(uint32_t x, uint32_t y) {
    relative_x = x;
    relative_y = y;
  }

  uint32_t GetX() const { return relative_x; }

  uint32_t GetY() const { return relative_y; }

  uint32_t GetWidth() const { return width; }

  uint32_t GetHeight() const { return height; }

  virtual void render(void* callee, Renderer& renderer) = 0;
};
