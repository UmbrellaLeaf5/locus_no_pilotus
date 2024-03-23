#include "add_trappy_line_form.h"

#include "ui_add_trappy_line_form.h"

AddTrappyLineForm::AddTrappyLineForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddTrappyLineForm) {
  ui->setupUi(this);
}

AddTrappyLineForm::~AddTrappyLineForm() { delete ui; }

void AddTrappyLineForm::on_pushButton_clicked() {
  ui->lineEdit->clear();
  ui->lineEdit_2->clear();
  ui->lineEdit_3->clear();
  ui->lineEdit_4->clear();
}

void AddTrappyLineForm::on_pushButton_2_clicked() {
  double x1 = (ui->lineEdit->displayText()).toDouble();
  double y1 = (ui->lineEdit_2->displayText()).toDouble();
  double x2 = (ui->lineEdit_3->displayText()).toDouble();
  double y2 = (ui->lineEdit_4->displayText()).toDouble();
  emit AddTrappyLine(x1, y1, x2, y2);
  close();
}
