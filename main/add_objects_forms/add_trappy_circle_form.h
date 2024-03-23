#pragma once
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
  void AddTrappyCircle(double x, double y, double radius, QColor color);

 private slots:

  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();

 private:
  Ui::AddTrappyCircleForm *ui;
};
