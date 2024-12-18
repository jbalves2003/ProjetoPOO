#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "Map.h"
#include "Caravana.h"
#include <vector>
#include <string>

class CommandHandler {
private:
    Map* currentMap;
    std::vector<Caravana*> caravanas; // Vetor para armazenar as caravanas
    std::vector<Caravana*> barbaros; // Vetor para armazenar as caravanas bárbaras

public:
    CommandHandler(Map* initialMap);
    ~CommandHandler();
    void handleCommand(const std::string& command);
    Map* getCurrentMap() const;
    void initializeCaravans(); // Método para inicializar caravanas
    void initializeBarbaros();// Método para inicializar bárbaros

};

#endif