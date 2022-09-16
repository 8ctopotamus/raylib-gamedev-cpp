#include "raylib.h"

class Prop {
  public:
    Prop(Vector2 pos, Texture2D tex);
  private:
    float scale{4.f};
    Vector2 worldPos{};
    Texture2D texture{};
};