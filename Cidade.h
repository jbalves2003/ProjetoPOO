#ifndef CIDADE_H
#define CIDADE_H

class Cidade {
private:
    int id;
    int row;
    int col;
    int stock; // Quantidade de mercadoria em stock
    int price;
    char symbol;

public:
    // Construtor
    Cidade(int id, int row, int col, int stock, int price, char symbol);

    // Métodos de Acesso
    int getId() const;
    int getRow() const;
    int getCol() const;
    int getStock() const;
    int getPrice() const;
    char getSymbol() const;
    void setStock(int stock);


};

#endif