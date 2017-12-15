#ifndef DLGCREATECONF_H
#define DLGCREATECONF_H

#include <QDialog>

#include "VideoConfProvider.h"

//======================================================================================================================

namespace Ui {
class DlgCreateConf;
}

//======================================================================================================================
// TODO Place class description here
class DlgCreateConf : public QDialog
{
  using _Base = QDialog;
  Q_OBJECT

public:
  explicit DlgCreateConf(VideoConfProvider&, QWidget *parent = 0);
  virtual ~DlgCreateConf();

private slots:
  void onInclude();
  void onExclude();
  void onGetABook(AddressBook::Shared);

  void setOkEnabled();

private:
  // Disable copying
  DlgCreateConf(const DlgCreateConf&) = delete;
  DlgCreateConf& operator=(const DlgCreateConf&) = delete;

  Ui::DlgCreateConf* ui;
  VideoConfProvider& wtVideo_;
};

#endif // DLGCREATECONF_H
