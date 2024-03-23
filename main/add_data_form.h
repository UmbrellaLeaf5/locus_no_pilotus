#ifndef ADD_DATA_FORM_H
#define ADD_DATA_FORM_H

#include <QDialog>

namespace Ui {
class AddDataForm;
}

class AddDataForm : public QDialog {
  Q_OBJECT

 public:
  explicit AddDataForm(QWidget *parent = nullptr);
  ~AddDataForm();

 signals:
  void AddTrappyCircle(double x, double y, double radius, QColor color);

 private slots:

  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();

 private:
  Ui::AddDataForm *ui;
};

#endif  // ADD_DATA_FORM_H
