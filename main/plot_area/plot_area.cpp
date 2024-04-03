#include "plot_area.h"

void PlotArea::Draw(gui::ObjectType obj_type) {
  if (obj_type == gui::ObjectType::Targets || obj_type == gui::ObjectType::All)
    // FIXME: в этом месте поменять использование Draw на то, что в manager
    for (const auto& target : manager_.GetTargets()) target.Draw(plot_.get());

  if (obj_type == gui::ObjectType::Hills || obj_type == gui::ObjectType::All)
    for (const auto& hill : manager_.GetHills()) hill.Draw(plot_.get());

  if (obj_type == gui::ObjectType::TrappyCircles ||
      obj_type == gui::ObjectType::All)
    for (const auto& tr_circle : manager_.GetTrappyCircles())
      tr_circle.Draw(plot_.get());

  if (obj_type == gui::ObjectType::TrappyLines ||
      obj_type == gui::ObjectType::All)
    for (const auto& tr_line : manager_.GetTrappyLines())
      tr_line.Draw(plot_.get());

  UpdateInfo(obj_type);
  plot_->replot();
}

void PlotArea::UpdateInfo(gui::ObjectType obj_type) {
  if (obj_type == gui::ObjectType::Targets ||
      obj_type == gui::ObjectType::All) {
    QString text = "Targets on plot: \n";
    for (size_t i = 0; i < manager_.GetTargets().size(); i++) {
      auto target = manager_.GetTargets()[i];
      text += "  target n." + QString::number(i + 1) + ":\n";
      text += "    x: " + QString::number(target.GetPoint().x) + "\n";
      text += "    y: " + QString::number(target.GetPoint().y) + "\n";
    }

    targets_info_->setText(text);
    targets_info_->setWordWrap(true);
  }

  if (obj_type == gui::ObjectType::Hills || obj_type == gui::ObjectType::All) {
    QString text = "Hills on plot: \n";
    for (size_t i = 0; i < manager_.GetHills().size(); i++) {
      auto hill = manager_.GetHills()[i];
      text += "  hill n." + QString::number(i + 1) + ":\n";
      text += "    x: " + QString::number(hill.GetCenter().x) + "\n";
      text += "    y: " + QString::number(hill.GetCenter().y) + "\n";
      text += "    r: " + QString::number(hill.GetRadius()) + "\n";
    }

    hills_info_->setText(text);
    hills_info_->setWordWrap(true);
  }

  if (obj_type == gui::ObjectType::TrappyCircles ||
      obj_type == gui::ObjectType::All) {
    QString text = "Trappy circles on plot: \n";
    for (size_t i = 0; i < manager_.GetTrappyCircles().size(); i++) {
      auto tr_circle = manager_.GetTrappyCircles()[i];
      text += "  trappy c. n." + QString::number(i + 1) + ":\n";
      text += "    x: " + QString::number(tr_circle.GetCenter().x) + "\n";
      text += "    y: " + QString::number(tr_circle.GetCenter().y) + "\n";
      text += "    r: " + QString::number(tr_circle.GetRadius()) + "\n";
    }

    tr_circles_info_->setText(text);
    tr_circles_info_->setWordWrap(true);
  }

  if (obj_type == gui::ObjectType::TrappyLines ||
      obj_type == gui::ObjectType::All) {
    QString text = "Trappy lines on plot: \n";
    for (size_t i = 0; i < manager_.GetTrappyLines().size(); i++) {
      auto tr_line = manager_.GetTrappyLines()[i];
      text += "  trappy l. n." + QString::number(i + 1) + ":\n";
      for (size_t j = 0; j < tr_line.GetTargets().size(); j++) {
        auto target = tr_line.GetTargets()[j];
        text += "   target n." + QString::number(j + 1) + ":\n";
        text += "     x: " + QString::number(target.GetPoint().x) + "\n";
        text += "     y: " + QString::number(target.GetPoint().y) + "\n";
      }
    }

    tr_lines_info_->setText(text);
    tr_lines_info_->setWordWrap(true);
  }
}
