#include "hill.h"

void gui::Hill::Draw(QCustomPlot* plot) {
  // фигура представляет собой зеленый многоугольник с полупрозрачной заливкой
  // (зеленый по умолчанию, однако цвет задаётся в аргументах конструктора)

  curve_ = new QCPCurve(plot->xAxis, plot->yAxis);

  QColor fill_color = QColor(color_.red(), color_.green(), color_.blue(), 100);

  QPen pen;
  pen.setColor(color_);
  pen.setStyle(Qt::SolidLine);
  curve_->setPen(pen);
  curve_->setBrush(fill_color);

  curve_->setLineStyle(QCPCurve::lsLine);

  auto points = data_.GetPoints();

  for (size_t i = 0; i < points.size(); i++) {
    curve_->addData(points[i].x, points[i].y);
  }

  // замыкаем, соединяя с первой точкой
  curve_->addData(points[0].x, points[0].y);
}
