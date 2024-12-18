//
// Created by 2003j on 18/12/2024.
//

#ifndef MILITARCARAVANA_H
#define MILITARCARAVANA_H


#include "Caravana.h"

class MilitarCaravana : public Caravana {
public:
    MilitarCaravana(int id, int row, int col, int capacity, int crew, int water, char symbol);
    void move(int newRow, int newCol) override;
};

#endif
//MILITARCARAVANA_H
