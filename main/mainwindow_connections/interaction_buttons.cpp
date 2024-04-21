#include <cmath>

#include "main/mainwindow.h"

void MainWindow::DisconnectObject(gui::ObjectType obj_type) {
  switch (obj_type) {
    case gui::ObjectType::TrappyCircles: {
      disconnect(ui->plot, SIGNAL(mouseMove(QMouseEvent*)), this,
                 SLOT(mouseMoveSetRadiusFromPlot(QMouseEvent*)));
      disconnect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this,
                 SLOT(mousePressSetRadiusFromPlot(QMouseEvent*)));
      break;
    }

    case gui::ObjectType::TrappyLines: {
      disconnect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this,
                 SLOT(mousePressSelectSecondTarget(QMouseEvent*)));
      break;
    }

    case gui::ObjectType::Hills: {
      disconnect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this,
                 SLOT(mousePressAddVertice(QMouseEvent*)));
      disconnect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), this,
                 SLOT(mousePressDeleteLastVertice(QMouseEvent*)));
    }

    default:
      break;
  }

  connect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this,
          SLOT(mousePressObjectsButton(QMouseEvent*)));

  ui->plot->setCursor(Qt::CrossCursor);
  cursor_ = CursorType::DefaultCursor;
}

// Функция, которая удаляет последний добавленный объект с помощью кнопок слева,
// причем его добавление не закончилось. Она должна вызывается везде, где
// происходит взаимодействие пользователя с кнопками класса "MainWindow"
void MainWindow::DeleteLastAddedObject() {
  DisconnectObject(GetObjType());
  switch (what_obj_addition_) {
    case WhatObjectAddition::TrCircle: {
      size_t last = manager_->GetTrappyCircles().size() - 1;
      manager_->Remove(gui::ObjectType::TrappyCircles, last);
      break;
    }

    case WhatObjectAddition::TrLine: {
      size_t last = manager_->GetTrappyLines().size() - 1;
      manager_->Remove(gui::ObjectType::TrappyLines, last);
      break;
    }

    case WhatObjectAddition::Hill: {
      size_t last = manager_->GetHills().size() - 1;
      manager_->Remove(gui::ObjectType::Hills, last);
      break;
    }

    default:
      break;
  }

  area_->Redraw();
  t_connection_->UpdateTables();

  what_obj_addition_ = WhatObjectAddition::Nothing;
}

void MainWindow::keyPressEvent(QKeyEvent* key_event) {
  if (key_event->key() == Qt::Key_Escape) {
    // Проверка на то, что пользователь уже начал создавать объект,
    // поэтому при нажатии Esc мы должны удалять последний добавленный объект
    DeleteLastAddedObject();
  }
}

void MainWindow::mousePressObjectsButton(QMouseEvent* mouse_event) {
  if (mouse_event->button() == Qt::LeftButton) {
    double x = ui->plot->xAxis->pixelToCoord(mouse_event->pos().x());
    double y = ui->plot->yAxis->pixelToCoord(mouse_event->pos().y());

    switch (cursor_) {
      case CursorType::TargetCursor: {
        manager_->Add(new gui::Target(x, y));

        ui->plot->setCursor(Qt::CrossCursor);
        cursor_ = CursorType::DefaultCursor;
        break;
      }

      case CursorType::TrCircleCursor: {
        manager_->Add(new gui::TrappyCircle({x, y}, 0));
        disconnect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this,
                   SLOT(mousePressObjectsButton(QMouseEvent*)));

        connect(ui->plot, SIGNAL(mouseMove(QMouseEvent*)), this,
                SLOT(mouseMoveSetRadiusFromPlot(QMouseEvent*)));
        connect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this,
                SLOT(mousePressSetRadiusFromPlot(QMouseEvent*)));

        ui->plot->setCursor(Qt::ClosedHandCursor);
        what_obj_addition_ = WhatObjectAddition::TrCircle;
        break;
      }

      case CursorType::TrLineCursor: {
        if (!ui->plot->selectedGraphs().empty()) {
          for (const auto& t_ptr : manager_->GetTargetsPtrs()) {
            if (t_ptr->GetGraphPtr() == ui->plot->selectedGraphs()[0]) {
              manager_->Add(new gui::TrappyLine(t_ptr, t_ptr));
              break;
            }
          }
          disconnect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this,
                     SLOT(mousePressObjectsButton(QMouseEvent*)));

          connect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this,
                  SLOT(mousePressSelectSecondTarget(QMouseEvent*)));

          what_obj_addition_ = WhatObjectAddition::TrLine;
        }
        break;
      }

      case CursorType::HillCursor: {
        manager_->Add(new gui::Hill{{x, y}, {x, y}});

        disconnect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this,
                   SLOT(mousePressObjectsButton(QMouseEvent*)));

        connect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this,
                SLOT(mousePressAddVertice(QMouseEvent*)));
        connect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), this,
                SLOT(mousePressDeleteLastVertice(QMouseEvent*)));

        what_obj_addition_ = WhatObjectAddition::Hill;
        break;
      }

      default:
        break;
    }

    area_->Redraw();
    t_connection_->UpdateTables();
  }
}

