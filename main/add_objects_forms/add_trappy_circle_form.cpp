#include "add_trappy_circle_form.h"

#include <QColorDialog>

#include "ui_add_trappy_circle_form.h"

AddTrappyCircleForm::AddTrappyCircleForm(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddTrappyCircleForm) {
  ui->setupUi(this);
}

AddTrappyCircleForm::~AddTrappyCircleForm() { delete ui; }

void AddTrappyCircleForm::on_clearPushButton_clicked() {
  ui->abscissaLineEdit->clear();
  ui->ordinateLineEdit->clear();
  ui->radiusLineEdit->clear();
  ui->colorLineEdit->clear();
}

void AddTrappyCircleForm::on_colorSelectPushButton_clicked() {
  QColorDialog* qcd = new QColorDialog;
  qcd->setModal(true);
  ui->colorLineEdit->setText(qcd->getColor().name());
}

void AddTrappyCircleForm::on_createPushButton_clicked() {
  double x = (ui->abscissaLineEdit->displayText()).toDouble();
  double y = (ui->ordinateLineEdit->displayText()).toDouble();
  double radius = (ui->radiusLineEdit->displayText()).toDouble();

  QColor color = QColor(ui->colorLineEdit->displayText());

  emit AddTrappyCircle(x, y, radius, color);
  close();
}
