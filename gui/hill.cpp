#include "hill.h"

void gui::Hill::Draw(QCustomPlot* plot) const {
  // оказалось, что существует класс представляющий собой
  // кривой замкнутой линии в QCustomPlot

  auto curve = new QCPCurve(plot->xAxis, plot->yAxis);

  QPen pen;
  pen.setColor(color_);
  pen.setStyle(Qt::SolidLine);
  curve->setPen(pen);

  curve->setLineStyle(QCPCurve::lsLine);

  auto points = data_.GetPoints();

  for (int i = 0; i < points.size(); i++) {
    curve->addData({points[i].x}, {points[i].y});
  }

  // замыкаем, соединяя с первой точкой
  curve->addData({points[0].x}, {points[0].y});
}
