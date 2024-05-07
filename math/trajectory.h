#pragma once

#include <lib/hill.h>
#include <lib/target.h>
#include <lib/trappy_circle.h>
#include <lib/trappy_line.h>
#include <math/littles_algorithm/travelling_salesmans_problem.h>
#include <math/optimal_way/optimal_way.h>

using lib::Hill;
using lib::Target;
using lib::TrappyCircle;
using lib::TrappyLine;

namespace math {

class TrajectoryCalculator {
 public:
  TrajectoryCalculator();
};

}  // namespace math
