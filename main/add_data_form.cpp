#include "add_data_form.h"

#include "qcustomplot.h"
#include "ui_add_data_form.h"

AddDataForm::AddDataForm(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddDataForm) {
  ui->setupUi(this);
}

AddDataForm::~AddDataForm() { delete ui; }

void AddDataForm::on_pushButton_3_clicked() {
  double x = (ui->lineEdit->displayText()).toDouble();
  double y = (ui->lineEdit_2->displayText()).toDouble();
  double radius = (ui->lineEdit_3->displayText()).toDouble();
  QColor color = QColor(ui->lineEdit_4->displayText());
  emit AddTrappyCircle(x, y, radius, color);
  close();
}

void AddDataForm::on_pushButton_clicked() {
  ui->lineEdit->clear();
  ui->lineEdit_2->clear();
  ui->lineEdit_3->clear();
  ui->lineEdit_4->clear();
}

void AddDataForm::on_pushButton_2_clicked() {
  QColorDialog* qcd = new QColorDialog;
  qcd->setModal(true);
  ui->lineEdit_4->setText(qcd->getColor().name());
}
