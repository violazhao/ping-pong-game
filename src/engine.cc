//
// Created by Viola F Zhao on 5/2/20.
// taken from snake

#include <mylibrary/engine.h>
#include <mylibrary/direction.h>
#include <mylibrary/location.h>

namespace mylibrary {

// Converts a direction into a delta location.
Location FromDirection(const Direction direction) {
    switch (direction) {
        case Direction::kUp:
            return {-1, 0};
        case Direction::kDown:
            return {+1, 0};
        case Direction::kLeft:
            return {0, -1};
        case Direction::kRight:
            return {0, +1};
    }

    throw std::out_of_range("switch statement not matched");
}

void Engine::SetDirection(const mylibrary::Direction direction) {
    direction_ = direction;
}

} //namespace mylibrary