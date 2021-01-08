#ifndef CARDPART_H
#define CARDPART_H

#include <QVBoxLayout>
#include <string>

class CardPart
{

protected:

    QVBoxLayout* layout;

    CardPart(QVBoxLayout* layout) : layout(layout) {}

public:

    virtual QVBoxLayout* to_gui() = 0;

    virtual std::string to_saveable() = 0;

};

#endif // CARDPART_H
