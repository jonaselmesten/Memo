#ifndef DECKHOLDER_H
#define DECKHOLDER_H

#include <map>
#include <string>
#include <vector>
#include "card.h"

class DeckHolder
{
    std::map<std::string, std::vector<Card*>*> deck_map;


public:
    DeckHolder();

    bool addNewDeck(std::string name);

    void deleteDeck(std::string name);

    std::vector<Card*>& getDeck(std::string name);

    void printMap();

    bool hasDeck(std::string name);
};

#endif // DECKHOLDER_H
