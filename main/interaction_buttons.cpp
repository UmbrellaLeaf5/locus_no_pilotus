#include <cmath>

#include "mainwindow.h"

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
    }
    default:
      break;
  }
  connect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this,
          SLOT(mousePressObjectsButton(QMouseEvent*)));

  ui->plot->setCursor(Qt::CrossCursor);
  cursor_ = CursorType::DefaultCursor;
}

void MainWindow::keyPressEvent(QKeyEvent* key_event) {
  if (key_event->key() == Qt::Key_Escape) {
    switch (cursor_) {
      case CursorType::DefaultCursor:
      case CursorType::TargetCursor:
        break;
      case CursorType::TrCircleCursor: {
        DisconnectObject(gui::ObjectType::TrappyCircles);
        break;
      }
      case CursorType::TrLineCursor: {
        DisconnectObject(gui::ObjectType::TrappyLines);
        break;
      }
      case CursorType::HillCursor: {
        DisconnectObject(gui::ObjectType::Hills);
        break;
      }
    }

    // Проверка на то, что пользователь уже начал создавать объект,
    // поэтому при нажатии Esc мы должны удалять последний добавленный объект
    switch (what_obj_addition_) {
      case WhatObjectAddition::Nothing:
      case WhatObjectAddition::Target:
        break;
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
    }

    cursor_ = CursorType::DefaultCursor;
    what_obj_addition_ = WhatObjectAddition::Nothing;
    ui->plot->setCursor(Qt::CrossCursor);

    area_->Redraw();
    t_connection_->UpdateTables();
  }
}

void MainWindow::mousePressObjectsButton(QMouseEvent* mouse_event) {
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

      what_obj_addition_ = WhatObjectAddition::Hill;
      break;
    }
    default:
      break;
  }
  area_->Redraw();
  t_connection_->UpdateTables();
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
  if (!ui->plot->selectedGraphs().empty()) {
    for (const auto& t_ptr : manager_->GetTargetsPtrs()) {
      if (t_ptr->GetGraphPtr() == ui->plot->selectedGraphs()[0]) {
        size_t last = manager_->GetTrappyLines().size() - 1;
        if (manager_->GetTrappyLinesPtrs()[last]->GetTargetsPtrs().second !=
            t_ptr) {
          manager_->GetTrappyLinesPtrs()[last]->SetSecondTarget(t_ptr);

          DisconnectObject(gui::ObjectType::TrappyLines);

          what_obj_addition_ = WhatObjectAddition::Nothing;
          area_->Redraw();
          t_connection_->UpdateTables();
          break;
        }
      }
    }
  }
}

void MainWindow::mousePressAddVertice(QMouseEvent* mouse_event) {
  double x = ui->plot->xAxis->pixelToCoord(mouse_event->pos().x());
  double y = ui->plot->yAxis->pixelToCoord(mouse_event->pos().y());
  size_t last = manager_->GetHills().size() - 1;

  if (abs(manager_->GetHills()[last].GetPoints()[0].x - x) < 0.1 &&
      abs(manager_->GetHills()[last].GetPoints()[0].y - y) < 0.1) {
    DisconnectObject(gui::ObjectType::Hills);

    what_obj_addition_ = WhatObjectAddition::Nothing;
  } else
    manager_->GetHillsPtrs()[last]->AddVertice({x, y});

  area_->Redraw();
  t_connection_->UpdateTables();
}
