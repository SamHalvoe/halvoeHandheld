#include "halvoeUtility.hpp"

namespace halvoe
{
  double distanceVec(const tgx::iVec2& in_a, const tgx::iVec2& in_b)
  {
    int x = in_a.x - in_b.x;
    x = x * x;
    int y = in_a.y - in_b.y;
    y = y * y;
    return sqrt(x + y);
  }
}
