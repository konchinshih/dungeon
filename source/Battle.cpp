#include"Battle.hpp"

namespace dungeon {

Battle::Battle(IOSystem& ios, Character& mainChar, Monster& enemy):
  ios(ios), mainChar(mainChar), enemy(enemy) {}

void Battle::action() {
  ios << "";
}

void Battle::run() {
  ios << "Encounter \"" << enemy.name << "\"" << endl;
  int curTick = 0;
  while (true) {
    showEnemyStatus();
    showCharStatus();
    if (actionAvailable())
      action();
    curTick++;
  }
}

}
