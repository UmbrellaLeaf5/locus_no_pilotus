#include "trappy_circle.h"

void gui::TrappyCircle::Draw(QCustomPlot* plot) {
  // фигура представляет собой красный круг с полупрозрачной заливкой
  // (красный по умолчанию, однако цвет задаётся в аргументах конструктора)

  ellipse_ = new QCPItemEllipse(plot);

  QColor fill_color = QColor(color_.red(), color_.green(), color_.blue(), 100);

  ellipse_->setPen(QColor(color_));
  ellipse_->setBrush(fill_color);
  ellipse_->topLeft->setCoords(GetCenter().x - GetRadius(),
                               GetCenter().y + GetRadius());
  ellipse_->bottomRight->setCoords(GetCenter().x + GetRadius(),
                                   GetCenter().y - GetRadius());

  // SetPlottableIndex(plot); невозможно использовать, так как
  // ellipse это item, а не plottable

  // индекс последнего созданного = кол-во всех - 1
  item_index_ = plot->itemCount() - 1;
}
