#pragma once

// Qt libs:
#include <QDialog>

namespace Ui {
class AddTrappyCircleForm;
}

class AddTrappyCircleForm : public QDialog {
  Q_OBJECT

 public:
  explicit AddTrappyCircleForm(QWidget *parent = nullptr);
  ~AddTrappyCircleForm();

 signals:
  void AddTrappyCircle(std::string x, std::string y, std::string radius);

 private slots:
  void on_clearPushButton_clicked();
  void on_createPushButton_clicked();

 private:
  Ui::AddTrappyCircleForm *ui;
};
