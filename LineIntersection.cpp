//
// Created by Dan on 07/11/2020.
//

#include "LineIntersection.h"
#include <iostream>

LineIntersection::LineIntersection(const size_t width, const size_t height, const std::string &title)
: SFUIBase(width, height, title), mEndPointMouseOver(5), mIsMouseOverEndPoint(false), mIsDraggingEndPoint(false), mSelectedLineSegment(nullptr), mSelectedLineEndPoint(0)
{
    mEndPointMouseOver.setOrigin(5.0, 5.0);
    mEndPointMouseOver.setOutlineThickness(2.0);
    mEndPointMouseOver.setFillColor(sf::Color::Transparent);
    mEndPointMouseOver.setOutlineColor(sf::Color::Transparent);
}

void LineIntersection::mouseMoved(const sf::Event::MouseMoveEvent &event)
{
    if(this->mIsDraggingEndPoint) //If the dragging flag is set and the mouse has moved, move the selected end point
    {
        if(this->mSelectedLineEndPoint == 0)
            this->mSelectedLineSegment->setEndPoint<0>(this->screenToWorldCoords({event.x, event.y}));
        else
            this->mSelectedLineSegment->setEndPoint<1>(this->screenToWorldCoords({event.x, event.y}));
        this->mEndPointMouseOver.setPosition(static_cast<float>(event.x), static_cast<float>(event.y));
        return;
    }

    mIsMouseOverEndPoint = false;
    mSelectedLineSegment = nullptr;
    for(auto &lineSeg : this->mLineSegments) //Loop over all line segments and check if the mouse is within range of a line end point
    {
        auto [distance, endPoint] = lineSeg.getShortestDistanceToEndPoint(this->screenToWorldCoords({event.x, event.y}));
        if(distance < 0.05)
        {
            mSelectedLineSegment = &lineSeg;
            auto endPointPosition = lineSeg.getEndPoint<0>();
            mSelectedLineEndPoint = 0;
            if(endPoint == 1)
            {
                endPointPosition = lineSeg.getEndPoint<1>();
                mSelectedLineEndPoint = 1;
            }
            auto [x, y] = this->worldToScreenCoords(endPointPosition);
            this->mEndPointMouseOver.setPosition(x, y);
            mIsMouseOverEndPoint = true;
        }
    }
}

void LineIntersection::mouseButtonReleased(const sf::Event::MouseButtonEvent &event)
{
    if(this->mIsDraggingEndPoint) //This must be a second click from the user, stop dragging an end point
    {
        this->mIsDraggingEndPoint = false;
        return;
    }

    if(!this->mIsMouseOverEndPoint) //If no end points are within range, create a new line segment and set an end to be dragged by the user
    {
        auto wCoords = screenToWorldCoords({event.x, event.y});
        mSelectedLineSegment = &this->mLineSegments.emplace_back(wCoords, wCoords);
        mSelectedLineEndPoint = 1;

        this->mIsDraggingEndPoint = true;
        this->mIsMouseOverEndPoint = true;
        this->mEndPointMouseOver.setPosition(static_cast<float>(event.x), static_cast<float>(event.y));
    }
    else
    {
        this->mIsDraggingEndPoint = true; //if a line segment end point is in range, start dragging it
    }
}

void LineIntersection::draw(sf::RenderTarget &window)
{
    window.clear();

    sf::VertexArray mLines(sf::Lines);
    std::vector<sf::CircleShape> mLineIntersections;

    for(auto &lineSeg : this->mLineSegments)
    {
        auto [aX, aY] = this->worldToScreenCoords(lineSeg.getEndPoint<0>());
        auto [bX, bY] = this->worldToScreenCoords(lineSeg.getEndPoint<1>());
        mLines.append({{aX, aY}, sf::Color::White});
        mLines.append({{bX, bY}, sf::Color::White});

        for(auto &intersectLineSeg : this->mLineSegments)
        {
            float lineMidWeight = lineSeg.intersect(intersectLineSeg);
            if(lineMidWeight > 0.0 && lineMidWeight < 1.0) //If the mid way point is above 0% and less than 100%, it intersects.
            {
                auto [iX, iY] = this->worldToScreenCoords(lineSeg.midPoint(lineMidWeight)); //Use the mid point to get a point along the line and covert that point to screen coordinates.
                auto &intersectionCircle = mLineIntersections.emplace_back(5, 30); //Add the new point to the list and set it's attributes.
                intersectionCircle.setFillColor(sf::Color::Red);
                intersectionCircle.setOrigin(5.0, 5.0);
                intersectionCircle.setPosition(iX, iY);
            }
        }
    }

    this->mEndPointMouseOver.setOutlineColor(mIsMouseOverEndPoint ? sf::Color::White : sf::Color::Transparent);
    this->mEndPointMouseOver.setFillColor(mIsDraggingEndPoint ? sf::Color::White : sf::Color::Transparent); //hide or show the highlight point

    for(auto &intersectionCircle : mLineIntersections)
        window.draw(intersectionCircle);

    window.draw(mLines);
    window.draw(mEndPointMouseOver);
}

//world coords are between 0.0 and 1.0.
std::tuple<float, float> LineIntersection::screenToWorldCoords(const std::tuple<int, int> &screenCoords)
{
    const auto screenSize = this->mWindow.getView().getSize();
    const auto [screenX, screenY] = screenCoords;
    return {static_cast<float>(screenX) * (1.0 / screenSize.x), static_cast<float>(screenY) * (1.0 / screenSize.y)};
}

std::tuple<float, float> LineIntersection::worldToScreenCoords(const std::tuple<float, float> &worldCoords)
{
    const auto screenSize = this->mWindow.getView().getSize();
    const auto [worldX, worldY] = worldCoords;
    return {worldX * screenSize.x, worldY * screenSize.y};
}
