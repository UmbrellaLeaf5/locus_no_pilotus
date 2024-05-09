#pragma once

// Qt libs:
#include <QDialog>
#include <QDoubleValidator>
#include <QMessageBox>

namespace Ui {
class AddTrappyLineForm;
}

class AddTrappyLineForm : public QDialog {
  Q_OBJECT

 public:
  explicit AddTrappyLineForm(QWidget *parent = nullptr);
  ~AddTrappyLineForm();

 signals:
  void AddTrappyLine(double x1, double y1, double x2, double y2);

 private slots:
  void on_clearPushButton_clicked();
  void on_createPushButton_clicked();

 private:
  Ui::AddTrappyLineForm *ui;
};
