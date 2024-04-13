#pragma once

#include "../../data_tools/plot_area/plot_area.h"

class GuiJsonFile {
 public:
  GuiJsonFile() = default;
  GuiJsonFile(QFile* file) : file_{file} {};

  void Save(data_tools::PlotArea& plot_area);
  void New();
  void Open(data_tools::PlotArea& plot_area);

  QString GetFileName();
  QString GetUntitledFile() { return untitled_file_; }

  void SetFile(QString file_name) { file_->setFileName(file_name); }
  void ChangeUntitled(QString old_untitled);
  void Clear() { file_->setFileName(""); }

  bool IsExistsFile() {
    return (file_->fileName().size() != 0 && file_->exists());
  }
  bool IsChanged(data_tools::PlotArea& plot_area);

 private:
  QFile* file_{new QFile};
  QString untitled_file_ = "Untitled.json";

  QJsonObject LoadJson();
};
