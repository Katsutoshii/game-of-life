/*
 * File: game_of_life.hpp
 * Project: src
 * File Created: Wednesday, 27th March 2019 11:11:39 am
 * Author: Josiah Putman (joshikatsu@gmail.com)
 * -----
 * Last Modified: Friday, 29th March 2019 5:36:56 pm
 * Modified By: Josiah Putman (joshikatsu@gmail.com)
 */

#include <iostream>
#include <map>
#include <functional>
#include <string>

typedef unsigned int uint;

template <uint W, uint H>
class GameOfLife
{
    public:
        GameOfLife(std::ostream& out, bool seed[W * H] = nullptr);
        void print();
        void run(uint num_rounds);
        uint get_num_alive();

    private:
        std::ostream& out;
        bool matrix[W * H] = {false};
        std::map<uint, bool> updates;
        void update();
        void update_cell(uint n);
        uint get_n(uint x, uint y);
        uint get_x(uint n);
        uint get_y(uint n);
        bool get(uint n);
        bool get(uint x, uint y);
        void set(uint x, uint y, bool alive);
        void set(uint n, bool alive);
        bool in_bounds(uint n);
        uint num_live = 0;
        uint round_num = 0;
};
