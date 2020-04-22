#include <iostream>
#include "Sudoku.h"

int main() {
    int sum = 0;
    for(int i = 1; i <= 50; i++) {
        std::ostringstream ss;
        ss << "src/sudokus/" << i << ".txt";
        Sudoku s(ss.str());
        std::cout << "Now solving sudoku " << i << std::endl;
        s.solve();
        if(!s.isSolved()) {
            std::cerr << "failed to solve sudoku " << i << std::endl;
            exit(1);
        }
        sum += s.getNumber();
        std::cout << "Found number " << s.getNumber() << " sum is now " << sum << std::endl;
    }

    std::cout << "Sum: " << sum << std::endl;
    return 0;
}