#include "segment.h"

#include <QtMath>

namespace lib {
enum class QuarterOfСircle { First, Second, Third, Fourth };

static QuarterOfСircle GetQuarterOfСircle(lib::Point p) {
  double x = p.x, y = p.y;
  if (x >= 0 && y >= 0)
    return QuarterOfСircle::First;
  else if (x < 0 && y >= 0)
    return QuarterOfСircle::Second;
  else if (x <= 0 && y < 0)
    return QuarterOfСircle::Third;
  else if (x > 0 && y < 0)
    return QuarterOfСircle::Fourth;

  // Impossible case
  return QuarterOfСircle::First;
}

static double GetMinAngle(lib::Point p, double R, QuarterOfСircle quarter) {
  double angle{lib::inf};
  char sign{CHAR_MAX};

  switch (quarter) {
    case QuarterOfСircle::First: {
      angle = 0;
      sign = 1;
      break;
    }
    case QuarterOfСircle::Second: {
      angle = 180;
      sign = -1;
      break;
    }
    case QuarterOfСircle::Third: {
      angle = 180;
      sign = 1;
      break;
    }
    case QuarterOfСircle::Fourth: {
      angle = 360;
      sign = -1;
      break;
    }
  }

  // Считаем угол между осью OX и радиусом, проходящим через нашу точку и
  // суммируем с angle, с учетом знака
  double sinus = qAsin(abs(p.y) / R) * 180 / M_PI;
  angle += sign * sinus;

  if (abs(-360 + angle) < angle) return -360 + angle;
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
  QuarterOfСircle start_quarter = GetQuarterOfСircle(start);
  QuarterOfСircle end_quarter = GetQuarterOfСircle(end);

  // Находим минимальный по модулю угол у каждой точки
  double min_start_angle = GetMinAngle(start, R, start_quarter);
  double min_end_angle = GetMinAngle(end, R, end_quarter);

  return {min_start_angle, min_end_angle};
}
}  // namespace lib
