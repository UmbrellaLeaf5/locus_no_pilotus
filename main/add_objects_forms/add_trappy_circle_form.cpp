// header file:
#include "add_trappy_circle_form.h"

// autogen libs:
#include "./ui_add_trappy_circle_form.h"

AddTrappyCircleForm::AddTrappyCircleForm(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddTrappyCircleForm) {
  ui->setupUi(this);
}

AddTrappyCircleForm::~AddTrappyCircleForm() { delete ui; }

void AddTrappyCircleForm::on_clearPushButton_clicked() {
  ui->abscissaLineEdit->clear();
  ui->ordinateLineEdit->clear();
  ui->radiusLineEdit->clear();
}

void AddTrappyCircleForm::on_createPushButton_clicked() {
  std::string x = ui->abscissaLineEdit->displayText().toStdString();
  std::string y = ui->ordinateLineEdit->displayText().toStdString();
  std::string radius = ui->radiusLineEdit->displayText().toStdString();

  emit AddTrappyCircle(x, y, radius);
  close();
}
