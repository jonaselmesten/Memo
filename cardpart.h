//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#ifndef CARDPART_H
#define CARDPART_H

#include <QVBoxLayout>
#include <string>
#include <iostream>

/**
 * @brief The CardPart class
 * The base for all the parts that go into card class.
 * All questions and answers that go into card will inherit from this class.
 * This class will make sure you implement toGui and toSavable so the object
 * can be used as a visible GUI-part and that its saveable to a file.
 */
class CardPart {

protected:

    QVBoxLayout* layout;

    CardPart(QVBoxLayout* layout) : layout(layout) {}

public:

    virtual QVBoxLayout* toGui() = 0;

    virtual std::string toSaveable() = 0;

    virtual ~CardPart() {};

};

#endif // CARDPART_H
