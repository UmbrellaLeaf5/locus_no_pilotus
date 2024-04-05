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
  void AddHill(std::vector<double> x, std::vector<double> y);

 private slots:
  void on_createPushButton_clicked();
  void on_clearPushButton_clicked();
  void on_newPushButton_clicked();

 private:
  Ui::AddHillForm *ui;
};
