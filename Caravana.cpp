#include "Caravana.h"

Caravana::Caravana(int id, int row, int col, const std::string& type, int capacity, int crew, int water, char symbol)
    : id(id), row(row), col(col), type(type), capacity(capacity), crew(crew), water(water), symbol(symbol) {}

int Caravana::getId() const {
    return id;
}

int Caravana::getRow() const {
    return row;
}

int Caravana::getCol() const {
    return col;
}
std::string Caravana::getType() const {
    return type;
}

int Caravana::getCapacity() const {
    return capacity;
}

int Caravana::getCrew() const {
    return crew;
}

int Caravana::getWater() const {
    return water;
}
char Caravana::getSymbol() const {
    return symbol;
}

void Caravana::setRow(int row) {
    this->row = row;
}
void Caravana::setCol(int col) {
    this->col = col;
}
void Caravana::setWater(int water) {
    this->water = water;
}