#include"Map.hpp"
#include"Item.hpp"
#include"Monster.hpp"
#include"Error.hpp"
#include"NPC.hpp"

#include<algorithm>
#include<chrono>

namespace dungeon {

Map::Map(): rndGen(std::chrono::steady_clock::now().time_since_epoch().count()) {
  for (int i = 0; i < 25; i++)
    roomQue.push_back(std::make_shared<Room>());
  roomQue.push_back(std::make_shared<TreasureRoom>(std::make_unique<Excalibur>()));
  roomQue.push_back(std::make_shared<TreasureRoom>(std::make_unique<WaterPistol>()));
  roomQue.push_back(std::make_shared<TreasureRoom>(std::make_unique<Rhongomyniad>()));
  roomQue.push_back(std::make_shared<TreasureRoom>(std::make_unique<AltereactorEngine>()));
  for (int i = 0; i < 6; i++)
    roomQue.push_back(std::make_shared<TreasureRoom>(std::make_unique<PhilosophersStone>()));
  for (int i = 0; i < 5; i++)
    roomQue.push_back(std::make_shared<MonsterRoom>(std::make_unique<Slime>()));
  for (int i = 0; i < 2; i++) {
    roomQue.push_back(std::make_shared<MonsterRoom>(std::make_unique<Goblin<Class::saber>>()));
    roomQue.push_back(std::make_shared<MonsterRoom>(std::make_unique<Goblin<Class::archer>>()));
    roomQue.push_back(std::make_shared<MonsterRoom>(std::make_unique<Goblin<Class::lancer>>()));
    roomQue.push_back(std::make_shared<MonsterRoom>(std::make_unique<Goblin<Class::berserker>>()));
  }
  roomQue.push_back(std::make_shared<BossRoom>(std::make_unique<Rimuru>()));
  std::shuffle(roomQue.begin(), roomQue.end(), rndGen);
}

void Map::regenerate() {
  for (int i = 0; i < 25; i++)
    roomQue.push_back(std::make_shared<Room>());
  roomQue.push_back(std::make_shared<TreasureRoom>(std::make_unique<PhilosophersStone>()));
  for (int i = 0; i < 4; i++)
    roomQue.push_back(std::make_shared<MonsterRoom>(std::make_unique<Slime>()));
  for (int i = 0; i < 5; i++) {
    roomQue.push_back(std::make_shared<MonsterRoom>(std::make_unique<Goblin<Class::saber>>()));
    roomQue.push_back(std::make_shared<MonsterRoom>(std::make_unique<Goblin<Class::archer>>()));
    roomQue.push_back(std::make_shared<MonsterRoom>(std::make_unique<Goblin<Class::lancer>>()));
    roomQue.push_back(std::make_shared<MonsterRoom>(std::make_unique<Goblin<Class::berserker>>()));
  }
  std::shuffle(roomQue.begin(), roomQue.end(), rndGen);
}

std::shared_ptr<Room>& Map::at(int x, int y) {
  if (roomMap.count(std::make_pair(x, y)))
    return roomMap[std::make_pair(x, y)];
  if (roomQue.empty()) regenerate();
  roomMap[std::make_pair(x, y)] = roomQue.front();
  roomQue.pop_front();
  return roomMap[std::make_pair(x, y)];
}

}
