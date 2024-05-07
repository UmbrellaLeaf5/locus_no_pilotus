#include "add_trappy_line_form.h"

#include "ui_add_trappy_line_form.h"

AddTrappyLineForm::AddTrappyLineForm(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddTrappyLineForm) {
  ui->setupUi(this);
  QDoubleValidator* double_validator{new QDoubleValidator()};
  ui->firstPointAbscissaLineEdit->setValidator(double_validator);
  ui->firstPointOrdinateLineEdit->setValidator(double_validator);
  ui->secondPointAbscissaLineEdit->setValidator(double_validator);
  ui->secondPointOrdinateLineEdit->setValidator(double_validator);
}

AddTrappyLineForm::~AddTrappyLineForm() { delete ui; }

void AddTrappyLineForm::on_clearPushButton_clicked() {
  ui->firstPointAbscissaLineEdit->clear();
  ui->firstPointOrdinateLineEdit->clear();
  ui->secondPointAbscissaLineEdit->clear();
  ui->secondPointOrdinateLineEdit->clear();
}

void AddTrappyLineForm::on_createPushButton_clicked() {
  QString x1 = ui->firstPointAbscissaLineEdit->displayText().replace(',', '.');
  QString y1 = ui->firstPointOrdinateLineEdit->displayText().replace(',', '.');
  QString x2 = ui->secondPointAbscissaLineEdit->displayText().replace(',', '.');
  QString y2 = ui->secondPointOrdinateLineEdit->displayText().replace(',', '.');
  if (x1.isEmpty() || y1.isEmpty() || x2.isEmpty() || y2.isEmpty())
    QMessageBox::warning(
        this, "Warning!",
        "There are empty fields! Please, enter values in all fields.");
  else {
    emit AddTrappyLine(x1.toDouble(), y1.toDouble(), x2.toDouble(),
                       y2.toDouble());
    close();
  }
}
