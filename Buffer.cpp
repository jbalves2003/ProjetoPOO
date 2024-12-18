#include "Buffer.h"
#include <iostream>
#include <cstring> // Required for strlen

Buffer::Buffer(int rows, int cols) : rows(rows), cols(cols), cursorRow(0), cursorCol(0) {
    grid = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new char[cols];
    }
    initialize();
}

Buffer::~Buffer() {
    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}


void Buffer::initialize() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = ' ';
        }
    }
}

void Buffer::writeChar(char c) {
    if (cursorRow >= 0 && cursorRow < rows && cursorCol >= 0 && cursorCol < cols) {
        grid[cursorRow][cursorCol] = c;
        // Avançar cursor para a direita, com quebra de linha
        cursorCol++;
        if (cursorCol >= cols)
        {
            cursorCol = 0;
            cursorRow++;
        }
    }
}

void Buffer::writeString(const char* str) {
    for (size_t i = 0; i < strlen(str); i++) {
        writeChar(str[i]);
    }
}


void Buffer::clear() {
    initialize();
    cursorRow = 0;
    cursorCol = 0;
}


void Buffer::print() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
}

void Buffer::moveCursor(int row, int col) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        cursorRow = row;
        cursorCol = col;
    }
}

int Buffer::getRows() const
{
    return rows;
}

int Buffer::getCols() const
{
    return cols;
}

char** Buffer::getGrid() {
    return grid;
}