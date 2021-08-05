//
// Created by Viola Zhao on 5/2/20.

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <string>

namespace mylibrary {

struct Player {
    Player(const std::string& name, size_t score) : name(name), score(score) {}
    std::string name;
    size_t score;
};

} // namespace mylibrary

#endif //FINALPROJECT_PLAYER_H
