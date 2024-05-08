#pragma once

#include "base.h"
#include "lib/segment.h"
#include "plot_item_arc.h"

enum class QuarterOfCircle { First, Second, Third, Fourth };

namespace gui {

/**
 * @brief Фигура отрезка траектории
 * @details Фигура представляет собой отрезок или дугу окружности синего цвета
 */
class Segment : private Drawable {
 public:
  Segment() = default;

  Segment(const lib::Point& start, const lib::Point& end) : data_(start, end) {}

  Segment(const lib::Point& start, const lib::Point& end,
          const lib::Point& center)
      : data_(start, end, center) {}

  double Radius() { return data_.Radius(); }

  /// @brief Возвращает начало сегмента
  lib::Point& Start() { return data_.Start(); }

  /// @brief Возвращает конец сегмента
  lib::Point& End() { return data_.End(); }

  /**
   * @brief Возвращает центр окружности
   * @return Point&: центр окружности
   */
  lib::Point& Center() { return data_.Center(); }

  /**
   * @brief Проверяет, является ли текущий сегмент дугой окружности
   * @return true: да, является
   * @return false: нет, не является
   */
  bool IsArc() { return data_.IsArc(); }

  /**
   * @brief Возвращает угловые коэффициенты на окружности
   * @param start: точка старта
   * @param end: конечная точка
   * @param center: центр окружности
   * @return std::pair<double, double>: угол первой точки, угол второй точки
   */
  static std::pair<double, double> GetAngles(lib::Point start, lib::Point end,
                                             const lib::Point& center);

  /**
   * @brief Отрисовывает фигуру на полотне
   * @details Фигура представляет собой отрезок или дугу окружности синего цвета
   * @param plot: указатель на полотно
   */
  void Draw(QCustomPlot* plot) override;

 private:
  lib::Segment data_;

  QColor color_{QColor(50, 100, 200, 255)};

  static QuarterOfCircle GetQuarterOfCircle(const lib::Point& p);
  static double GetMinAngle(const lib::Point& p, double R,
                            QuarterOfCircle quarter);
};

inline std::pair<double, double> Segment::GetAngles(lib::Point start,
                                                    lib::Point end,
                                                    const lib::Point& center) {
  // Считаем радиус окружности
  double R = lib::Segment::DistanceBetweenPoints(start, center);

  // Чтобы легче считать, переносим окружность в начало координат
  start -= center;
  end -= center;

  return {GetMinAngle(start, R, GetQuarterOfCircle(start)),
          GetMinAngle(end, R, GetQuarterOfCircle(end))};
}

inline QuarterOfCircle Segment::GetQuarterOfCircle(const lib::Point& p) {
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

inline double Segment::GetMinAngle(const lib::Point& p, double R,
                                   QuarterOfCircle quarter) {
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

inline void Segment::Draw(QCustomPlot* plot) {
  if (IsArc()) {
    auto arc = new PlotItemArc(plot);

    arc->SetPen(QColor(color_));
    arc->SetCenterAndRadiusCoords(Center().x, Center().y, Radius());
    arc->SetStartAndEnd(GetAngles(Start(), End(), Center()));

  } else {
    auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

    graph->setPen(QColor(color_));
    graph->setLineStyle(QCPGraph::lsLine);
    graph->setSelectable(QCP::stNone);

    graph->addData(Start().x, Start().y);
    graph->addData(End().x, End().y);
  }
}

}  // namespace gui
