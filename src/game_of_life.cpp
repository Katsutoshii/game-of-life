/*
 * File: game_of_life.cpp
 * Project: src
 * File Created: Wednesday, 27th March 2019 11:11:13 am
 * Author: Josiah Putman (joshikatsu@gmail.com)
 * -----
 * Last Modified: Friday, 29th March 2019 6:24:49 pm
 * Modified By: Josiah Putman (joshikatsu@gmail.com)
 */
#include "game_of_life.hpp"

template <uint W, uint H>
GameOfLife<W, H>::GameOfLife(std::ostream& out, bool seed[W * H]) : out(out)
{
	out << "Game of Life (" << W << " x " << H << ")" << std::endl;
	if (seed != nullptr) {
		for (uint n = 0; n < W * H; n++) {
			matrix[n] = seed[n];
		}
		out << "Seed copied." << std::endl;
	}
	else {
		out << "Using empty board." << std::endl;
	}
}

template <uint W, uint H>
uint GameOfLife<W, H>::get_n(uint x, uint y)
{
	return (y * W) + x;
}

template <uint W, uint H>
uint GameOfLife<W, H>::get_x(uint n)
{
	return n % W;
}

template <uint W, uint H>
uint GameOfLife<W, H>::get_y(uint n)
{
	return n / W;
}

template <uint W, uint H>
bool GameOfLife<W, H>::in_bounds(uint n)
{
	if (n >= 0 && n < W * H) {
		return true;
	}
	else {
		out << "Bounds error: x = " << get_x(n) << ", y = " << get_y(n) << "." << std::endl;
		return false;
	}
}

template <uint W, uint H>
bool GameOfLife<W, H>::get(uint n)
{
	if (in_bounds(n)) {
		return matrix[n];
	}
	else {
		return false;
	}
}

template <uint W, uint H>
bool GameOfLife<W, H>::get(uint x, uint y)
{
	return get(get_n(x, y));
}

template <uint W, uint H>
uint GameOfLife<W, H>::get_num_alive() {
	return num_alive;
}

template <uint W, uint H>
void GameOfLife<W, H>::set(uint x, uint y, bool alive)
{
	set(get_n(x, y), alive);
}

template <uint W, uint H>
void GameOfLife<W, H>::set(uint n, bool alive)
{
	if (in_bounds(n)) {
		matrix[n] = alive;
	}
}

template <uint W, uint H>
void GameOfLife<W, H>::run(uint num_rounds)
{
	for (uint i = 0; i < num_rounds; i++) {
		update();
		out << "Round " << round_num << std::endl;
		print();
		out << std::endl;
	}
}

template <uint W, uint H>
void GameOfLife<W, H>::update()
{
	for (uint n = 0; n < W * H; n++) {
		update_cell(n);
	}
	for (auto update : updates) {
		out << "    Applying update " << update.second << " to cell " << update.first << std::endl;
		set(update.first, update.second);
	}
	updates.clear();
	
	round_num++;
}

template <uint W, uint H>
void GameOfLife<W, H>::update_cell(uint n)
{
	uint alive_count = 0;
	for (int j = -1; j <= 1; j += 1) {
		for (int i = -1; i <= 1; i++) {
			uint m = n + i + (j * W);
			out << "    m = " << m << std::endl;
			if (in_bounds(m) && (m != n) && (get(m))) {
				alive_count++;
			}
		}
	}
	out << "    Cell " << n << " had " << alive_count << " live neighbors." << std::endl;
	switch (alive_count) {
		case 2:
			break;
		case 3:
			if (!matrix[n]) {
				updates[n] = true;
			}
			break;
		default:
			if (matrix[n]) {
				updates[n] = false;
			}
			break;
	}
}

template <uint W, uint H>
void GameOfLife<W, H>::print()
{
	for (uint y = 0; y < H; y++) {
		for (uint x = 0; x < W; x++) {
			out << (get(x, y) ? "0" : ".") << " ";
		}
		out << std::endl;
	}
}

// ======================================================
int main()
{
	const uint W = 17;
	const int H = 17;
	bool seed[W * H] = {
		// 2     4     6     8     10    12    14    16
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//2
		0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //4
		0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0,	//6
		0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,	//8
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,	//10
		0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0,  //12
		0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //14
		0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //16
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
	
	GameOfLife<W, H> game(std::cout, seed);
	game.print();
	while (1) {
		std::cout << "Type 'c' to continue and 'q' to quit." << std::endl;
		std::string cmd;
		std::cin >> cmd;
		if (cmd == "c") {
			game.run(1);
		}
		else if (cmd == "q") {
			std::cout << "Exiting..." << std::endl;
			break;
		}
		else {
			std:: cout << "Unknown command." << std::endl;
		}
	}
	return 0;
}
