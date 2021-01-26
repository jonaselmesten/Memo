#ifndef DECKFORMATEXCEPTION_H
#define DECKFORMATEXCEPTION_H

#include <exception>

/**
 * @brief The DeckFormatException class
 * Exception class for when errors in the deck format occur during I/O operations.
 */
class DeckFormatException : public std::exception
{
public:
    DeckFormatException();

    const char * what () const throw ();
};

#endif // DECKFORMATEXCEPTION_H
