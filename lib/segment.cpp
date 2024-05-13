// header file:
#include "segment.h"

// std libs:
#include <algorithm>
#include <array>
#include <stdexcept>
#include <utility>

namespace lib {

Segment::Segment(const Point& start, const Point& end, const Point& center)
    : start_{start}, end_{end}, center_{center} {
  if (std::abs(DistanceBetweenPoints(start, center) -
               DistanceBetweenPoints(end, center)) > lib::precision)
    throw std::runtime_error(
        "dev: start and end in Segment do not lie on the same circle");
}

Point& Segment::Center() {
  if (IsArc()) return center_;

  throw std::runtime_error("dev: Segment is not Arc");
}

const Point& Segment::Center() const {
  if (IsArc()) return center_;

  throw std::runtime_error("dev: Segment is not Arc");
}

double Segment::Radius() const {
  if (IsArc()) return DistanceBetweenPoints(start_, center_);

  throw std::runtime_error("dev: Segment is not Arc");
}

std::pair<double, double> Segment::ToAnglesOnCircle() {
  auto start_angles = lib::PointAsAngles::FromPoint(Start(), Center());
  auto end_angles = lib::PointAsAngles::FromPoint(End(), Center());

  auto angle_pairs = std::array{
      std::make_pair(start_angles.positive_angle, end_angles.positive_angle),
      std::make_pair(start_angles.positive_angle, end_angles.negative_angle),
      std::make_pair(start_angles.negative_angle, end_angles.positive_angle),
      std::make_pair(start_angles.negative_angle, end_angles.negative_angle)};

  return *std::min_element(angle_pairs.begin(), angle_pairs.end(),
                           [](const auto& pair_1, const auto& pair_2) {
                             return std::abs(pair_1.first - pair_1.second) <
                                    std::abs(pair_2.first - pair_2.second);
                           });
}

bool Segment::CouldBeArc(const lib::Segment& seg, const lib::Point& center) {
  try {
    lib::Segment(seg.Start(), seg.End(), center);
  } catch (const std::runtime_error&) {
    return false;
  }
  return true;
}

}  // namespace lib
