//
// Created by 2003j on 18/12/2024.
//

#include "MilitarCaravana.h"

MilitarCaravana::MilitarCaravana(int id, int row, int col, int capacity, int crew, int water, char symbol)
    : Caravana(id, row, col, "Militar", capacity, crew, water, symbol) {}

void MilitarCaravana::move(int newRow, int newCol){
    setRow(newRow);
    setCol(newCol);
}