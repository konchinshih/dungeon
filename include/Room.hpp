#pragma once

#include"Item.hpp"
#include"Monster.hpp"
#include"NPC.hpp"

#include<memory>

namespace dungeon {

enum class RoomType {
  NOTHING, TREASURE, NPC, MONSTER, BOSS
};

struct Game;

struct Room {
  RoomType type;

  Room(RoomType = RoomType::NOTHING);
  virtual void doAction(Game&);
};

struct TreasureRoom: Room {
  bool isActionDone;
  std::unique_ptr<Item> item;

  TreasureRoom(std::unique_ptr<Item>&&);
  void doAction(Game&);
};

struct NPCRoom: Room {
  std::unique_ptr<NPC> npc;

  NPCRoom(std::unique_ptr<NPC>&&);
  void doAction(Game&);
};

struct MonsterRoom: Room {
  bool isActionDone;
  std::unique_ptr<Monster> monster;

  MonsterRoom(std::unique_ptr<Monster>&&);
  void doAction(Game&);
};

struct BossRoom: Room {
  std::unique_ptr<Boss> boss;

  BossRoom(std::unique_ptr<Boss>&&);
  void doAction(Game&);
};

}
