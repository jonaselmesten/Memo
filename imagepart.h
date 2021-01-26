//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G


#ifndef IMAGEPART_H
#define IMAGEPART_H

#include "cardpart.h"
#include <string>

/**
 * @brief The ImagePart class
 * A class that is represented as a visible image that can be shown in the GUI.
 */
class ImagePart: public CardPart {

public:

    ImagePart(std::string imagePath);

    ImagePart(const ImagePart &rhs); //Copy

    ImagePart(ImagePart &&rhs); //Move const

    ImagePart& operator =(const ImagePart &rhs); //Copy assign

    ImagePart& operator =(ImagePart &&rhs); //Move assign

    QVBoxLayout* toGui();

    std::string toSaveable();

    void changeImagePath(std::string imagePath);

    ~ImagePart();

private:

    void swap(ImagePart &lhs, ImagePart &rhs);

    std::string imagePath;

};

#endif // IMAGEPART_H
