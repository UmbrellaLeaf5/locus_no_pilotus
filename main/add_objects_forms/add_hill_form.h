#pragma once
#include <QDialog>

namespace Ui {
class AddHillForm;
}

class AddHillForm : public QDialog {
  Q_OBJECT

 public:
  explicit AddHillForm(QWidget *parent = nullptr);
  ~AddHillForm();

 signals:
  void AddHill();

 private:
  Ui::AddHillForm *ui;
};
