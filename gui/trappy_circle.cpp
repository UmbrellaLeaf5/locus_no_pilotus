#include "trappy_circle.h"

#include "plot_item_arc.h"

static void SetCenterAndRadiusCoords(QCPItemEllipse*& ellipse,
                                     lib::Point center, double rad) {
  ellipse->topLeft->setCoords(center.x - rad, center.y + rad);
  ellipse->bottomRight->setCoords(center.x + rad, center.y - rad);
}

void gui::TrappyCircle::Draw(QCustomPlot* plot) {
  ellipse_ = new QCPItemEllipse(plot);

  QColor fill_color = QColor(color_.red(), color_.green(), color_.blue(), 100);

  ellipse_->setPen(QColor(color_));
  ellipse_->setBrush(fill_color);
  SetCenterAndRadiusCoords(ellipse_, GetCenter(), GetRadius());
}
