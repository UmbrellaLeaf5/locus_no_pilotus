#ifndef ADD_TARGET_FORM_H
#define ADD_TARGET_FORM_H

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
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

 private:
  Ui::AddTargetForm *ui;
};

#endif  // ADD_TARGET_FORM_H