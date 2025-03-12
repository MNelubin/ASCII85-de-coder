#include "../include/ascii85.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    bool decode_mode = false;
    
    if (argc == 2) {
        string arg = argv[1];
        if (arg == "-d") decode_mode = true;
        else if (arg != "-e") {
            cerr << "Usage: " << argv[0] << " [-d | -e]\n";
            return 1;
        }
    } else if (argc > 2) {
        cerr << "Usage: " << argv[0] << " [-d | -e]\n";
        return 1;
    }

    if (decode_mode) {
        if (!decode(cin, cout)) return 1;
    } else {
        char buffer[4];
        while (cin.read(buffer, 4)) {
            encode(buffer, cin.gcount(), cout);
        }
        encode(buffer, cin.gcount(), cout); // Обработка последнего блока
    }
    
    return 0;
}