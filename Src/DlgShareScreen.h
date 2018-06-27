#ifndef DLGSHARESCREEN_H
#define DLGSHARESCREEN_H

#include <QDialog>

#include "ui_DlgShareScreen.h"

class VideoConfProvider;

//======================================================================================================================
// TODO Place class description here
class DlgShareScreen : public QDialog
{
  using _Base = QDialog;
  Q_OBJECT
public:
  DlgShareScreen(QWidget* parent, VideoConfProvider* wtVideo_);
  virtual ~DlgShareScreen();

private slots:
  void onModeChanged(int);
  void onMonitors(const QSharedPointer<QJsonArray>&);

private:
  // Disable copying
  DlgShareScreen(const DlgShareScreen&) = delete;
  DlgShareScreen& operator=(const DlgShareScreen&) = delete;

  Ui::DlgShareScreen ui_;
  VideoConfProvider* wtVideo_;
};


#endif // DLGSHARESCREEN_H
