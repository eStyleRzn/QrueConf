#ifndef DLGSHARESCREEN_H
#define DLGSHARESCREEN_H

#include <QDialog>

#include "ui_DlgShareScreen.h"

class QJsonValueRef;
class VideoConfProvider;

//======================================================================================================================
// TODO Place class description here
class DlgShareScreen : public QDialog
{
  using _Base = QDialog;
  using TCScreensInfo = QSharedPointer<QJsonArray>;
  Q_OBJECT
public:
  DlgShareScreen(QWidget* parent, VideoConfProvider* wtVideo_);
  virtual ~DlgShareScreen();

  void selectedScreen(int& index, QRect& rect) const;

signals:
  void selectDisplay(bool);

private slots:
  void onScreens(const QSharedPointer<QJsonArray>&);
  void onScreenThumbClicked();
  void onScreenSelected(int, QRect);

private:
  // Disable copying
  DlgShareScreen(const DlgShareScreen&) = delete;
  DlgShareScreen& operator=(const DlgShareScreen&) = delete;

  QScreen* getScreen(const QJsonValueRef&) const;

  Ui::DlgShareScreen ui_;
  VideoConfProvider* wtVideo_;
  TCScreensInfo screensInfo_;
  int selectedScreen_ = 0;
  QRect selectScreenRect_;
};


#endif // DLGSHARESCREEN_H
