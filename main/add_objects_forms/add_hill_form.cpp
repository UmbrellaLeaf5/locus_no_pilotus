#include "add_hill_form.h"

#include "ui_add_hill_form.h"

AddHillForm::AddHillForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddHillForm) {
  ui->setupUi(this);
}

AddHillForm::~AddHillForm() { delete ui; }
