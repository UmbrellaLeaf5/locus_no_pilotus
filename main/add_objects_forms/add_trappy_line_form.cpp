// header file:
#include "add_trappy_line_form.h"

// autogen libs:
#include "./ui_add_trappy_line_form.h"

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
  std::string x1 = ui->firstPointAbscissaLineEdit->displayText().toStdString();
  std::string y1 = ui->firstPointOrdinateLineEdit->displayText().toStdString();
  std::string x2 = ui->secondPointAbscissaLineEdit->displayText().toStdString();
  std::string y2 = ui->secondPointOrdinateLineEdit->displayText().toStdString();

  emit AddTrappyLine(x1, y1, x2, y2);
  close();
}
