#include"IOSystem.hpp"

#include<iostream>
#include<string>
#include<sstream>
#include<thread>
#include<chrono>
#include<cctype>
#include<algorithm>

namespace dungeon {

IOSystem::IOSystem() {
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::ios::sync_with_stdio(false);
}

void IOSystem::clear() {
	std::cout.rdbuf()->sputn(ANSI_ESC_CLEAR, sizeof ANSI_ESC_CLEAR);
	std::cout.rdbuf()->sputn(ANSI_ESC_CURSOR_RESET, sizeof ANSI_ESC_CURSOR_RESET);
	std::cout.rdbuf()->sputn(HEADER_MESSAGE, sizeof HEADER_MESSAGE);
	std::cout.flush();
}

void IOSystem::pause() {
	std::string str;
	std::cout.rdbuf()->sputn(PAUSE_MESSAGE, sizeof PAUSE_MESSAGE);
	std::getline(std::cin, str);
}

void IOSystem::sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

}
