#ifndef VIDEOCONFPROVIDER_H
#define VIDEOCONFPROVIDER_H

#include <QFrame>

#include "TrueConf_CallX.h"
#include "ui_VideoConfProvider.h"
#include "AddressBook.h"

//======================================================================================================================
// TODO Place class description here
class Ui::VideoConfProvider;
class VideoConfProvider : public QFrame
{
  using _Base = QFrame;
  Q_OBJECT
public:
  VideoConfProvider(QWidget *parent = 0, Qt::WindowFlags f = 0);
  virtual ~VideoConfProvider();

public slots:
  void connectToServer(const QString& serverStr) { obj_->connectToServer(serverStr); }
//  void disconnectFromServer();

  void login(const QString& login, const QString& password) { obj_->login(login, password); }
  void logout() { obj_->logout(); }

  void accept() { obj_->accept(); }
  void reject() { obj_->reject(); }

  void startCall(const QString& peerId) { obj_->call(peerId); }
  void stopCall() { obj_->hangUp(); }

  void restart() { obj_->XRestart(); }
  QString libPath() const { return obj_->CallXPath(); }

  void cameraModes() { return obj_->getModes(); }

  void setMyVideoMuted(bool mute) { obj_->setVideoMute(mute); }
  void setBackgroundImage(const QString& imagePath)
  {
    obj_->XSetBackgroundImage(imagePath);
  }

  int getCameraCount() { return obj_->XGetCameraCount(); }
  void setCameraByIndex(int cameraIdx) { obj_->XSetCameraByIndex(cameraIdx); }
  QString getCameraByIndex(int cameraIdx) { return obj_->XGetCameraByIndex(cameraIdx); }

  int getSpeakerCount() { return obj_->XGetSpeakerCount(); }
  void setSpeakerByIndex(int speakerIdx) { obj_->XSelectSpeakerByIndex(speakerIdx); }
  QString getSpeakerByIndex(int speakerIdx) { return obj_->XGetSpeakerByIndex(speakerIdx); }

  int getMicCount() { return obj_->XGetMicCount(); }
  void setMicByIndex(int microphoneIdx) { obj_->XSelectMicByIndex(microphoneIdx); }
  QString getMicByIndex(int microphoneIdx) { return obj_->XGetMicByIndex(microphoneIdx); }

  void getAddressBook() { return obj_->getAbook(); }

  void createConference(const QString& name, int mode, const QStringList& users);
  void getConfUsers() { obj_->getIdListRequestInvite(); }

  void startScreenCapture(const QString& id);
  void stopScreenCapture();

  void getSelfieBroadcast();
  void getDisplayNameById(const QString&);
  void getMonitorsInfo();
  void getSettings();
  void getSystemInfo();

signals:
  void onCreated();
  void onServerConnected();
  void onServerDisconnected();
  void onLoginSucceded();
  void onLoginFailed();
  void onLogout();

  void onConfStarted(const QString&);
  void onConfStopped(const QString&);

  void onGetAddressBook(AddressBook::Shared);
  void onGetMonitorsInfo(const QSharedPointer<QJsonArray>&);

  void onIncomingCall(QString& callerID, QString& callerInfo);

private slots:
  void axEvent(const QString&,int,void*);
  void axConnected(const QString&);
  void axLoginSucceded(const QString&);
  void axUpdateCameraInfo(const QString&);
  void axConferenceCreated(const QString&);
  void axConferenceDeleted(const QString&);
  void axVideoMatrixChanged(const QString&);
  void axXNotify(const QString&);
  void axDeviceModesDone(const QString&);
  void axServerDisconnected(const QString&);
  void axLogout(const QString&);
  void axXLoginError(int);
  void axXCommandExecution(const QString&, const QString&);
  void axInviteReceived(const QString&);
  void axXTerminate();

  void onAxException(int code, const QString &source, const QString &desc, const QString &help);

private:
  // Disable copying
  VideoConfProvider(const VideoConfProvider&) = delete;
  VideoConfProvider& operator=(const VideoConfProvider&) = delete;

  Ui::VideoConfProvider* ui_;
  TrueConf::TrueConfCallX* obj_;

  QMetaObject::Connection connCmdExec_;
  QMetaObject::Connection connNotify_;
};

#endif // VIDEOCONFPROVIDER_H
