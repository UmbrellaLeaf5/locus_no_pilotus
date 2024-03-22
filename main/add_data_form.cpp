#include "add_data_form.h"

#include "ui_add_data_form.h"

AddDataForm::AddDataForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddDataForm) {
  ui->setupUi(this);
}

AddDataForm::~AddDataForm() { delete ui; }

void AddDataForm::on_pushButton_3_clicked() {
  double x = (ui->lineEdit->displayText()).toDouble();
  double y = (ui->lineEdit_2->displayText()).toDouble();
  double radius = (ui->lineEdit_3->displayText()).toDouble();
  emit AddTrappyCircle(x, y, radius);
  close();
}
