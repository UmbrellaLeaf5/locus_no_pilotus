#include "add_hill_form.h"

#include <icecream.hpp>

#include "ui_add_hill_form.h"


AddHillForm::AddHillForm(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddHillForm) {
  ui->setupUi(this);

  // на начальный момент на окне находится 3 поля ввода
  AddNewInputFields(3);
}

AddHillForm::~AddHillForm() { delete ui; }

void AddHillForm::on_createPushButton_clicked() {
  std::vector<lib::Point> points;
  for (size_t i = 0; i < both_coords_point_line_edits_.size(); i++) {
    points.push_back(
        {both_coords_point_line_edits_[i].abscissa->displayText().toDouble(),
         both_coords_point_line_edits_[i].ordinate->displayText().toDouble()});
  }
  emit AddHill(points);
  close();
}

void AddHillForm::on_clearPushButton_clicked() {
  for (size_t i = 0; i < both_coords_point_line_edits_.size(); i++) {
    both_coords_point_line_edits_[i].abscissa->clear();
    both_coords_point_line_edits_[i].ordinate->clear();
  }
}

void AddHillForm::on_newPushButton_clicked() { AddNewInputFields(); }

void AddHillForm::AddNewInputFields(size_t amount) {
  // передвигаем кнопки в конец
  ui->gridLayout->removeItem(ui->buttonsLayout);
  ui->gridLayout->addItem(ui->buttonsLayout, ui->gridLayout->count() + amount,
                          0);

  // (-1, так как buttonLayout считается за отдельный уже находящийся элемент)
  auto old_size = ui->gridLayout->count() - 1;
  auto new_size = ui->gridLayout->count() - 1 + amount;

  for (size_t i = old_size; i < new_size; i++) {
    // создаём виджет и лейаут, на который будем добавлять поля ввода и лейблы
    point_layouts_widgets_.emplace_back(new QWidget(ui->gridLayoutWidget));
    point_layouts_widgets_[i]->setObjectName("point" + QString::number(i + 1) +
                                             "LayoutWidget");
    point_layouts_widgets_[i]->setLayout(new QHBoxLayout);
    ui->gridLayout->addWidget(point_layouts_widgets_[i].get(), i, 0);

    // добавляем лейбл с указанием, к какой точке он относится
    QLabel* point_label = new QLabel(this);
    point_label->setObjectName("point" + QString::number(i + 1) + "Label");
    point_label->setText("Point " + QString::number(i + 1) + ":");
    point_layouts_widgets_[i]->layout()->addWidget(point_label);

    // добавляем лейбл координаты X и поле для его ввода
    QLabel* abscissa_label = new QLabel(this);
    abscissa_label->setObjectName("abscissa" + QString::number(i + 1) +
                                  "Label");
    abscissa_label->setText("X:");
    point_layouts_widgets_[i]->layout()->addWidget(abscissa_label);

    QLineEdit* abscissa_line_edit = new QLineEdit(this);
    abscissa_line_edit->setObjectName("abscissa" + QString::number(i + 1) +
                                      "LineEdit");
    point_layouts_widgets_[i]->layout()->addWidget(abscissa_line_edit);

    // добавляем лейбл координаты Y и поле для его ввода
    QLabel* ordinate_label = new QLabel(this);
    ordinate_label->setObjectName("ordinate" + QString::number(i + 1) +
                                  "Label");
    ordinate_label->setText("Y:");
    point_layouts_widgets_[i]->layout()->addWidget(ordinate_label);

    QLineEdit* ordinate_line_edit = new QLineEdit(this);
    ordinate_line_edit->setObjectName("ordinate" + QString::number(i + 1) +
                                      "LineEdit");
    point_layouts_widgets_[i]->layout()->addWidget(ordinate_line_edit);

    // добавляем оба лейбла в вектор
    both_coords_point_line_edits_.emplace_back(
        PointLineEdits(abscissa_line_edit, ordinate_line_edit));
  }
}
