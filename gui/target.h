#pragma once

// our code libs:
#include "base.h"
#include "lib/target.h"

namespace gui {

/**
 * @brief Фигура контрольной точки
 * @details Фигура представляет собой малую серую окружность (точку)
 */
class Target : public Drawable {
 public:
  Target() = default;

  Target(double x, double y) : data_(x, y) {}
  Target(lib::Point p) : data_(p) {}
  Target(const lib::Target& data) : data_(data) {}

  Target(const Target&) = default;
  Target(Target&&) = default;

  Target& operator=(const Target&) = default;
  Target& operator=(Target&&) = default;

  void SetPoint(lib::Point p) { data_.SetPoint(p); }
  void SetPoint(double x, double y) { data_.SetPoint(x, y); }

  lib::Point GetPoint() const { return data_.GetPoint(); }
  lib::Target& GetData() { return data_; }
  const lib::Target& GetData() const { return data_; }

  /**
   * @brief Отрисовывает фигуру на полотне
   * @details Фигура представляет собой малую серую окружность (точку)
   * @param plot: указатель на полотно
   */
  virtual void Draw(QCustomPlot* plot) override;

  /**
   * @brief Возвращает значение указателя на полотне
   * @return QCPGraph*: указатель
   */
  QCPGraph* GetGraphPtr() const { return graph_; }

  bool operator==(const gui::Target& target) const {
    return data_ == target.GetData();
  }

 private:
  lib::Target data_;

  QCPGraph* graph_{nullptr};
};

inline void Target::Draw(QCustomPlot* plot) {
  graph_ = plot->addGraph(plot->xAxis, plot->yAxis);

  graph_->setPen(QColor(50, 50, 50, 255));
  graph_->setLineStyle(QCPGraph::lsNone);
  graph_->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

  graph_->setData({GetPoint().x}, {GetPoint().y});
}

}  // namespace gui
