#ifndef CARAVANA_H
#define CARAVANA_H

#include <string>

class Caravana {
private:
    int id;
    int row;
    int col;
    std::string type;
    int capacity;
    int crew;
    int water;
    char symbol; // Simbolo da Caravana no mapa

public:
    // Construtor
    Caravana(int id, int row, int col, const std::string& type, int capacity, int crew, int water, char symbol);

    // Métodos de Acesso
    int getId() const;
    int getRow() const;
    int getCol() const;
    std::string getType() const;
    int getCapacity() const;
    int getCrew() const;
    int getWater() const;
    char getSymbol() const;
    void setRow(int row);
    void setCol(int col);
    void setWater(int water);


    // Método virtual para mover a caravana (será implementado nas classes derivadas)
    virtual void move(int newRow, int newCol) {}

    virtual ~Caravana() {}
};

#endif