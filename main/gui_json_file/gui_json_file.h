#pragma once

#include "./plot_area/plot_area.h"

class GuiJsonFile {
 public:
  GuiJsonFile() = default;
  GuiJsonFile(QFile* file) : file_{file} {};

  void Save(PlotArea& plot_area);
  void New();
  void Open(PlotArea& plot_area);

  QString GetFileName() { return file_->fileName(); }
  QString GetUntitledFile() { return untitled_file; }

  void SetFile(QString file_name) { file_->setFileName(file_name); }
  void ChangeUntitled(QString old_untitled);

  bool IsExistsFile() {
    return (file_->fileName().size() != 0 && file_->exists());
  }
  bool IsChanged(PlotArea& plot_area);

 private:
  QFile* file_{new QFile};
  QString untitled_file = "Untitled";

  QJsonObject LoadJson();
};
