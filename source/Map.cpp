#include"Map.hpp"

#include"Item.hpp"
#include"Monster.hpp"
#include"NPC.hpp"
#include"Character.hpp"
#include"ClassType.hpp"

#include<algorithm>
#include<chrono>
#include<utility>

namespace dungeon {

Map::Map(std::mt19937& rndGen): rndGen(rndGen) {
  for (int i = 0; i < 25; i++)
    roomPool.push_back(std::make_unique<Room>());
  roomPool.push_back(std::make_unique<TreasureRoom>(std::make_unique<Excalibur>()));
  roomPool.push_back(std::make_unique<TreasureRoom>(std::make_unique<WaterPistol>()));
  roomPool.push_back(std::make_unique<TreasureRoom>(std::make_unique<Rhongomyniad>()));
  roomPool.push_back(std::make_unique<TreasureRoom>(std::make_unique<AltereactorEngine>()));
  for (int i = 0; i < 6; i++)
    roomPool.push_back(std::make_unique<TreasureRoom>(std::make_unique<PhilosophersStone>()));
  for (int i = 0; i < 5; i++)
    roomPool.push_back(std::make_unique<MonsterRoom>(std::make_unique<Slime>()));
  for (int i = 0; i < 2; i++) {
    roomPool.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::SABER>>()));
    roomPool.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::ARCHER>>()));
    roomPool.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::LANCER>>()));
    roomPool.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::BERSERKER>>()));
  }
  roomPool.push_back(std::make_unique<BossRoom>(std::make_unique<Rimuru>()));
  std::shuffle(roomPool.begin(), roomPool.end(), rndGen);
}

void Map::reGenPool() {
  for (int i = 0; i < 25; i++)
    roomPool.push_back(std::make_unique<Room>());
  roomPool.push_back(std::make_unique<TreasureRoom>(std::make_unique<PhilosophersStone>()));
  for (int i = 0; i < 4; i++)
    roomPool.push_back(std::make_unique<MonsterRoom>(std::make_unique<Slime>()));
  for (int i = 0; i < 5; i++) {
    roomPool.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::SABER>>()));
    roomPool.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::ARCHER>>()));
    roomPool.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::LANCER>>()));
    roomPool.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::BERSERKER>>()));
  }
  std::shuffle(roomPool.begin(), roomPool.end(), rndGen);
}

std::unique_ptr<Room>& Map::at(const Character& character) {
  int x = character.curX, y = character.curY;
  if (roomMap.count(std::make_pair(x, y)))
    return roomMap[std::make_pair(x, y)];
  if (roomPool.empty()) reGenPool();
  roomMap[std::make_pair(x, y)] = std::move(roomPool.back());
  roomPool.pop_back();
  return roomMap[std::make_pair(x, y)];
}

}
