#include "deckholder.h"
#include <iostream>

DeckHolder::DeckHolder() {

}

void DeckHolder::printMap() {
    std::map<std::string, std::vector<Card*>*>::iterator itr;

    std::cout << "--------" << std::endl;
    for (itr = deck_map.begin(); itr != deck_map.end(); ++itr) {
        std::cout << itr->first << std::endl;
    }
    std::cout << "--------" << std::endl;
}

bool DeckHolder::addNewDeck(std::string name) {

    std::pair<std::string, std::vector<Card*>*> card_pair(name, new std::vector<Card*>);

    if(hasDeck(name))
        return false;

    deck_map.insert(card_pair);
    return true;
}

bool DeckHolder::hasDeck(std::string name) {

    std::map<std::string, std::vector<Card*>*>::iterator itr = deck_map.find(name);
    if ( deck_map.end() != itr ) {
        return true;
    }else
        return false;
}

void DeckHolder::deleteDeck(std::string name) {
    deck_map.erase(name);
    printMap();
}

std::vector<Card*>& DeckHolder::getDeck(std::string name) {
    std::map<std::string, std::vector<Card*>*>::iterator itr = deck_map.find(name);
    return *itr->second;
}
