#ifndef TEXTPART_H
#define TEXTPART_H

#include "cardpart.h"
#include <QString>

class TextPart: public CardPart {

    QString text;

public:

    TextPart(QString text);

    QVBoxLayout* to_gui();

    std::string to_saveable();

};

#endif // TEXTPART_H
