#pragma once
#include "utils.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Program prima jedan argument u komandnoj liniji!" << std::endl;
        return 0;
    }


    playGame();

    std::cin.get();
    return 0;
}
