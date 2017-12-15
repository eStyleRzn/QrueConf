#include "DlgIncomingCall.h"
#include "ui_DlgIncomingCall.h"

//======================================================================================================================
DlgIncomingCall::DlgIncomingCall(const QString& callerInfo, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DlgIncomingCall)
{
  ui->setupUi(this);
  ui->lblCaller->setText(callerInfo);
}

//======================================================================================================================
DlgIncomingCall::~DlgIncomingCall()
{
  delete ui;
}
