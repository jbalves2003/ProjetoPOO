//
// Created by 2003j on 18/12/2024.
//

#include "SecretaCaravana.h"
SecretaCaravana::SecretaCaravana(int id, int row, int col, int capacity, int crew, int water, char symbol)
    : Caravana(id, row, col, "Secreta", capacity, crew, water, symbol) {}

void SecretaCaravana::move(int newRow, int newCol){
    setRow(newRow);
    setCol(newCol);
}