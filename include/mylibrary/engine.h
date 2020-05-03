//
// Created by Viola F Zhao on 5/2/20.
// taken from snake

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include "direction.h"
#include "location.h"

namespace mylibrary {

class Engine {
public:
    // Changes the direction of the snake for the next time step.
    void SetDirection(Direction);

private:
    Direction direction_;
};

} // namespace mylibrary


#endif //FINALPROJECT_ENGINE_H
