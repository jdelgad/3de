//#include "SDL.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class Sector {
public:
private:
    float floor;
    float ceiling;
    signed char *neighbors;
};

void LoadData() {
    const char SPACE = ' ';

    std::ifstream map;
    map.open("map-clear.txt", std::fstream::in);

    if (!map.is_open()) {
        std::cerr << "Could not open map-clear.txt" << std::endl;
        throw std::runtime_error("file does not exist");
    }

    std::string line;
    int vertex = 0;
    int sector = 0;
    int player = 0;
    while (getline(map, line)) {
        std::stringstream ss(line);
        std::string type;
        getline(ss, type, SPACE);
        if (type.compare("vertex") == 0) {
            vertex++;
            std::cout << "found a vertex!" << std::endl;
        } else if (type.compare("sector") == 0) {
            std::cout << "SECTOR!" << std::endl;
            sector++;
        } else if (type.compare("player") == 0) {
            std::cout << "player" << std::endl;
            player++;
        } else {
            std::cerr << "invalid line = " << line << std::endl;
            throw std::runtime_error("invalid data format");
        }
    }

    std::cout << "vertex = " << vertex << std::endl;
    std::cout << "sector = " << sector << std::endl;
    std::cout << "player = " << player << std::endl;

    map.close();
}

int main(int argc, char *argv[]) {
    LoadData();
    return 0;
}