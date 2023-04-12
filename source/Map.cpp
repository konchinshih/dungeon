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
    roomQue.push_back(std::make_unique<Room>());
  roomQue.push_back(std::make_unique<TreasureRoom>(std::make_unique<Excalibur>()));
  roomQue.push_back(std::make_unique<TreasureRoom>(std::make_unique<WaterPistol>()));
  roomQue.push_back(std::make_unique<TreasureRoom>(std::make_unique<Rhongomyniad>()));
  roomQue.push_back(std::make_unique<TreasureRoom>(std::make_unique<AltereactorEngine>()));
  for (int i = 0; i < 6; i++)
    roomQue.push_back(std::make_unique<TreasureRoom>(std::make_unique<PhilosophersStone>()));
  for (int i = 0; i < 5; i++)
    roomQue.push_back(std::make_unique<MonsterRoom>(std::make_unique<Slime>()));
  for (int i = 0; i < 2; i++) {
    roomQue.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::SABER>>()));
    roomQue.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::ARCHER>>()));
    roomQue.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::LANCER>>()));
    roomQue.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::BERSERKER>>()));
  }
  roomQue.push_back(std::make_unique<BossRoom>(std::make_unique<Rimuru>()));
  std::shuffle(roomQue.begin(), roomQue.end(), rndGen);
}

void Map::reGenQue() {
  for (int i = 0; i < 25; i++)
    roomQue.push_back(std::make_unique<Room>());
  roomQue.push_back(std::make_unique<TreasureRoom>(std::make_unique<PhilosophersStone>()));
  for (int i = 0; i < 4; i++)
    roomQue.push_back(std::make_unique<MonsterRoom>(std::make_unique<Slime>()));
  for (int i = 0; i < 5; i++) {
    roomQue.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::SABER>>()));
    roomQue.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::ARCHER>>()));
    roomQue.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::LANCER>>()));
    roomQue.push_back(std::make_unique<MonsterRoom>(std::make_unique<Goblin<ClassType::BERSERKER>>()));
  }
  std::shuffle(roomQue.begin(), roomQue.end(), rndGen);
}

std::unique_ptr<Room>& Map::at(const std::unique_ptr<Character>& character) {
  int x = character->curX, y = character->curY;
  if (roomMap.count(std::make_pair(x, y)))
    return roomMap[std::make_pair(x, y)];
  if (roomQue.empty()) reGenQue();
  roomMap[std::make_pair(x, y)] = std::move(roomQue.back());
  roomQue.pop_back();
  return roomMap[std::make_pair(x, y)];
}

}
