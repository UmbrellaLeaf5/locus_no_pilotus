#pragma once

#include <QDialog>

namespace Ui {
class AddTargetForm;
}

class AddTargetForm : public QDialog {
  Q_OBJECT

 public:
  explicit AddTargetForm(QWidget *parent = nullptr);
  ~AddTargetForm();

 signals:
  void AddTarget(double x, double y);

 private slots:
  void on_clearPushButton_clicked();
  void on_createPushButton_clicked();

 private:
  Ui::AddTargetForm *ui;
};
