// header file:
#include "add_target_form.h"

// autogen libs:
#include "./ui_add_target_form.h"

AddTargetForm::AddTargetForm(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddTargetForm) {
  ui->setupUi(this);
  QDoubleValidator* double_validator{new QDoubleValidator()};
  ui->abscissaLineEdit->setValidator(double_validator);
  ui->ordinateLineEdit->setValidator(double_validator);
}

AddTargetForm::~AddTargetForm() { delete ui; }

void AddTargetForm::on_clearPushButton_clicked() {
  ui->abscissaLineEdit->clear();
  ui->ordinateLineEdit->clear();
}

void AddTargetForm::on_createPushButton_clicked() {
  QString x = ui->abscissaLineEdit->displayText().replace(',', '.');
  QString y = ui->ordinateLineEdit->displayText().replace(',', '.');
  if (x.isEmpty() || y.isEmpty())
    QMessageBox::warning(
        this, "Warning!",
        "There are empty fields! Please, enter values in all fields.");
  else {
    emit AddTarget(x.toDouble(), y.toDouble());
    close();
  }
}
