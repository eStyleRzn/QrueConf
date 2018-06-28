
#include "MainWindow.h"

#include "Objbase.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QFile styleFile(":/style.qss");
  if (styleFile.open(QIODevice::ReadOnly))
  {
    a.setStyleSheet(styleFile.readAll());
  }

  MainWindow w;
  w.show();

  return a.exec();
}
