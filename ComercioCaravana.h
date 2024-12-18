#ifndef COMERCIOCARAVANA_H
#define COMERCIOCARAVANA_H

#include "Caravana.h"

class ComercioCaravana : public Caravana {
public:
    ComercioCaravana(int id, int row, int col, int capacity, int crew, int water, char symbol);
    void move(int newRow, int newCol) override;
};

#endif
