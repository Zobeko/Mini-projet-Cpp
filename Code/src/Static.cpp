#include "Static.h"

Static::Static(int _x, int _y, int _h, int _l, std::string textureName, b2World& world) : UnitePhysic(_x, _y, _h, _l, textureName, b2_staticBody, world) {
}
