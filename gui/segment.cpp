#include "segment.h"

#include <QtMath>

namespace gui {

enum class QuarterOfCircle { First, Second, Third, Fourth };

static QuarterOfCircle GetQuarterOfCircle(lib::Point p) {
  double x = p.x, y = p.y;
  if (x >= 0 && y >= 0)
    return QuarterOfCircle::First;
  else if (x < 0 && y >= 0)
    return QuarterOfCircle::Second;
  else if (x <= 0 && y < 0)
    return QuarterOfCircle::Third;
  else if (x > 0 && y < 0)
    return QuarterOfCircle::Fourth;

  // Impossible case
  return QuarterOfCircle::First;
}

static double GetMinAngle(lib::Point p, double R, QuarterOfCircle quarter) {
  double angle{lib::inf};
  char sign{CHAR_MAX};

  switch (quarter) {
    case QuarterOfCircle::First: {
      angle = 0;
      sign = 1;
      break;
    }
    case QuarterOfCircle::Second: {
      angle = 180;
      sign = -1;
      break;
    }
    case QuarterOfCircle::Third: {
      angle = 180;
      sign = 1;
      break;
    }
    case QuarterOfCircle::Fourth: {
      angle = 360;
      sign = -1;
      break;
    }
  }

  // Считаем угол между осью OX и радиусом, проходящим через нашу точку и
  // суммируем с angle, с учетом знака
  double sinus = qAsin(abs(p.y) / R) * 180 / M_PI;
  angle += sign * sinus;

  if (abs(angle - 360) < angle) return angle - 360;
  return angle;
}

static std::pair<double, double> GetAngles(lib::Point start, lib::Point end,
                                           lib::Point center) {
  // Считаем радиус окружности
  double R = sqrt(pow(start.x - center.x, 2) + pow(start.y - center.y, 2));

  // Чтобы легче считать, переносим окружность в начало координат
  start -= center;
  end -= center;

  // Находим, в какие четвертях находятся точки
  QuarterOfCircle start_quarter = GetQuarterOfCircle(start);
  QuarterOfCircle end_quarter = GetQuarterOfCircle(end);

  // Находим минимальный по модулю угол у каждой точки
  double min_start_angle = GetMinAngle(start, R, start_quarter);
  double min_end_angle = GetMinAngle(end, R, end_quarter);

  return {min_start_angle, min_end_angle};
}

void Segment::Draw(QCustomPlot* plot) {
  if (IsArc()) {
  } else {
  }
}

}  // namespace gui
