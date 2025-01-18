#include "halvoeUtility.hpp"

namespace halvoe
{
  double distanceVec(const tgx::iVec2& in_a, const tgx::iVec2& in_b)
  {
    return sqrt(sq(in_a.x - in_b.x) + sq(in_a.y - in_b.y));
  }
}
