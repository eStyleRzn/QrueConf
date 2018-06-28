#include "MainWindow.h"

#include <QDockWidget>
#include <QDebug>

#include "VideoConfProvider.h"
#include "WtSettings.h"
#include "WtStartConf.h"
#include "DlgIncomingCall.h"
#include "DlgCreateConf.h"
#include "DlgShareScreen.h"

//======================================================================================================================
using namespace TrueConf;

//======================================================================================================================
QString MainWindow::host_;
QString MainWindow::user_;
QString MainWindow::password_;

//----------------------------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
  ui.setupUi(this);

  wtVideo_ = new VideoConfProvider(this);

  connect(wtVideo_, &VideoConfProvider::onLoginSucceded, [this]()
  {
    menuBar()->setEnabled(true);
    statusBar()->showMessage("User logged in");
  });

  connect(wtVideo_, &VideoConfProvider::onIncomingCall, [this](const QString&, const QString& info)
  {
    DlgIncomingCall dlg(info);
    if (QDialog::Accepted == dlg.exec())
      wtVideo_->accept();
    else
      wtVideo_->reject();
  });

//  connect(wtVideo_, &VideoConfProvider::onConfStarted, [this]()
//  {
//    wtVideo_->getConfUsers();
//  });

  connect(wtVideo_, SIGNAL(onCreated()), this, SLOT(onAxLoaded()));

  setCentralWidget(wtVideo_);
}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::connectToServer(const QString& host, const QString& user, const QString& password)
{
//  QMetaObject::invokeMethod(wtVideo_,
//                            "connectToServer",
//                            Qt::QueuedConnection,
//                            Q_ARG(QString, host_),
//                            Q_ARG(QString, user_),
//                            Q_ARG(QString, password_));

  // Do connect
  wtVideo_->connectToServer(host);
  connect(wtVideo_, &VideoConfProvider::onServerConnected, [=]()
  {
    wtVideo_->login(user, password);
  });
}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::onCreateConference()
{
  DlgCreateConf dlg(*wtVideo_);
  dlg.exec();
}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::onScreenSharing()
{
  DlgShareScreen dlg(this, wtVideo_);
  if (QDialog::Accepted == dlg.exec())
  {
    wtVideo_->startScreenCapture(QString::number(dlg.selectedScreen() + 1));

    QWidgetList widgets = qApp->topLevelWidgets();
    for (auto&& wt : widgets)
    {
      wt->setWindowState(Qt::WindowMinimized);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::onAxLoaded()
{
  qDebug() << "VideoConfProvider library path is: " << wtVideo_->libPath();

//  wtVideo_->getDisplayNameById("1");
//  wtVideo_->getSettings();
//  wtVideo_->getSystemInfo();

  if (!windowsCreated_)
  {
    createWindowsAfterStart();
    windowsCreated_ = true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
//void MainWindow::onShareScreen()
//{
//  DlgShareScreen dlg(this, wtVideo_);
//  dlg.exec();
//}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::createWindowsAfterStart()
{
  dockSettings_ = new QDockWidget(this);
  wtSettings_ = new WtSettings(*wtVideo_);
  dockSettings_->setWidget(wtSettings_);
  addDockWidget(Qt::LeftDockWidgetArea, dockSettings_);

  connect(wtSettings_, &WtSettings::serverConnect, this, &MainWindow::connectToServer);

  dockStartConf_ = new QDockWidget(this);
  wtStartConf_ = new WtStartConf(*wtVideo_);
  dockStartConf_->setWidget(wtStartConf_);
  addDockWidget(Qt::TopDockWidgetArea, dockStartConf_);

  wtVideo_->show();

  auto menu = menuBar();
  menu->addAction("Create conference", this, SLOT(onCreateConference()));
  actScreenSharing_ = menu->addAction("Screen sharing", this, SLOT(onScreenSharing()));
//  connect(actScreenSharing_, SIGNAL(toggled(bool)), this, SLOT(onShareScreen()));
  menu->setEnabled(false);
}

