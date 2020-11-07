//
// Created by Dan on 07/11/2020.
//

#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <concepts>
#include <tuple>
#include <limits>
#include <cmath>

namespace jnz
{
template<typename T>
concept isNumber =  std::is_integral<T>::value || std::is_floating_point<T>::value;

template<isNumber NumberType>
class LineSegment
{
    using EndPointType = std::tuple<NumberType, NumberType>;
    std::tuple<EndPointType, EndPointType> mEndPoints;
public:
    explicit LineSegment(const std::tuple<EndPointType, EndPointType> &endPoints) : mEndPoints(endPoints)
    {}

    LineSegment(const EndPointType &endPointA, EndPointType &endPointB) : mEndPoints({endPointA, endPointB})
    {}

    LineSegment(const NumberType aX, const NumberType aY, const NumberType bX, const NumberType bY) : mEndPoints({{aX, aY}, {bX, bY}})
    {}

    const std::tuple<EndPointType, EndPointType> &getEndPoints() const
    {
        return mEndPoints;
    }

    void setEndPoints(const std::tuple<EndPointType, EndPointType> &endPoints)
    {
        mEndPoints = endPoints;
    }

    template<std::size_t EndPointIndex>
    const EndPointType &getEndPoint() const
    {
        return std::get<EndPointIndex>(mEndPoints);
    }

    template<std::size_t EndPointIndex>
    EndPointType &getEndPoint()
    {
        return std::get<EndPointIndex>(mEndPoints);
    }

    template<std::size_t EndPointIndex>
    void setEndPoint(const EndPointType &endPoint)
    {
        std::get<EndPointIndex>(mEndPoints) = endPoint;
    }

    constexpr NumberType intersect(const LineSegment<NumberType> &lSegment) const
    {
        auto [a1X, a1Y] = this->getEndPoint<0>();
        auto [a2X, a2Y] = this->getEndPoint<1>();

        auto [b1X, b1Y] = lSegment.getEndPoint<0>();
        auto [b2X, b2Y] = lSegment.getEndPoint<1>();

        NumberType determinant = ((a1X-a2X) * (b1Y-b2Y)) - ((a1Y-a2Y) * (b1X-b2X));
        NumberType u =  -(((a1X - a2X)*(a1Y - b1Y)) - ((a1Y - a2Y)*(a1X - b1X))) / determinant;
        if(std::fabs(determinant) < std::numeric_limits<NumberType>::min() || u < 0.0 || u > 1.0) //if the determinant is zero, then the lines are parallel and don't intersect.
            return std::numeric_limits<NumberType>::max();
        return (((a1X - b1X) * (b1Y - b2Y)) - ((a1Y - b1Y) * (b1X - b2X))) / determinant; //Get the intersection point and return it.
    }

    template <std::floating_point WeightType>
    EndPointType midPoint(const WeightType weight) const
    {
        auto [aX, aY] = this->getEndPoint<0>();
        auto [bX, bY] = this->getEndPoint<1>();
        return {std::lerp(aX, bX, weight), std::lerp(aY, bY, weight)}; //interpolate the mid point
    }

    template<std::size_t EndPointIndex, typename PointType = NumberType>
    constexpr NumberType getDistanceToEndPoint(const std::tuple<PointType, PointType> &point) const
    {
        auto [a1X, a1Y] = this->getEndPoint<EndPointIndex>();
        auto [pX, pY] = point;

        return std::fabs(std::sqrt(((pX - a1X) * (pX - a1X)) + ((pY - a1Y) * (pY - a1Y)))); //simple distance formula
    }

    constexpr NumberType getLineLength() const
    {
        return getDistanceToEndPoint<0>(this->getEndPoint<1>());
    }

    template <typename PointType>
    constexpr std::tuple<NumberType, size_t> getShortestDistanceToEndPoint(const std::tuple<PointType, PointType> &point) const
    {
        auto distanceToA = this->getDistanceToEndPoint<0>(point);
        auto distanceToB = this->getDistanceToEndPoint<1>(point);
        if(distanceToA <= distanceToB)
            return {distanceToA, 0};
        return {distanceToB, 1};
    }
};
}

#endif //LINESEGMENT_H
