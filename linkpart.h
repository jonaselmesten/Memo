#ifndef LINKPART_H
#define LINKPART_H

#include "textpart.h"

/**
 * @brief The LinkPart class
 * A class that holds a hyperlink that can be clicked.
 * Shown as text in the GUI.
 */
class LinkPart: public CardPart {

public:

    LinkPart(QString text);

    LinkPart(const LinkPart &rhs); //Copy

    LinkPart(LinkPart &&rhs); //Move const

    LinkPart& operator =(const LinkPart &rhs); //Copy assign

    LinkPart& operator =(LinkPart &&rhs); //Move assign

    QVBoxLayout* toGui();

    std::string toSaveable();

    ~LinkPart();

private:

    void LinkPart::swap(LinkPart &lhs, LinkPart &rhs);

    QString text;
};

#endif // LINKPART_H
