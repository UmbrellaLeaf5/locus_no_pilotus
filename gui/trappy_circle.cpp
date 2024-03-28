#include "trappy_circle.h"

#include "qcustomplot.h"

void gui::TrappyCircle::Draw(QCustomPlot* plot) const {
  // фигура представляет собой красный круг с полупрозрачной заливкой

  // QPen pen;
  // pen.setColor(color_);

  QColor fill_color = QColor(color_.red(), color_.green(), color_.blue(), 100);

  QCPItemEllipse* ellipse = new QCPItemEllipse(plot);
  ellipse->setPen(QColor(color_));
  ellipse->setBrush(fill_color);
  ellipse->topLeft->setCoords(GetCenter().x - GetRadius(),
                              GetCenter().y + GetRadius());
  ellipse->bottomRight->setCoords(GetCenter().x + GetRadius(),
                                  GetCenter().y - GetRadius());
}
