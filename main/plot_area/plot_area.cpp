#include "plot_area.h"

#include "icecream.hpp"

void PlotArea::Redraw() {
  plot_->clearPlottables();
  plot_->clearItems();

  for (size_t i = 0; i < manager_.GetTargets().size(); i++)
    manager_.Draw(gui::ObjectType::Targets, i, plot_.get());

  for (size_t i = 0; i < manager_.GetHills().size(); i++)
    manager_.Draw(gui::ObjectType::Hills, i, plot_.get());

  for (size_t i = 0; i < manager_.GetTrappyCircles().size(); i++)
    manager_.Draw(gui::ObjectType::TrappyCircles, i, plot_.get());

  for (size_t i = 0; i < manager_.GetTrappyLines().size(); i++)
    manager_.Draw(gui::ObjectType::TrappyLines, i, plot_.get());

  UpdateInfo();
  plot_->replot();
}

void PlotArea::UpdateInfo() {
  QString text = "Targets on plot: \n";
  for (size_t i = 0; i < manager_.GetTargets().size(); i++) {
    auto target = manager_.GetTargets()[i];
    text += "• target n." + QString::number(i + 1) + ":\n";
    text +=
        "   plot id: " + QString::number(target.GetPlottableIndex()) + ":\n";
    text += "   x: " + QString::number(target.GetPoint().x) + "\n";
    text += "   y: " + QString::number(target.GetPoint().y) + "\n";
  }

  targets_info_->setText(text);
  targets_info_->setWordWrap(true);

  text = "Hills on plot: \n";
  for (size_t i = 0; i < manager_.GetHills().size(); i++) {
    auto hill = manager_.GetHills()[i];
    text += "• hill n." + QString::number(i + 1) + ":\n";
    text += "   plot id: " + QString::number(hill.GetPlottableIndex()) + ":\n";
    text += "   x: " + QString::number(hill.GetCenter().x) + "\n";
    text += "   y: " + QString::number(hill.GetCenter().y) + "\n";
    text += "   r: " + QString::number(hill.GetRadius()) + "\n";
  }

  hills_info_->setText(text);
  hills_info_->setWordWrap(true);

  text = "Trappy circles on plot: \n";
  for (size_t i = 0; i < manager_.GetTrappyCircles().size(); i++) {
    auto tr_circle = manager_.GetTrappyCircles()[i];
    text += "• trappy c. n." + QString::number(i + 1) + ":\n";
    text += "   plot id: " + QString::number(tr_circle.GetItemIndex()) + ":\n";
    text += "   x: " + QString::number(tr_circle.GetCenter().x) + "\n";
    text += "   y: " + QString::number(tr_circle.GetCenter().y) + "\n";
    text += "   r: " + QString::number(tr_circle.GetRadius()) + "\n";
  }

  tr_circles_info_->setText(text);
  tr_circles_info_->setWordWrap(true);

  text = "Trappy lines on plot: \n";
  for (size_t i = 0; i < manager_.GetTrappyLines().size(); i++) {
    auto tr_line = manager_.GetTrappyLines()[i];
    text += "• trappy l. n." + QString::number(i + 1) + ":\n";
    text +=
        "   plot id: " + QString::number(tr_line.GetPlottableIndex()) + ":\n";
    for (size_t j = 0; j < tr_line.GetTargets().size(); j++) {
      auto target = tr_line.GetTargets()[j];
      text += "   target n." + QString::number(j + 1) + ":\n";
      text += "    x: " + QString::number(target.GetPoint().x) + "\n";
      text += "    y: " + QString::number(target.GetPoint().y) + "\n";
    }
  }

  tr_lines_info_->setText(text);
  tr_lines_info_->setWordWrap(true);
}
