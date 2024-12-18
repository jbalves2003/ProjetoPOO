#include "CommandHandler.h"
#include "ComercioCaravana.h"
#include "MilitarCaravana.h"
#include "SecretaCaravana.h"
#include "Cidade.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath> // Para usar std::abs
 #include <random>

CommandHandler::CommandHandler(Map* initialMap) : currentMap(initialMap) {
   initializeCaravans();
    initializeBarbaros();
}

CommandHandler::~CommandHandler() {
   if (currentMap)
      delete currentMap;
    for (Caravana* caravana : caravanas) {
       delete caravana;
    }
    caravanas.clear();
    for(Caravana* barbaro : barbaros) {
        delete barbaro;
    }
   barbaros.clear();

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
              initializeBarbaros();
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

    }  else if (tokens[0] == "prox") {
       if (tokens.size() == 2) {
         try {
           int turns = std::stoi(tokens[1]);
              for (int i = 0; i < turns; ++i) {
               // Combate
                std::vector<std::pair<Caravana*, Caravana*>> combates;
                  for (Caravana* caravana : caravanas) {
                     for (Caravana* barbaro : barbaros) {
                       if (std::abs(caravana->getRow() - barbaro->getRow()) <= 1 &&
                             std::abs(caravana->getCol() - barbaro->getCol()) <= 1) {
                          combates.push_back({caravana, barbaro});
                             }
                         }
                      }
                    for (const auto& combate : combates) {
                      Caravana* caravana = combate.first;
                      Caravana* barbaro = combate.second;

                        int result = caravana->combat(barbaro);
                        if (result > 0) {
                          std::cout << "Caravana " << caravana->getId() << " venceu o combate contra o barbaro " << barbaro->getId() << std::endl;
                            // Remover barbaro
                          for (size_t i = 0; i < barbaros.size(); ++i) {
                             if (barbaros[i]->getId() == barbaro->getId()) {
                               delete barbaros[i];
                                barbaros.erase(barbaros.begin() + i);
                                  break;
                                   }
                               }
                           } else if (result < 0) {
                          std::cout << "Caravana " << caravana->getId() << " perdeu o combate contra o barbaro " << barbaro->getId() << std::endl;
                           // Remover Caravana
                          for (size_t i = 0; i < caravanas.size(); ++i) {
                             if (caravanas[i]->getId() == caravana->getId()) {
                                delete caravanas[i];
                                 caravanas.erase(caravanas.begin() + i);
                                  break;
                              }
                           }

                         } else {
                           std::cout << "Combate entre a Caravana " << caravana->getId() << " e o barbaro " << barbaro->getId() << " resultou num empate" << std::endl;
                           }
                     }
                  std::cout << "Avançando turno..." << std::endl;
                }
                   currentMap->printMap(); //Imprimir o mapa apos os combates

            } catch (const std::invalid_argument& e) {
              std::cerr << "Use: prox <numero_de_turnos>" << std::endl;
              }
          } else {
              std::cout << "Use: prox <numero_de_turnos>" << std::endl;
              }
    }else if (tokens[0] == "compra") {
        if (tokens.size() == 3) {
            try {
                 int cityId = std::stoi(tokens[1]);
                 int amount = std::stoi(tokens[2]);

                  bool cidadeEncontrada = false;
                   for (Cidade* cidade : currentMap->getCidades()) {
                        if (cidade->getId() == cityId) {
                            cidadeEncontrada = true;
                               // Procurar a caravana mais proxima da cidade
                            int closestCaravanId = -1;
                            double closestDistance = std::numeric_limits<double>::max();
                              for(Caravana* caravana : caravanas)
                              {
                                double distance = std::sqrt(std::pow(caravana->getRow() - cidade->getRow(), 2) + std::pow(caravana->getCol() - cidade->getCol(), 2));
                                if(distance < closestDistance)
                                {
                                  closestDistance = distance;
                                  closestCaravanId = caravana->getId();
                                }
                              }
                            // Se houver uma caravana próxima, permite fazer a compra
                            if(closestCaravanId != -1)
                            {
                              for(Caravana* caravana : caravanas)
                              {
                                if(caravana->getId() == closestCaravanId)
                                {
                                      if(cidade->getStock() >= amount)
                                     {
                                          int buyPrice = currentMap->getBuyPrice();
                                           int totalPrice = amount * buyPrice;
                                           if(amount <= caravana->getCapacity()){
                                               if (totalPrice <= currentMap->getInitialCoins()){ // Por enquanto, como não temos um atributo de moedas nas caravanas, usamos as moedas iniciais para testar o sistema.
                                                   // Implementar lógica de compra aqui
                                                   cidade->setStock(cidade->getStock() - amount);
                                                    currentMap->setInitialCoins(currentMap->getInitialCoins() - totalPrice);  // Por enquanto, como não temos um atributo de moedas nas caravanas, usamos as moedas iniciais para testar o sistema.
                                                    std::cout << "Caravana " << closestCaravanId << " comprou " << amount << " unidades em Cidade " << cityId << " por " << totalPrice << " moedas." << std::endl;
                                               }else{
                                                   std::cout << "Moedas insuficientes na caravana " << closestCaravanId << std::endl;
                                                 }
                                            }else {
                                              std::cout << "Capacidade de carga da caravana " << closestCaravanId << " insuficiente" << std::endl;
                                             }

                                        }else {
                                             std::cout << "Stock insuficiente na cidade " << cityId << std::endl;
                                         }
                                    }
                               }
                             } else{
                                 std::cout << "Nenhuma caravana próxima da cidade" << cityId << std::endl;
                             }


                         }
                    }
                    if(!cidadeEncontrada)
                     std::cout << "Cidade com ID " << cityId << " não encontrada" << std::endl;

            } catch (const std::invalid_argument& e) {
               std::cerr << "Use: compra <id_cidade> <quantidade>" << std::endl;
            }
        }else{
              std::cout << "Use: compra <id_cidade> <quantidade>" << std::endl;
        }

    }else if (tokens[0] == "vende") {
        if (tokens.size() == 3) {
            try {
                 int cityId = std::stoi(tokens[1]);
                 int amount = std::stoi(tokens[2]);

                  bool cidadeEncontrada = false;
                  for (Cidade* cidade : currentMap->getCidades()) {
                      if (cidade->getId() == cityId) {
                            cidadeEncontrada = true;
                               // Procurar a caravana mais proxima da cidade
                            int closestCaravanId = -1;
                            double closestDistance = std::numeric_limits<double>::max();
                              for(Caravana* caravana : caravanas)
                              {
                                double distance = std::sqrt(std::pow(caravana->getRow() - cidade->getRow(), 2) + std::pow(caravana->getCol() - cidade->getCol(), 2));
                                if(distance < closestDistance)
                                {
                                  closestDistance = distance;
                                  closestCaravanId = caravana->getId();
                                }
                              }
                            // Se houver uma caravana próxima, permite fazer a venda
                            if(closestCaravanId != -1)
                            {
                               for(Caravana* caravana : caravanas)
                              {
                                if(caravana->getId() == closestCaravanId)
                                {
                                    if(amount > 0){
                                        int sellPrice = currentMap->getSellPrice();
                                         int totalPrice = amount * sellPrice;
                                        // Implementar lógica de venda aqui
                                          cidade->setStock(cidade->getStock() + amount);
                                         currentMap->setInitialCoins(currentMap->getInitialCoins() + totalPrice);   // Por enquanto, como não temos um atributo de moedas nas caravanas, usamos as moedas iniciais para testar o sistema.
                                         std::cout << "Caravana " << closestCaravanId << " vendeu " << amount << " unidades em Cidade " << cityId << " por " << totalPrice << " moedas." << std::endl;

                                     }else{
                                        std::cout << "Quantidade a vender inválida!" << std::endl;
                                      }
                                }
                              }
                            } else{
                                 std::cout << "Nenhuma caravana próxima da cidade" << cityId << std::endl;
                             }
                         }
                    }
                    if(!cidadeEncontrada)
                       std::cout << "Cidade com ID " << cityId << " não encontrada" << std::endl;
            } catch (const std::invalid_argument& e) {
               std::cerr << "Use: vende <id_cidade> <quantidade>" << std::endl;
            }
        }else{
             std::cout << "Use: vende <id_cidade> <quantidade>" << std::endl;
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

void CommandHandler::initializeBarbaros(){
       for (Caravana* barbaro : barbaros) {
             delete barbaro;
          }
         barbaros.clear();


     if (currentMap == nullptr) {
          return;
       }

        int barbaroId = caravanas.size() + 1; //Garante que não existe conflito de Ids
       int rows = currentMap->getRows();
       int cols = currentMap->getCols();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
             if (currentMap->getBuffer()->getGrid()[i][j] == 'b') {
               barbaros.push_back(new MilitarCaravana(barbaroId++, i, j, 5, 2, 20, 'b'));  //Inicializar caravanas bárbaras com valores por defeito
                 }
              }
           }
 }