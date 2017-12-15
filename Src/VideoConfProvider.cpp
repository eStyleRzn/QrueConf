#include "VideoConfProvider.h"

#include "windows.h"
#include <oleauto.h>

#include <QDebug>
#include <QJsonDocument>
#include <QThread>

#include "ServerNotifyProcessor.h"

using namespace TrueConf;

//======================================================================================================================
VideoConfProvider::VideoConfProvider(QWidget* parent, Qt::WindowFlags f)
  : _Base(parent, f)
  , ui_( new Ui::VideoConfProvider)
{
  ui_->setupUi(this);

  obj_ = new TrueConf::TrueConfCallX(/*this*/);
  obj_->setObjectName(QStringLiteral("obj_"));
  ui_->layout->addWidget(obj_, 0, 0, 1, 1);

  connect(obj_, SIGNAL(exception(int, const QString&, const QString& , const QString& )),
          this, SLOT(onAxException(int, const QString&, const QString&, const QString&)));

  connNotify_ = connect(obj_, SIGNAL(OnXNotify(const QString&)), this, SLOT(axXNotify(const QString&)));

  connCmdExec_ = connect(obj_, SIGNAL(OnXCommandExecution(const QString&, const QString&)),
                         this, SLOT(axXCommandExecution(const QString&, const QString&)));

  connect(obj_, SIGNAL(OnXAfterStart()), this, SIGNAL(onCreated()));
  connect(obj_, SIGNAL(OnServerConnected(const QString&)), this, SLOT(axConnected(const QString&)));
  connect(obj_, SIGNAL(OnLogin(const QString&)), this, SLOT(axLoginSucceded(const QString&)));
  connect(obj_, SIGNAL(OnUpdateCameraInfo(const QString&)), this, SLOT(axUpdateCameraInfo(const QString&)));
  connect(obj_, SIGNAL(OnConferenceCreated(const QString&)), this, SLOT(axConferenceCreated(const QString&)));
  connect(obj_, SIGNAL(OnConferenceDeleted(const QString&)), this, SLOT(axConferenceDeleted(const QString&)));
  connect(obj_, SIGNAL(OnVideoMatrixChanged(const QString&)), this, SLOT(axVideoMatrixChanged(const QString&)));

  connect(obj_, SIGNAL(OnDeviceModesDone(const QString&)), this, SLOT(axDeviceModesDone(const QString&)));
  connect(obj_, SIGNAL(OnServerDisconnected(const QString&)), this, SLOT(axServerDisconnected(const QString&)));
  connect(obj_, SIGNAL(OnLogout(const QString&)), this, SLOT(axLogout(const QString&)));
  connect(obj_, SIGNAL(OnXLoginError(int)), this, SLOT(axXLoginError(int)));
  connect(obj_, SIGNAL(OnInviteReceived(const QString&)), this, SLOT(axInviteReceived(const QString&)));

  connect(obj_, SIGNAL(OnXTerminate()), this, SLOT(axXTerminate()));

//  if (!connect(obj_, SIGNAL(signal(const QString&, int, void*)), SLOT(axEvent(QString,int,void*))))
//  {
//    Q_ASSERT_X(false, __FUNCTION__, "Logic error");
//  }
}

//----------------------------------------------------------------------------------------------------------------------
VideoConfProvider::~VideoConfProvider()
{
  delete ui_;

  // Stop receiving notifications from CallX
  disconnect(connCmdExec_);
  disconnect(connNotify_);

  obj_->disableEventSink();

  // Stop CallX
  obj_->shutdown();

  // Destroy CallX's ActiveX
  obj_->clear();

  // Delete ActiveX's holder object
  delete obj_;
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::createConference(const QString& name, int mode, const QStringList& users)
{
  obj_->createConference(name, ServerNotifyProcessor::EnumCallXConfModes.at(mode), true, users.join(","));
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axEvent(const QString& name, int argc, void* argv)
{
  Q_UNUSED(argc);
  VARIANTARG* params = (VARIANTARG*)argv;
  Q_UNUSED(params);

  qDebug() << __FUNCTION__ << name << " signal emitted from TrueConfCallX object";
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axConnected(const QString&)
{
//  qDebug() << __FUNCTION__ << s;
  emit onServerConnected();
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axLoginSucceded(const QString&)
{
//  qDebug() << __FUNCTION__ << s;
  emit onLoginSucceded();
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axUpdateCameraInfo(const QString&)
{
//  qDebug() << __FUNCTION__ << s;
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axConferenceCreated(const QString& s)
{
//  qDebug() << __FUNCTION__ << s;
  emit onConfStarted(s);
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axConferenceDeleted(const QString& s)
{
  qDebug() << __FUNCTION__ << s;
  emit onConfStopped(s);
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axVideoMatrixChanged(const QString&)
{
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axXNotify(const QString& s)
{
  Q_UNUSED(s)
//  processServerNotification(s);
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axDeviceModesDone(const QString&)
{
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axServerDisconnected(const QString&)
{
  emit onServerDisconnected();
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axLogout(const QString&)
{
  emit onLogout();
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axXLoginError(int)
{
  emit onLoginFailed();
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axXCommandExecution(const QString& cmdName, const QString& allData)
{
  if (cmdName == ServerNotifyProcessor::enumStrVal<ServerNotifyProcessor::EnumICallX>(ServerNotifyProcessor::EnumICallX::getAbook))
  {
    QJsonArray out;
    ServerNotifyProcessor::getAbook(allData, out);
    emit onGetAddressBook(AddressBook::Shared::create(out));
  }
  else
  {
    qDebug() << __FUNCTION__ << cmdName << allData;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axInviteReceived(const QString& details)
{
//  qDebug() << __FUNCTION__ << details;

  QString callerID; QString callerInfo;

  ServerNotifyProcessor::incomingCall(details, callerID, callerInfo);
  emit onIncomingCall(callerID, callerInfo);
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::axXTerminate()
{
  qDebug() << __FUNCTION__;
}

//----------------------------------------------------------------------------------------------------------------------
void VideoConfProvider::onAxException(int code, const QString& source, const QString& desc, const QString& help)
{
  qDebug() << code << source << desc << help;
}
