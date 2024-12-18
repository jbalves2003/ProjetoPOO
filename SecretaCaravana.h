//
// Created by 2003j on 18/12/2024.
//

#ifndef SECRETACARAVANA_H
#define SECRETACARAVANA_H
#include "Caravana.h"

class SecretaCaravana : public Caravana {
public:
    SecretaCaravana(int id, int row, int col, int capacity, int crew, int water, char symbol);
    void move(int newRow, int newCol) override;
};

#endif//SECRETACARAVANA_H
