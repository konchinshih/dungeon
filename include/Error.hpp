#pragma once

namespace dungeon {

struct Error {};

struct TypeError: Error {
	TypeError();
};

}
