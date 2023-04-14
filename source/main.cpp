#include"Game.hpp"
#include"Error.hpp"

int main() {
	try {
		dungeon::Game game;
		game.run();
	} catch (dungeon::Error) {
		return -1;
	}
	return 0;
}