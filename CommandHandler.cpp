#include "CommandHandler.h"
#include "ComercioCaravana.h"
#include "MilitarCaravana.h"
#include "SecretaCaravana.h"

#include <iostream>
#include <sstream>
#include <vector>

CommandHandler::CommandHandler(Map* initialMap) : currentMap(initialMap) {
   initializeCaravans();
}

CommandHandler::~CommandHandler() {
   if (currentMap)
      delete currentMap;
    for (Caravana* caravana : caravanas) {
       delete caravana;
    }
    caravanas.clear();
}

void CommandHandler::handleCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string token;
    std::vector<std::string> tokens;

    while(iss >> token)
    {
       tokens.push_back(token);
    }

     if (tokens.empty())
    {
      return;
    }

    if (tokens[0] == "config")
    {
       if(tokens.size() > 1){
          if (currentMap)
             delete currentMap;
           currentMap = new Map(tokens[1].c_str());
           if(currentMap)
            {
              currentMap->printMap();
             initializeCaravans();
             }
           else
              std::cerr << "Erro ao carregar novo mapa!" << std::endl;
          }
       else
           std::cout << "Use: config <nomeFicheiro>" << std::endl;

    } else if (tokens[0] == "sair") {
        std::cout << "Encerrando o programa." << std::endl;
        exit(0); // Termina o programa
    }else if (tokens[0] == "move") {
       if (tokens.size() == 4) {
           try {
                int caravanId = std::stoi(tokens[1]);
                int newRow = std::stoi(tokens[2]);
                int newCol = std::stoi(tokens[3]);

                bool caravanaEncontrada = false;
                  for (Caravana* caravana : caravanas) {
                      if (caravana->getId() == caravanId) {
                            int oldRow = caravana->getRow();
                            int oldCol = caravana->getCol();

                           // Limpar a posição antiga da caravana no buffer
                            currentMap->getBuffer()->moveCursor(oldRow,oldCol);
                            currentMap->getBuffer()->writeChar('.'); //Escreve um ponto na antiga posição

                           //Atualizar a posição da caravana
                           caravana->move(newRow, newCol);

                           // Colocar o símbolo da caravana na nova posição no buffer
                           currentMap->getBuffer()->moveCursor(newRow, newCol);
                           currentMap->getBuffer()->writeChar(caravana->getSymbol());


                          caravanaEncontrada = true;
                         }
                    }
                if(!caravanaEncontrada)
                   std::cout << "Caravana com ID " << caravanId << " não encontrada" << std::endl;
               else
                    currentMap->printMap();
            } catch (const std::invalid_argument& e) {
              std::cerr << "Erro ao converter argumentos move. Use move <id> <linha> <coluna>" << std::endl;
             }
            } else {
               std::cout << "Use: move <id> <linha> <coluna>" << std::endl;
            }

    }
     else {
       std::cout << "Comando inválido." << std::endl;
    }
}
 Map* CommandHandler::getCurrentMap() const {
   return currentMap;
 }


 void CommandHandler::initializeCaravans(){
     for (Caravana* caravana : caravanas) {
          delete caravana;
      }
     caravanas.clear();

   if (currentMap == nullptr) {
         return;
     }

    int caravanId = 1;
     int rows = currentMap->getRows();
     int cols = currentMap->getCols();
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
         if (currentMap->getBuffer()->getGrid()[i][j] == '^') {
          caravanas.push_back(new ComercioCaravana(caravanId++, i, j, 10, 3, 50, '^')); //Inicializar caravanas com valores por defeito, como sugerido
             }
            else if (currentMap->getBuffer()->getGrid()[i][j] == '1') {
            caravanas.push_back(new MilitarCaravana(caravanId++, i, j, 10, 3, 50, '1'));
            }
           else if(currentMap->getBuffer()->getGrid()[i][j] == '2') {
           caravanas.push_back(new SecretaCaravana(caravanId++, i, j, 10, 3, 50, '2'));
           }
          else if(currentMap->getBuffer()->getGrid()[i][j] == '3') {
              caravanas.push_back(new ComercioCaravana(caravanId++, i, j, 10, 3, 50, '3'));
           }
          else if(currentMap->getBuffer()->getGrid()[i][j] == '4') {
          caravanas.push_back(new MilitarCaravana(caravanId++, i, j, 10, 3, 50, '4'));
             }
         }
     }

 }