#include "add_trappy_line_form.h"

#include "ui_add_trappy_line_form.h"

AddTrappyLineForm::AddTrappyLineForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddTrappyLineForm) {
  ui->setupUi(this);
}

AddTrappyLineForm::~AddTrappyLineForm() { delete ui; }

void AddTrappyLineForm::on_clearPushButton_clicked() {
  ui->firstPointAbscissaLineEdit->clear();
  ui->firstPointOrdinateLineEdit->clear();
  ui->secondPointAbscissaLineEdit->clear();
  ui->secondPointOrdinateLineEdit->clear();
}

void AddTrappyLineForm::on_createPushButton_clicked() {
  double x1 = (ui->firstPointAbscissaLineEdit->displayText()).toDouble();
  double y1 = (ui->firstPointOrdinateLineEdit->displayText()).toDouble();
  double x2 = (ui->secondPointAbscissaLineEdit->displayText()).toDouble();
  double y2 = (ui->secondPointOrdinateLineEdit->displayText()).toDouble();
  emit AddTrappyLine(x1, y1, x2, y2);
  close();
}
