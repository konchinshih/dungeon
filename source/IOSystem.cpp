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
	std::cout.flush();
}

void IOSystem::print(const std::string& str, bool isEoln) {
	std::cout.rdbuf()->sputn(str.data(), str.size());
	if (isEoln) std::cout.rdbuf()->sputc('\n');
	std::cout.flush();
}

char IOSystem::inputChar(const std::string& question) {
	print(question, false);
	std::string str;
	while (str.empty()) {
		std::remove_if(str.begin(), str.end(), [](char c) {
			return isspace(c);
		});
	}
	return str.front();
}

std::vector<std::string> IOSystem::inputTokens(const std::string& question) {
	print(question, false);
	std::string str, tmp;
	std::vector<std::string> ret;
	while (ret.empty()) {
		std::getline(std::cin, str);
		std::stringstream ss(str);
		while (ss >> tmp)
			ret.emplace_back(tmp);
	}
	return ret;
}

void IOSystem::pause() {
	std::string str;
	print("[Press enter to continue]");
	std::getline(std::cin, str);
}

void IOSystem::sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

template<typename T>
IOSystem& operator<<(IOSystem& ios, const T& obj) {
	std::cout << obj;
	return ios;
}

}
