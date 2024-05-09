// Qt libs:
#include <QApplication>

// our code libs:
#include "mainwindow.h"  // lovely window :)

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;

  w.show();
  return a.exec();
}
