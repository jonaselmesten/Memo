//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#include "deckformatexception.h"

DeckFormatException::DeckFormatException() {}

const char * DeckFormatException::what () const throw () {
      return "Fromat error found.";
}
