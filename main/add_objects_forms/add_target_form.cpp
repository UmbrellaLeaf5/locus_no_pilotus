#include "add_target_form.h"

#include "ui_add_target_form.h"

AddTargetForm::AddTargetForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddTargetForm) {
  ui->setupUi(this);
}

AddTargetForm::~AddTargetForm() { delete ui; }

void AddTargetForm::on_pushButton_clicked() {
  ui->lineEdit->clear();
  ui->lineEdit_2->clear();
}

void AddTargetForm::on_pushButton_2_clicked() {
  double x = (ui->lineEdit->displayText()).toDouble();
  double y = (ui->lineEdit_2->displayText()).toDouble();
  emit AddTarget(x, y);
  close();
}
