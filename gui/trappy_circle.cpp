#include "trappy_circle.h"

void gui::TrappyCircle::Draw(QCustomPlot* plot) {
  // фигура представляет собой красный круг с полупрозрачной заливкой
  // (красный по умолчанию, однако цвет задаётся в аргументах конструктора)

  auto ellipse = new QCPItemEllipse(plot);

  QColor fill_color = QColor(color_.red(), color_.green(), color_.blue(), 100);

  ellipse->setPen(QColor(color_));
  ellipse->setBrush(fill_color);
  ellipse->topLeft->setCoords(GetCenter().x - GetRadius(),
                              GetCenter().y + GetRadius());
  ellipse->bottomRight->setCoords(GetCenter().x + GetRadius(),
                                  GetCenter().y - GetRadius());

  // индекс последнего созданного = кол-во всех - 1
  item_index_ = plot->itemCount() - 1;
}
