#include "add_hill_form.h"

#include <vector>

#include "ui_add_hill_form.h"

AddHillForm::AddHillForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddHillForm) {
  ui->setupUi(this);
}

AddHillForm::~AddHillForm() { delete ui; }

void AddHillForm::on_createPushButton_clicked() {
  auto x = std::vector<double>();
  x.push_back((ui->firstPointAbscissaLineEdit->displayText()).toDouble());
  x.push_back((ui->secondPointAbscissaLineEdit->displayText()).toDouble());
  x.push_back((ui->thirdPointAbscissaLineEdit->displayText()).toDouble());

  auto y = std::vector<double>();
  y.push_back((ui->firstPointOrdinateLineEdit->displayText()).toDouble());
  y.push_back((ui->secondPointOrdinateLineEdit->displayText()).toDouble());
  y.push_back((ui->thirdPointOrdinateLineEdit->displayText()).toDouble());

  emit AddHill(x, y);
  close();
}

void AddHillForm::on_clearPushButton_clicked() {
  ui->firstPointAbscissaLineEdit->clear();
  ui->firstPointOrdinateLineEdit->clear();

  ui->secondPointAbscissaLineEdit->clear();
  ui->secondPointOrdinateLineEdit->clear();

  ui->thirdPointAbscissaLineEdit->clear();
  ui->thirdPointOrdinateLineEdit->clear();
}

void AddHillForm::on_newPushButton_clicked() {}
