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
  void on_clearPushButton_clicked();
  void on_createPushButton_clicked();
  void on_colorSelectPushButton_clicked();

 private:
  Ui::AddTrappyCircleForm *ui;
};
