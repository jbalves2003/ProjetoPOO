#include "ComercioCaravana.h"

ComercioCaravana::ComercioCaravana(int id, int row, int col, int capacity, int crew, int water, char symbol)
    : Caravana(id, row, col, "Comercio", capacity, crew, water, symbol) {}

void ComercioCaravana::move(int newRow, int newCol){
    setRow(newRow);
    setCol(newCol);
}