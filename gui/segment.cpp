#include "segment.h"

#include <QtMath>

#include "plot_item_arc.h"

namespace gui {

QuarterOfCircle Segment::GetQuarterOfCircle(const lib::Point& p) {
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

double Segment::GetMinAngle(const lib::Point& p, double R,
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

std::pair<double, double> Segment::GetAngles(lib::Point start, lib::Point end,
                                             const lib::Point& center) {
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
