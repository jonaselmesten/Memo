//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#include "linkpart.h"
#include <QLabel>
#include <iostream>
#include <algorithm>

LinkPart::LinkPart(QString text)
    : CardPart(new QVBoxLayout)
{
    std::string url =  "<a href=\"\"></a>";

    url.insert(11, text.simplified().toStdString());
    url.insert(9, text.simplified().toStdString());

    this->text = text.simplified();

    QLabel *label = new QLabel();
    label->setText(QString(url.c_str()));
    label->setTextFormat(Qt::RichText);
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setOpenExternalLinks(true);

    label->setWordWrap(true);
    label->setAlignment(Qt::AlignHCenter);

    this->layout->addWidget(label);
}

//Copy
LinkPart::LinkPart(const LinkPart &rhs)
    : LinkPart(rhs.text) {}

//Move const
LinkPart::LinkPart(LinkPart &&rhs)
    : LinkPart(rhs.text) {
    swap(*this, rhs);
}

//Copy assign
LinkPart& LinkPart::operator =(const LinkPart &rhs) {
    LinkPart temp(rhs);
    swap(*this, temp);

    return *this;
}

//Move assign
LinkPart& LinkPart::operator =(LinkPart &&rhs) {
    swap(*this, rhs);

    return *this;
}

void LinkPart::swap(LinkPart &lhs, LinkPart &rhs) {

    using std::swap;

    swap(lhs.text, rhs.text);
    swap(lhs.layout, rhs.layout);
}

QVBoxLayout* LinkPart::toGui() {
    return layout;
}

std::string LinkPart::toSaveable() {
    return text.toStdString();
}

LinkPart::~LinkPart() {
    delete layout;
}
