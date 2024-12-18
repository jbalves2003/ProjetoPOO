#include "Cidade.h"

Cidade::Cidade(int id, int row, int col, int stock, int price, char symbol)
    : id(id), row(row), col(col), stock(stock), price(price), symbol(symbol) {}

int Cidade::getId() const {
    return id;
}

int Cidade::getRow() const {
    return row;
}

int Cidade::getCol() const {
    return col;
}
int Cidade::getStock() const {
    return stock;
}
int Cidade::getPrice() const {
    return price;
}
char Cidade::getSymbol() const {
    return symbol;
}
void Cidade::setStock(int stock) {
    this->stock = stock;
}