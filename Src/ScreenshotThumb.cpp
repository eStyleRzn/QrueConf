#include "ScreenshotThumb.h"

#include <QVariant>
#include <QStyle>
#include <QScreen>

//======================================================================================================================
ScreenshotThumb::ScreenshotThumb(QScreen& screen, int screenIndex, QWidget* parent)
  : _Base(parent)
  , screenIndex_(screenIndex)
{
  QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
  setSizePolicy(sizePolicy);
  // setFrameShape(QFrame::Box);
  setAlignment(Qt::AlignCenter);

  const auto r = screen.geometry();
  auto pixmap = screen.grabWindow(0, r.x(), r.y(), r.width(), r.height());

  // Размеры картинки
  static const int imageHeight  = 200;
  static const int imageWidth   = 350;

  setPixmap(pixmap.scaled(QSize(imageWidth, imageHeight)));
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
    emit selected(screenIndex_);
  }

  return ok;
}

//----------------------------------------------------------------------------------------------------------------------
void ScreenshotThumb::mousePressEvent(QMouseEvent* event)
{
  _Base::mousePressEvent(event);

  emit clicked();
}
