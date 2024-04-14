#pragma once

#include "data_tools/plot_area/plot_area.h"

class GuiJsonFile {
 public:
  GuiJsonFile() = default;
  GuiJsonFile(QFile* file) : file_{file} {};

  void Save(data_tools::DataManager* plot_area);
  void Open(data_tools::DataManager* plot_area);

  QString GetFileName() const;
  QString GetUntitledFile() const { return untitled_file_; }

  void SetFile(const QString& file_name) { file_->setFileName(file_name); }
  void ChangeUntitled(const QString& old_untitled);
  void Clear() { file_->setFileName(""); }

  bool IsExistsFile() const {
    return (file_->fileName().size() != 0 && file_->exists());
  }

  bool IsChanged(data_tools::DataManager* plot_area) const;

 private:
  QFile* file_{new QFile};
  QString untitled_file_ = "Untitled.json";

  QJsonObject LoadJson() const;
};
