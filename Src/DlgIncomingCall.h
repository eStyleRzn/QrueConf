#ifndef DLGINCOMINGCALL_H
#define DLGINCOMINGCALL_H

#include <QDialog>

//======================================================================================================================
namespace Ui {
class DlgIncomingCall;
}

//======================================================================================================================
// TODO Place class description here
class DlgIncomingCall : public QDialog
{
  using _Base = QDialog;
  Q_OBJECT
public:
  explicit DlgIncomingCall(const QString& callerInfo, QWidget *parent = 0);
  virtual ~DlgIncomingCall();

private:
  // Disable copying
  DlgIncomingCall(const DlgIncomingCall&) = delete;
  DlgIncomingCall& operator=(const DlgIncomingCall&) = delete;

  Ui::DlgIncomingCall *ui;
};

#endif // DLGINCOMINGCALL_H
