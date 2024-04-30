#pragma once

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <memory>
#include <vector>

#include "lib/point.h"

namespace Ui {
class AddHillForm;
}

/// @brief Структура из двух QLineEdit, относящихся к вводу координаты точки
/// (чтобы не использовать std::pair<std::unique_ptr<QLineEdit>, ... >)
struct PointLineEdits {
  PointLineEdits() = default;
  PointLineEdits(QLineEdit* abscissa, QLineEdit* ordinate)
      : abscissa{abscissa}, ordinate{ordinate} {}

  std::unique_ptr<QLineEdit> abscissa;
  std::unique_ptr<QLineEdit> ordinate;
};

class AddHillForm : public QDialog {
  Q_OBJECT

 public:
  explicit AddHillForm(QWidget* parent = nullptr);
  ~AddHillForm();

 signals:
  void AddHill(std::vector<std::pair<std::string, std::string>> points);

 private slots:
  void on_createPushButton_clicked();
  void on_clearPushButton_clicked();
  void on_newPushButton_clicked();

 private:
  /**
   * @brief Добавляет определенное количество новых полей ввода на форму
   * @param amount: кол-ло новых полей ввода точки
   */
  void AddNewInputFields(size_t amount = 1);

  Ui::AddHillForm* ui;
  std::vector<std::unique_ptr<QWidget>> point_layouts_widgets_;
  std::vector<PointLineEdits> both_coords_point_line_edits_;
};
