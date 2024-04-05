#pragma once

#include "./plot_area/plot_area.h"

class GuiJsonFile {
 public:
  GuiJsonFile() = default;
  GuiJsonFile(QFile* file) : file_{file} {};

  void Save(PlotArea& plot_area);
  void New();
  void Open(PlotArea& plot_area);

  void SetFile(QString file_name) { file_->setFileName(file_name); }

  bool IsExistsFile() { return file_->fileName().size() != 0; }
  bool IsChanged(PlotArea& plot_area);

 private:
  QFile* file_{new QFile};
  QJsonDocument* json_file_{new QJsonDocument};

  void WriteFile(std::vector<QJsonArray> arr);
};
