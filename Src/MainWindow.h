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
  void onScreenSharing();
  void onAxLoaded();
//  void onShareScreen();

private:
  void createWindowsAfterStart();

  static QString host_;
  static QString user_;
  static QString password_;

  Ui::MainWindow ui;

  QDockWidget* dockSettings_;
  QDockWidget* dockStartConf_;
  WtSettings* wtSettings_;
  WtStartConf* wtStartConf_;
  VideoConfProvider* wtVideo_;
  QAction* actScreenSharing_ = false;
  bool windowsCreated_ = false;
};

#endif // MAINWINDOW_H
