#include"Ability.hpp"

namespace dungeon {

Ability::Ability(
  std::string name,
  int baseInterval,
  int baseMotionValuePercent,
  int motionValuePercentGrow,
  int maxLevel
):
  name(name),
  baseInterval(baseInterval),
  baseMotionValuePercent(baseMotionValuePercent),
  motionValuePercentGrow(motionValuePercentGrow),
  curLevel(1), maxLevel(maxLevel) {}

int Ability::motionValue()const {
  return baseMotionValuePercent + motionValuePercentGrow * curLevel;
}

}
