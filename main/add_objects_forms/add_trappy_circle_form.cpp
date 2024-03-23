#include "add_trappy_circle_form.h"

#include <QColorDialog>

#include "ui_add_trappy_circle_form.h"

AddTrappyCircleForm::AddTrappyCircleForm(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddTrappyCircleForm) {
  ui->setupUi(this);
}

AddTrappyCircleForm::~AddTrappyCircleForm() { delete ui; }

void AddTrappyCircleForm::on_pushButton_clicked() {
  ui->lineEdit->clear();
  ui->lineEdit_2->clear();
  ui->lineEdit_3->clear();
  ui->lineEdit_4->clear();
}

void AddTrappyCircleForm::on_pushButton_2_clicked() {
  QColorDialog* qcd = new QColorDialog;
  qcd->setModal(true);
  ui->lineEdit_4->setText(qcd->getColor().name());
}

void AddTrappyCircleForm::on_pushButton_3_clicked() {
  double x = (ui->lineEdit->displayText()).toDouble();
  double y = (ui->lineEdit_2->displayText()).toDouble();
  double radius = (ui->lineEdit_3->displayText()).toDouble();
  QColor color = QColor(ui->lineEdit_4->displayText());
  emit AddTrappyCircle(x, y, radius, color);
  close();
}
