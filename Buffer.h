#ifndef BUFFER_H
#define BUFFER_H

class Buffer {
private:
    int rows;
    int cols;
    char** grid;
    int cursorRow;
    int cursorCol;

public:
    // Construtor
    Buffer(int rows, int cols);

    // Destrutor
    ~Buffer();

    // Métodos
    void initialize();
    void writeChar(char c);
    void writeString(const char* str);
    void clear();
    void print();
    void moveCursor(int row, int col);

    // Funções de Acesso
    int getRows() const;
    int getCols() const;
    char** getGrid(); // Adicionando o método getGrid

};

#endif