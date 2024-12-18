#include "Map.h"
#include "CommandHandler.h"
#include <iostream>
#include <string>


int main() {

    // Criar um objeto Map inicial
    Map* initialMap = new Map("config.txt");

    // Criar um objeto CommandHandler, com o mapa inicial
    CommandHandler commandHandler(initialMap);

    if(!commandHandler.getCurrentMap()){
        std::cerr << "Erro ao carregar mapa inicial!" << std::endl;
        return 1;
    }

    // Loop principal do jogo
    std::string command;
    while (true) {
        std::cout << "> "; // Prompt
        std::getline(std::cin, command); // Lê o comando do usuário
        commandHandler.handleCommand(command);
    }

    return 0;
}