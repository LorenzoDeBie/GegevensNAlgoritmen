#ifndef SUDOKU_H
#define SUDOKU_H

#include <fstream>
#include <iostream>
#include <set>
    using std::set;

#include <sstream>
#include <string>

#define SIZE 9
#define EMPTY 0

class Sudoku{
public:
    Sudoku(const std::string filename);
    bool isSolved();
    bool solve();
    friend std::ostream& operator<< (std::ostream &out, const Sudoku &s);
    int getNumber();
private:
    int grid[SIZE][SIZE];

    bool checkRow(int row, int n) const;
    bool checkCol(int col, int n) const;
    bool checkBox(int row, int col, int n) const;
};

std::ostream& operator<< (std::ostream &out, const Sudoku &s){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            out << s.grid[i][j] << " " ;

            if ((j+1) % 3 == 0 && j < 8)
                out << "| ";
        }
        out << std::endl;
        if ((i+1) % 3 == 0 && i < 8){
            out << "------+-------+------" << std::endl;
        }
    }
    return out;
}

Sudoku::Sudoku(const std::string filename){
    std::ifstream infile(filename);
    if (infile){
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                infile >> grid[i][j];
            }
        }
    }
}

bool Sudoku::isSolved(){
    //check all rows
    for(int row = 0; row < SIZE; row++) {
        set<int> rowNumbers;
        for(int col = 0; col < SIZE; col++) {
            int cell = grid[row][col];
            //sudoku is not solved if a cell is empty
            if(cell == EMPTY) return false;
            //number in cell cannot be bigger than size
            if(cell > SIZE) return false;
            int currentsize = rowNumbers.size();
            rowNumbers.insert(cell);
            //if the size does not increase when adding the cell, this number was already in the set --> not a good sudoku
            if(currentsize >= rowNumbers.size()) return false;
        }
    }

    //check all columns
    for(int col = 0; col < SIZE; col++) {
        set<int> colNumbers;
        for(int row = 0; row < SIZE; row++) {
            int cell = grid[row][col];
            //no need to check for empty or too large here because we already did
            int currentsize = colNumbers.size();
            colNumbers.insert(cell);
            if(currentsize >= colNumbers.size()) return false;
        }
    }

    // to prevent having to run over the sudoku twice we need SIZE sets of SIZE length so we can store all the column values
    // if memory usage isn't a concern we could do that
    return true;
}


bool Sudoku::solve(){
    //loop over all rows
    for(int row = 0; row < SIZE; row++) {
        //loop over all cells in this row
        for(int col = 0; col < SIZE; col++) {
            int cell = grid[row][col];
            //we only need to change empty squares
            if(cell != 0) continue;
            //check all numbers for this cell
            for(int i = 1; i <= SIZE; i++) {
                //grid[row][col] = i;
                //check if row && col still valid
                if(checkRow(row, i) && checkCol(col, i) && checkBox(row / 3, col / 3, i)) {
                    //try to solve rest of sudoku with this test
                    grid[row][col] = i;
                    if(solve()) return true;
                }
            }
            // we tried all possible numbers and found no solution!
            grid[row][col] = EMPTY;
            return false;
        }
    }
    return true;
}

/// calculates the number of the top left 3 digits
int Sudoku::getNumber() {
    return grid[0][0] * 100 + grid[0][1] * 10 + grid[0][2];
}

/**
 * checks row for the number n
 * @param row number of row to search
 * @param n number to search for
 * @return if n is in row
 */
bool Sudoku::checkRow(int row, int n) const {
    for(int col = 0; col < SIZE; col++) {
        if(grid[row][col] == n) return false;
    }
    return true;
}

/**
 * checks col for the number n
 * @param col number of column to search
 * @param n number to search for
 * @return if n is in col
 */
bool Sudoku::checkCol(int col, int n) const {
    for(int row = 0; row < SIZE; row++) {
        if(grid[row][col] == n) return false;
    }
    return true;
}

/**
 * checks 3x3 box for n
 * @param row row of 3x3 box
 * @param col col of 3x3 box
 * @param n number to search for
 * @return if n is in 3x3 box
 */
bool Sudoku::checkBox(int row, int col, int n) const {
    for(int r = row*3; r < (row + 1)*3; r++) {
        for(int c = col*3; c < (col+1)*3; c++) {
            if(grid[r][c] == n) return false;
        }
    }
    return true;
}

#endif