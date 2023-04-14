#include"Effect.hpp"
#include"Entity.hpp"

namespace dungeon {

Effect::Effect(std::string name): name(name) {}

Poison::Poison(): Effect("Poison") {}

void Poison::begin(Entity & entity) {
  timeLeft = DURATION;
}
void Poison::affect(Entity& entity) {
  entity.curHp -= DAMAGE_OVER_TIME;
}
void Poison::end(Entity& entity) {}

Burning::Burning(): Effect("Burning") {}

void Burning::begin(Entity& entity) {
  timeLeft = DURATION;
}
void Burning::affect(Entity& entity) {
  entity.curHp -= DAMAGE_OVER_TIME;
}
void Burning::end(Entity& entity) {}

AtkPercentDown::AtkPercentDown(): Effect("AtkPercentDown") {}

void AtkPercentDown::begin(Entity& entity) {
  timeLeft = DURATION;
  entity.attr.atkPercent -= AMOUNT;
}
void AtkPercentDown::affect(Entity& entity) {}
void AtkPercentDown::end(Entity& entity) {
  entity.attr.atkPercent += AMOUNT;
}

AtkSpeedDown::AtkSpeedDown(): Effect("AtkSpeedDown") {}

void AtkSpeedDown::begin(Entity& entity) {
  timeLeft = DURATION;
  entity.attr.atkSpeedPercent -= AMOUNT;
}
void AtkSpeedDown::affect(Entity& entity) {}
void AtkSpeedDown::end(Entity& entity) {
  entity.attr.atkSpeedPercent += AMOUNT;
}

AtkPercentUp::AtkPercentUp(): Effect("AtkPercentUp") {}

void AtkPercentUp::begin(Entity& entity) {
  timeLeft = DURATION;
  entity.attr.atkPercent += AMOUNT;
}
void AtkPercentUp::affect(Entity& entity) {}
void AtkPercentUp::end(Entity& entity) {
  entity.attr.atkPercent -= AMOUNT;
}

CritRateUp::CritRateUp(): Effect("CritRateUp") {}

void CritRateUp::begin(Entity& entity) {
  timeLeft = DURATION;
  entity.attr.critRatePercent += AMOUNT;
}
void CritRateUp::affect(Entity& entity) {}
void CritRateUp::end(Entity& entity) {
  entity.attr.critRatePercent -= AMOUNT;
}

CritDamageUp::CritDamageUp(): Effect("CritDamageUp") {}

void CritDamageUp::begin(Entity& entity) {
  timeLeft = DURATION;
  entity.attr.critDamagePercent += AMOUNT;
}
void CritDamageUp::affect(Entity& entity) {}
void CritDamageUp::end(Entity& entity) {
  entity.attr.critDamagePercent -= AMOUNT;
}

AtkSpeedUp::AtkSpeedUp(): Effect("AtkSpeedUp") {}

void AtkSpeedUp::begin(Entity& entity) {
  timeLeft = DURATION;
  entity.attr.atkSpeedPercent += AMOUNT;
}
void AtkSpeedUp::affect(Entity& entity) {}
void AtkSpeedUp::end(Entity& entity) {
  entity.attr.atkSpeedPercent -= AMOUNT;
}

}