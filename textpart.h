//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#ifndef TEXTPART_H
#define TEXTPART_H

#include "cardpart.h"
#include <QString>

/**
 * @brief The TextPart class
 * A class that represents a simple piece of text that can be placed in the GUI.
 */
class TextPart: public CardPart {

public:

    TextPart(QString text);

    TextPart(const TextPart &rhs); //Copy

    TextPart(TextPart &&rhs); //Move const

    TextPart& operator =(const TextPart &rhs); //Copy assign

    TextPart& operator =(TextPart &&rhs); //Move assign

    QVBoxLayout* toGui();

    std::string toSaveable();

    ~TextPart();

private:

    void swap(TextPart &lhs, TextPart &rhs);

    QString text;
};

#endif // TEXTPART_H
