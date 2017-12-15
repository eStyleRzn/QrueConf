#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"

//======================================================================================================================
class VideoConfProvider;
class QDockWidget;
class WtSettings;
class WtStartConf;
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);

public slots:
  void connectToServer(const QString& host, const QString& user, const QString& password);

private slots:
  void onCreateConference();

private:
  static QString host_;
  static QString user_;
  static QString password_;

  Ui::MainWindow ui;

  QDockWidget* dockSettings_;
  QDockWidget* dockStartConf_;
  WtSettings* wtSettings_;
  WtStartConf* wtStartConf_;
  VideoConfProvider* wtVideo_;
};

#endif // MAINWINDOW_H
