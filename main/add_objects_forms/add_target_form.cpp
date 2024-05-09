// header file:
#include "add_target_form.h"

// autogen libs:
#include "./ui_add_target_form.h"

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
  std::string x = ui->abscissaLineEdit->displayText().toStdString();
  std::string y = ui->ordinateLineEdit->displayText().toStdString();
  emit AddTarget(x, y);
  close();
}
