#pragma once

#include "math/ofMath.h"

float step4d(float x, float y, float z, float w){
  return ofSignedNoise(x, y, z, w) > 0 ? 1 : -1;
}
