#include"Room.hpp"

#include<utility>

namespace dungeon {

Room::Room() {
  type = RoomType::nothing;
}

TreasureRoom::TreasureRoom(std::unique_ptr<Item>&& item) {
  type = RoomType::treasure;
  this->item = std::move(item);
}

NPCRoom::NPCRoom(std::unique_ptr<NPC>&& npc) {
  type = RoomType::npc;
  this->npc = std::move(npc);
}

MonsterRoom::MonsterRoom(std::unique_ptr<Monster>&& monster) {
  type = RoomType::monster;
  this->monster = std::move(monster);
}

BossRoom::BossRoom(std::unique_ptr<Boss>&& boss) {
  type = RoomType::boss;
  this->boss = std::move(boss);
}


}
