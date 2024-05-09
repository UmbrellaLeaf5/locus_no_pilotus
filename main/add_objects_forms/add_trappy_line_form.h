#pragma once

// Qt libs:
#include <QDialog>

namespace Ui {
class AddTrappyLineForm;
}

class AddTrappyLineForm : public QDialog {
  Q_OBJECT

 public:
  explicit AddTrappyLineForm(QWidget *parent = nullptr);
  ~AddTrappyLineForm();

 signals:
  void AddTrappyLine(std::string x1, std::string y1, std::string x2,
                     std::string y2);

 private slots:
  void on_clearPushButton_clicked();
  void on_createPushButton_clicked();

 private:
  Ui::AddTrappyLineForm *ui;
};
