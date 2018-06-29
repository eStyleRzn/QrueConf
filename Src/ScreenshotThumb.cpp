#include "ScreenshotThumb.h"

#include <QVariant>
#include <QStyle>
#include <QScreen>
#include <QResizeEvent>
//#include <QDebug>

//======================================================================================================================
ScreenshotThumb::ScreenshotThumb(QScreen& screen, int screenIndex, QWidget* parent)
  : _Base(parent)
  , screenIndex_(screenIndex)
{
  // Отшибаем ресайз родительского виджета по размерам этого виджета.
  QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
  setSizePolicy(sizePolicy);
  // setFrameShape(QFrame::Box);
  setAlignment(Qt::AlignCenter);

  screenRect_ = screen.geometry();
  img_ = screen.grabWindow(0, screenRect_.x(), screenRect_.y(), screenRect_.width(), screenRect_.height());
}

//----------------------------------------------------------------------------------------------------------------------
ScreenshotThumb::~ScreenshotThumb() {}

//----------------------------------------------------------------------------------------------------------------------
bool ScreenshotThumb::select(bool set)
{
  auto ok =  setProperty("selected", set);
  style()->unpolish(this);
  style()->polish(this);
  update();

  if (ok)
  {
    emit selected(screenIndex_, screenRect_);
  }

  return ok;
}

//----------------------------------------------------------------------------------------------------------------------
void ScreenshotThumb::resizeEvent(QResizeEvent* event)
{
//  qDebug() << __FUNCTION__ << event->size() << rect().size() << contentsRect() << frameSize();
  _Base::resizeEvent(event);

  setPixmap(img_.scaled(contentsRect().width(),
                        contentsRect().height()));
}

//----------------------------------------------------------------------------------------------------------------------
void ScreenshotThumb::mousePressEvent(QMouseEvent* event)
{
  _Base::mousePressEvent(event);

  emit clicked();
}
