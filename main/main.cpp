#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("Trajectory Calculation");
  w.setWindowIcon(QIcon("../images/icon.png"));

  w.show();
  return a.exec();
}
