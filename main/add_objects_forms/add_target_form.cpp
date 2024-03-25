#include "add_target_form.h"

#include "ui_add_target_form.h"

AddTargetForm::AddTargetForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddTargetForm) {
  ui->setupUi(this);
}

AddTargetForm::~AddTargetForm() { delete ui; }

void AddTargetForm::on_clearPushButton_clicked() {
  ui->abscissaLineEdit->clear();
  ui->ordinateLineEdit->clear();
}

void AddTargetForm::on_createPushButton_clicked() {
  double x = (ui->abscissaLineEdit->displayText()).toDouble();
  double y = (ui->ordinateLineEdit->displayText()).toDouble();
  emit AddTarget(x, y);
  close();
}
