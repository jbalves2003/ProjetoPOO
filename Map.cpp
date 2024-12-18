#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Map::Map(const char* filename) : buffer(nullptr), rows(0), cols(0),initial_coins(0), item_spawn_interval(0),
  item_duration(0), max_items(0), sell_price(0), buy_price(0), caravan_price(0), barbarian_spawn_interval(0), barbarian_duration(0)
{
        loadMap(filename);
}

Map::~Map() {
        if(buffer)
            delete buffer;
}


bool Map::loadMap(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return false;
    }

     std::string line;
     std::string key;
     int value;

      // Ler as dimensões
     if(std::getline(file, line)){
         std::istringstream iss(line);
         iss >> key >> value;
          if(key != "linhas"){
             std::cerr << "Erro ao ler o numero de linhas" << std::endl;
              file.close();
              return false;
            }
          rows = value;
    }
     if(std::getline(file, line)){
          std::istringstream iss(line);
          iss >> key >> value;
            if(key != "colunas"){
                std::cerr << "Erro ao ler o numero de colunas" << std::endl;
                file.close();
                 return false;
            }
             cols = value;
    }

     buffer = new Buffer(rows, cols);

     // Ler o mapa
    for (int i = 0; i < rows; ++i) {
        if(std::getline(file,line)) {
           buffer->moveCursor(i, 0);
            buffer->writeString(line.c_str());
        } else {
            std::cerr << "Erro ao ler o mapa" << std::endl;
            file.close();
            delete buffer;
            buffer = nullptr;
            return false;
        }
    }


    // Ler as restantes informações do arquivo
     while(std::getline(file,line)) {
          std::istringstream iss(line);
          iss >> key >> value;
         if(key == "moedas")
            initial_coins = value;
         else if(key == "instantes_entre_novos_itens")
            item_spawn_interval = value;
          else if(key == "duração_item")
            item_duration = value;
         else if(key == "max_itens")
             max_items = value;
        else if(key == "preço_venda_mercadoria")
            sell_price = value;
        else if(key == "preço_compra_mercadoria")
             buy_price = value;
         else if (key == "preço_caravana")
            caravan_price = value;
        else if (key == "instantes_entre_novos_barbaros")
             barbarian_spawn_interval = value;
        else if(key == "duração_barbaros")
             barbarian_duration = value;
     }

    file.close();

    return true;
}

void Map::printMap() {
    if (buffer) {
      buffer->print();
    }
}

int Map::getRows() const {
  return rows;
}
int Map::getCols() const {
  return cols;
}
 int Map::getInitialCoins() const {
  return initial_coins;
}
int Map::getItemSpawnInterval() const {
  return item_spawn_interval;
}
int Map::getItemDuration() const {
  return item_duration;
}
int Map::getMaxItems() const {
  return max_items;
}
int Map::getSellPrice() const {
  return sell_price;
}
int Map::getBuyPrice() const {
  return buy_price;
}
int Map::getCaravanPrice() const {
  return caravan_price;
}
int Map::getBarbarianSpawnInterval() const {
  return barbarian_spawn_interval;
}
int Map::getBarbarianDuration() const {
  return barbarian_duration;
}

Buffer* Map::getBuffer() {
   return buffer;
 }