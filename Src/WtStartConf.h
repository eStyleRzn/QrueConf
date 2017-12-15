#ifndef WTSTARTCONF_H
#define WTSTARTCONF_H

#include <QWidget>
#include "AddressBook.h"

//======================================================================================================================
namespace Ui {
class WtStartConf;
}

//======================================================================================================================
class VideoConfProvider;

//======================================================================================================================
// TODO Place class description here
class WtStartConf : public QWidget
{
  using _Base = QWidget;
  Q_OBJECT
public:
  explicit WtStartConf(VideoConfProvider& parent);
  virtual ~WtStartConf();

private:
  // Disable copying
  WtStartConf(const WtStartConf&) = delete;
  WtStartConf& operator=(const WtStartConf&) = delete;

  Ui::WtStartConf *ui;
  VideoConfProvider& wtVideo_;
};

#endif // WTSTARTCONF_H
