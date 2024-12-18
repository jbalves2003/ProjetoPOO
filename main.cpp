#include "Map.h"
#include "CommandHandler.h"
#include <iostream>
#include <string>

int main() {
    // Criar um objeto Map inicial
    Map* initialMap = new Map("config.txt");

    // Criar um objeto CommandHandler, com o mapa inicial
    CommandHandler commandHandler(initialMap);

    if (!commandHandler.getCurrentMap()) {
        std::cerr << "Erro ao carregar mapa inicial!" << std::endl;
        return 1;
    }

    int currentTurn = 0; // Variável para controlar os turnos
    bool firstTurn = true; // Flag para controlar o primeiro turno

    // Loop principal do jogo
    std::string command;
    while (true) {
         std::cout << "> "; // Prompt
        std::getline(std::cin, command); // Lê o comando do usuário

        if(firstTurn && command != "prox 1"){
          commandHandler.handleCommand(command);
           continue; // Se for o primeiro turno, não avança turnos e continua o loop
        }
        else if(firstTurn && command == "prox 1"){
             firstTurn = false;
           currentTurn++; // Avançar para o primeiro turno
           std::cout << "Turno " << currentTurn << std::endl;
           commandHandler.getCurrentMap()->printMap();// Mostrar o estado do mapa no início do turno
           commandHandler.handleCommand(command);
         }
         else{
            currentTurn++; // Avançar para o próximo turno
            std::cout << "Turno " << currentTurn << std::endl;
            commandHandler.getCurrentMap()->printMap();// Mostrar o estado do mapa no início do turno
            commandHandler.handleCommand(command);
        }

    }

    return 0;
}