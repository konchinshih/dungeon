#include"Attribute.hpp"

#include"Ability.hpp"

#include<cmath>

namespace dungeon {

Attribute::Attribute(
  int baseHp,
  int baseAtk,
  int baseAtkSpeed,
  int baseExp,

  int hpPercent,
  int atkPercent,
  int atkSpeedPercent,
  int critRatePercent,
  int critDamagePercent,
  int expGainPercent,

  int flatHp,
  int flatAtk,
  int flatExp
):
  baseHp(baseHp),
  baseAtk(baseAtk),
  baseAtkSpeed(baseAtkSpeed),
  baseExp(baseExp),
  hpPercent(hpPercent),
  atkPercent(atkPercent),
  atkSpeedPercent(atkSpeedPercent),
  critRatePercent(critRatePercent),
  critDamagePercent(critDamagePercent),
  expGainPercent(expGainPercent),
  flatHp(flatHp),
  flatAtk(flatAtk),
  flatExp(flatExp) {}

int Attribute::hp()const {
  return baseHp * (100 + hpPercent) / 100.0 + flatHp;
}

int Attribute::atk()const {
  return baseAtk * (100 + atkPercent) / 100.0 + flatAtk;
}

int Attribute::critRate()const {
  return critRatePercent;
}

int Attribute::critDamage()const {
  return critDamagePercent;
};

int Attribute::atkInterval(const Ability& ability)const {
  int atkSpeed = baseAtkSpeed * (100 + atkSpeedPercent) / 100.0;
  return ability.baseInterval +
         (ability.baseInterval - MIN_ATTACK_INTERVAL) * std::tanh(atkSpeed / ATKSPEED_MAGIC_NUMBER);
}

Attribute& Attribute::operator+=(const Attribute& attr) {
  baseHp += attr.baseHp;
  baseAtk += attr.baseAtk;
  baseAtkSpeed += attr.baseAtkSpeed;
  baseExp += attr.baseExp;

  hpPercent += attr.hpPercent;
  atkPercent += attr.atkPercent;
  atkSpeedPercent += attr.atkSpeedPercent;
  critRatePercent += attr.critRatePercent;
  critDamagePercent += attr.critDamagePercent;
  expGainPercent += attr.expGainPercent;

  flatHp += attr.flatHp;
  flatAtk += attr.flatAtk;
  flatExp += attr.flatExp;
  return *this;
}

Attribute& Attribute::operator-=(const Attribute& attr) {
  baseHp -= attr.baseHp;
  baseAtk -= attr.baseAtk;
  baseAtkSpeed -= attr.baseAtkSpeed;
  baseExp -= attr.baseExp;

  hpPercent -= attr.hpPercent;
  atkPercent -= attr.atkPercent;
  atkSpeedPercent -= attr.atkSpeedPercent;
  critRatePercent -= attr.critRatePercent;
  critDamagePercent -= attr.critDamagePercent;
  expGainPercent -= attr.expGainPercent;

  flatHp -= attr.flatHp;
  flatAtk -= attr.flatAtk;
  flatExp -= attr.flatExp;
  return *this;
}

}
