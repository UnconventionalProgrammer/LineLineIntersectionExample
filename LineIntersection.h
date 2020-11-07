//
// Created by Dan on 07/11/2020.
//

#ifndef LINEINTERSECTION_H
#define LINEINTERSECTION_H

#include "SFUIBase.h"
#include "LineSegment.h"

class LineIntersection : public SFUIBase
{
private:
    void mouseMoved(const sf::Event::MouseMoveEvent &event) override;
    std::tuple<float, float> screenToWorldCoords(const std::tuple<int, int> &screenCoords);
    std::tuple<float, float> worldToScreenCoords(const std::tuple<float, float> &worldCoords);
    void mouseButtonReleased(const sf::Event::MouseButtonEvent &event) override;
    void draw(sf::RenderTarget &window) override;

    std::vector<jnz::LineSegment<float>> mLineSegments;

    sf::CircleShape mEndPointMouseOver;
    bool mIsDraggingEndPoint;
    bool mIsMouseOverEndPoint;

    jnz::LineSegment<float> *mSelectedLineSegment;
    std::size_t mSelectedLineEndPoint;
public:
    LineIntersection(size_t width, size_t height, const std::string &title);

};


#endif //LINEINTERSECTION_H
