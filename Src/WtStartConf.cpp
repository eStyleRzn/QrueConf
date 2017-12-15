#include "WtStartConf.h"

#include "VideoConfProvider.h"
#include "ui_WtStartConf.h"
#include "DlgContacts.h"

//======================================================================================================================
WtStartConf::WtStartConf(VideoConfProvider& parent)
  : QWidget(&parent)
  , ui(new Ui::WtStartConf)
  , wtVideo_(parent)
{
  ui->setupUi(this);
  ui->btnStart->setEnabled(false);
  ui->btnStop->setEnabled(false);
  ui->btnAddressBook->setEnabled(false);
  ui->editPeerID->setEnabled(false);

  connect(ui->btnStart, &QAbstractButton::clicked, [this](){
    wtVideo_.startCall(ui->editPeerID->text());
  });

  connect(ui->btnStop, &QAbstractButton::clicked, [this](){
    wtVideo_.stopCall();
  });

  connect(ui->btnAddressBook, &QAbstractButton::clicked, [this](){
    DlgContacts dlg(wtVideo_);
    if (QDialog::Accepted == dlg.exec())
      ui->editPeerID->setText(dlg.selectedContactID().toString());
  });

  connect(&wtVideo_, &VideoConfProvider::onLoginSucceded, [this]()
  {
    ui->btnStart->setEnabled(true);
    ui->btnAddressBook->setEnabled(true);
    ui->editPeerID->setEnabled(true);
  });

  connect(&wtVideo_, &VideoConfProvider::onLogout, [this]()
  {
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(false);
    ui->btnAddressBook->setEnabled(false);
    ui->editPeerID->setEnabled(false);
  });

  connect(&wtVideo_, &VideoConfProvider::onConfStarted, [this]()
  {
    ui->btnStop->setEnabled(true);
    ui->btnStart->setEnabled(false);
    ui->editPeerID->setEnabled(false);
  });

  connect(&wtVideo_, &VideoConfProvider::onConfStopped, [this]()
  {
    ui->btnStop->setEnabled(false);
  });
}

//----------------------------------------------------------------------------------------------------------------------
WtStartConf::~WtStartConf()
{
  delete ui;
}
