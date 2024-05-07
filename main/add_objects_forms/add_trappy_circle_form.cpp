#include "add_trappy_circle_form.h"

#include "ui_add_trappy_circle_form.h"

AddTrappyCircleForm::AddTrappyCircleForm(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddTrappyCircleForm) {
  ui->setupUi(this);
  QDoubleValidator* double_validator{new QDoubleValidator()};
  ui->abscissaLineEdit->setValidator(double_validator);
  ui->ordinateLineEdit->setValidator(double_validator);
  ui->radiusLineEdit->setValidator(double_validator);
}

AddTrappyCircleForm::~AddTrappyCircleForm() { delete ui; }

void AddTrappyCircleForm::on_clearPushButton_clicked() {
  ui->abscissaLineEdit->clear();
  ui->ordinateLineEdit->clear();
  ui->radiusLineEdit->clear();
}

void AddTrappyCircleForm::on_createPushButton_clicked() {
  QString x = ui->abscissaLineEdit->displayText().replace(',', '.');
  QString y = ui->ordinateLineEdit->displayText().replace(',', '.');
  QString radius = ui->radiusLineEdit->displayText().replace(',', '.');
  if (x.isEmpty() || y.isEmpty() || radius.isEmpty())
    QMessageBox::warning(
        this, "Warning!",
        "There are empty fields! Please, enter values in all fields.");
  else {
    emit AddTrappyCircle(x.toDouble(), y.toDouble(), radius.toDouble());
    close();
  }
}