void MainWindow::mousePressSetRadiusFromPlot(QMouseEvent* mouse_event) {
  if (mouse_event->button() == Qt::LeftButton) {
    DisconnectObject(gui::ObjectType::TrappyCircles);
    what_obj_addition_ = WhatObjectAddition::Nothing;
  }
}

void MainWindow::mouseMoveSetRadiusFromPlot(QMouseEvent* mouse_event) {
  size_t last = manager_->GetTrappyCircles().size() - 1;

  // Расстояние от центра до курсора (по оси x)
  double x = abs(ui->plot->xAxis->pixelToCoord(mouse_event->pos().x()) -
                 manager_->GetTrappyCircles()[last].GetCenter().x);

  // Расстояние от центра до курсора (по оси y)
  double y = abs(ui->plot->yAxis->pixelToCoord(mouse_event->pos().y()) -
                 manager_->GetTrappyCircles()[last].GetCenter().y);

  // Значение радиуса
  double r = pow(pow(x, 2) + pow(y, 2), 0.5);

  manager_->GetTrappyCirclesPtrs()[last]->SetRadius(r);
  area_->Redraw();
  t_connection_->UpdateTables();
}

void MainWindow::mousePressSelectSecondTarget(QMouseEvent* mouse_event) {
  if (mouse_event->button() != Qt::LeftButton) return;
  if (ui->plot->selectedGraphs().empty()) return;

  for (const auto& t_ptr : manager_->GetTargetsPtrs()) {
    if (t_ptr->GetGraphPtr() == ui->plot->selectedGraphs()[0]) {
      size_t last = manager_->GetTrappyLines().size() - 1;

      // если это та же точка - пропускаем
      if (manager_->GetTrappyLinesPtrs()[last]->GetTargetsPtrs().second ==
          t_ptr)
        continue;

      manager_->GetTrappyLinesPtrs()[last]->SetSecondTarget(t_ptr);

      DisconnectObject(gui::ObjectType::TrappyLines);
      what_obj_addition_ = WhatObjectAddition::Nothing;

      area_->Redraw();
      t_connection_->UpdateTables();
      break;
    }
  }
}

void MainWindow::mousePressAddVertice(QMouseEvent* mouse_event) {
  if (mouse_event->button() == Qt::LeftButton) {
    // Позиция курсора в пикселях
    int x_pixels = mouse_event->pos().x();
    int y_pixels = mouse_event->pos().y();

    // // Позиция курсора в координатах
    double x = ui->plot->xAxis->pixelToCoord(x_pixels);
    double y = ui->plot->yAxis->pixelToCoord(y_pixels);

    size_t last = manager_->GetHills().size() - 1;

    // Позиция начальной точки в пикселях
    int x2_pixels = ui->plot->xAxis->coordToPixel(
        manager_->GetHills()[last].GetPoints()[0].x);
    int y2_pixels = ui->plot->yAxis->coordToPixel(
        manager_->GetHills()[last].GetPoints()[0].y);

    // Проверка на то, что расстояние от курсора до начальной точки меньше 10
    // пикселей. Если это так, то мы считаем, что он завершил создание Hill
    if (pow(pow(x_pixels - x2_pixels, 2) + pow(y_pixels - y2_pixels, 2), 0.5) <
            10 &&
        manager_->GetHills()[last].GetPoints().size() > 2) {
      DisconnectObject(gui::ObjectType::Hills);
      what_obj_addition_ = WhatObjectAddition::Nothing;

    } else if (manager_->GetHills()[last].GetPoints()[0] ==
               manager_->GetHills()[last].GetPoints()[1]) {
      size_t last_p = manager_->GetHills()[last].GetPoints().size() - 1;
      manager_->GetHillsPtrs()[last]->GetPoints()[last_p].x = x;
      manager_->GetHillsPtrs()[last]->GetPoints()[last_p].y = y;

    } else
      manager_->GetHillsPtrs()[last]->AddVertice({x, y});

    area_->Redraw();
    t_connection_->UpdateTables();
  }
}

void MainWindow::mousePressDeleteLastVertice(QMouseEvent* mouse_event) {
  if (mouse_event->button() == Qt::RightButton) {
    size_t last = manager_->GetHills().size() - 1;
    size_t vertices_size = manager_->GetHills()[last].GetPoints().size();
    if (vertices_size > 2)
      manager_->GetHillsPtrs()[last]->GetPoints().pop_back();

    else {
      if (manager_->GetHills()[last].GetPoints()[0] !=
          manager_->GetHills()[last].GetPoints()[1]) {
        manager_->GetHillsPtrs()[last]->GetPoints()[1] =
            manager_->GetHills()[last].GetPoints()[0];

      } else
        DeleteLastAddedObject();
    }

    area_->Redraw();
    t_connection_->UpdateTables();
  }
}
