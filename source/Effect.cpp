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
  entity.atkPercent -= AMOUNT;
}
void AtkPercentDown::affect(Entity& entity) {}
void AtkPercentDown::end(Entity& entity) {
  entity.atkPercent += AMOUNT;
}

void AtkSpeedDown::begin(Entity& entity) {
  duration = DURATION;
  entity.atkSpeed -= AMOUNT;
}
void AtkSpeedDown::affect(Entity& entity) {}
void AtkSpeedDown::end(Entity& entity) {
  entity.atkSpeed += AMOUNT;
}

}