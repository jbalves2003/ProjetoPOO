#ifndef MAP_H
#define MAP_H

#include "Buffer.h"
#include <string>
#include <vector>
#include "Cidade.h"


class Map {
private:
    int rows;
    int cols;
    Buffer* buffer;
    int initial_coins;
    int item_spawn_interval;
    int item_duration;
    int max_items;
    int sell_price;
    int buy_price;
    int caravan_price;
    int barbarian_spawn_interval;
    int barbarian_duration;
    std::vector<Cidade*> cidades;

public:
    // Construtor
    Map(const char* filename);

    // Destrutor
    ~Map();

    // Métodos
    bool loadMap(const char* filename);
    void printMap();

    //Funções de Acesso
    int getRows() const;
    int getCols() const;
    int getInitialCoins() const;
    int getItemSpawnInterval() const;
    int getItemDuration() const;
    int getMaxItems() const;
    int getSellPrice() const;
    int getBuyPrice() const;
    int getCaravanPrice() const;
    int getBarbarianSpawnInterval() const;
    int getBarbarianDuration() const;

    Buffer* getBuffer();
    std::vector<Cidade*> getCidades();
    void initializeCities(); // Método para inicializar cidades

    void setInitialCoins(int coins);

};

#endif