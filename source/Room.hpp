#pragma once

#include"Item.hpp"
#include"Monster.hpp"
#include"NPC.hpp"

#include<memory>

namespace dungeon {

struct Map;

enum RoomType {
  nothing, treasure, npc, monster, boss
};

struct Room {
  RoomType type;

  Room();
};

struct TreasureRoom: Room {
  std::unique_ptr<Item> item;

  TreasureRoom(std::unique_ptr<Item>&&);
};

struct NPCRoom: Room {
  std::unique_ptr<NPC> npc;

  NPCRoom(std::unique_ptr<NPC>&&);
};

struct MonsterRoom: Room {
  std::unique_ptr<Monster> monster;

  MonsterRoom(std::unique_ptr<Monster>&&);
};

struct BossRoom: Room {
  std::unique_ptr<Boss> boss;

  BossRoom(std::unique_ptr<Boss>&&);
};

}
