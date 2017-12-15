#ifndef WTSETTINGS_H
#define WTSETTINGS_H

#include <QWidget>
#include <QString>

#include "ui_WtSettings.h"

//======================================================================================================================
namespace Ui {
class WtSettings;
}

//======================================================================================================================
class VideoConfProvider;

//======================================================================================================================
// Place class description here
class WtSettings : public QWidget
{
  using _Base = QWidget;
  Q_OBJECT
public:
  explicit WtSettings(VideoConfProvider& parent);
  virtual ~WtSettings();

signals:
  void serverConnect(const QString&, const QString&, const QString&);

private slots:
  void onCameraChanged(int);
  void onMicChanged(int);
  void onSpeakerChanged(int);

private:
  void populateCameras();
  void populateMics();
  void populateSpeakers();

  // Disable copying
  WtSettings(const WtSettings&) = delete;
  WtSettings& operator=(const WtSettings&) = delete;

  Ui::WtSettings *ui;
  VideoConfProvider& wtVideo_;
};

#endif // WTSETTINGS_H
