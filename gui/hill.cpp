#include "hill.h"

void gui::Hill::Draw(QCustomPlot* plot) const {
  // так как QCustomPlot не позволяет создать замкнутый график, я создаю их
  // вектор, каждый из которых соед. по две точки (ребра многоугольника)
  // (т.е. происходит попарное соед., причем последняя соед. с первой)

  QPen pen;
  pen.setColor(color_);
  pen.setStyle(Qt::SolidLine);

  auto points = data_.GetPoints();
  // кол-во ребер = кол-во точек
  std::vector<QCPGraph*> edges(points.size());

  for (size_t i = 0; i < points.size(); i++) {
    // установка стандартных параметров
    edges[i] = plot->addGraph(plot->xAxis, plot->yAxis);
    edges[i]->setPen(pen);
    edges[i]->setLineStyle(QCPGraph::lsLine);
    edges[i]->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 0));

    // попарное соединение точек
    if (i != points.size() - 1) {
      for (short j = 0; j < 2; j++) {
        edges[i]->addData(points[i + j].x, points[i + j].y);
      }

    } else {
      // в том случае, если пришли в последнюю точку, соед. её с первой
      edges[i]->addData(points[i].x, points[i].y);
      edges[i]->addData(points[0].x, points[0].y);
    }
  }
}
