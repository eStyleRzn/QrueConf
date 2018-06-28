#ifndef SCREENSHOTTHUMB_H
#define SCREENSHOTTHUMB_H

#include <QLabel>

//======================================================================================================================
// TODO Place class description here
class ScreenshotThumb : public QLabel
{
  Q_OBJECT
  using _Base = QLabel;
  Q_PROPERTY(bool selected MEMBER selected_)
public:
  ScreenshotThumb(QScreen&, int screenIndex, QWidget* parent = Q_NULLPTR);
  virtual ~ScreenshotThumb();

public slots:
  bool select(bool set);

signals:
  void clicked();
  void selected(int screenIndex);

protected:
    void mousePressEvent(QMouseEvent* event);

private:
  // Disable copying
  ScreenshotThumb(const ScreenshotThumb&) = delete;
  ScreenshotThumb& operator=(const ScreenshotThumb&) = delete;

  bool selected_ = false;
  int screenIndex_ = 0;
};

#endif // SCREENSHOTTHUMB_H
