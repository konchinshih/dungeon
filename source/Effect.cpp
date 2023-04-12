#include"Effect.hpp"
#include"Entity.hpp"

namespace dungeon {

void Poison::begin(Entity& entity) {
  duration = DURATION;
}
void Poison::affect(Entity& entity) {
  entity.curHp -= DAMAGE_OVER_TIME;
}
void Poison::end(Entity& entity) {}

void Burning::begin(Entity& entity) {
  duration = DURATION;
}
void Burning::affect(Entity& entity) {
  entity.curHp -= DAMAGE_OVER_TIME;
}
void Burning::end(Entity& entity) {}

void AtkPercentDown::begin(Entity& entity) {
  duration = DURATION;
  entity.attr.atkPercent -= AMOUNT;
}
void AtkPercentDown::affect(Entity& entity) {}
void AtkPercentDown::end(Entity& entity) {
  entity.attr.atkPercent += AMOUNT;
}

void AtkSpeedDown::begin(Entity& entity) {
  duration = DURATION;
  entity.attr.atkSpeedPercent -= AMOUNT;
}
void AtkSpeedDown::affect(Entity& entity) {}
void AtkSpeedDown::end(Entity& entity) {
  entity.attr.atkSpeedPercent += AMOUNT;
}

void AtkPercentUp::begin(Entity& entity) {
  duration = DURATION;
  entity.attr.atkPercent += AMOUNT;
}
void AtkPercentUp::affect(Entity& entity) {}
void AtkPercentUp::end(Entity& entity) {
  entity.attr.atkPercent -= AMOUNT;
}

void CritRateUp::begin(Entity& entity) {
  duration = DURATION;
  entity.attr.critRatePercent += AMOUNT;
}
void CritRateUp::affect(Entity& entity) {}
void CritRateUp::end(Entity& entity) {
  entity.attr.critRatePercent -= AMOUNT;
}

void CritDamageUp::begin(Entity& entity) {
  duration = DURATION;
  entity.attr.critDamagePercent += AMOUNT;
}
void CritDamageUp::affect(Entity& entity) {}
void CritDamageUp::end(Entity& entity) {
  entity.attr.critDamagePercent -= AMOUNT;
}

void AtkSpeedUp::begin(Entity& entity) {
  duration = DURATION;
  entity.attr.atkSpeedPercent += AMOUNT;
}
void AtkSpeedUp::affect(Entity& entity) {}
void AtkSpeedUp::end(Entity& entity) {
  entity.attr.atkSpeedPercent -= AMOUNT;
}

}