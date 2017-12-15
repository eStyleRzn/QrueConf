#include "DlgContacts.h"

#include <QJsonObject>

#include "ui_DlgContacts.h"
#include "VideoConfProvider.h"

//======================================================================================================================
DlgContacts::DlgContacts(VideoConfProvider& wtVideo, QWidget* parent)
  : QDialog(parent)
  , ui(new Ui::DlgContacts)
  , wtVideo_(wtVideo)
{
  ui->setupUi(this);

  connect(&wtVideo_, SIGNAL(onGetAddressBook(AddressBook::Shared)),
          this, SLOT(onGetABook(AddressBook::Shared)));

  connect(ui->listWidget, &QListWidget::itemActivated, [this](QListWidgetItem* item)
  {
    selected_ = item->data(Qt::UserRole);
    accept();
  });

  wtVideo_.getAddressBook();
}

//----------------------------------------------------------------------------------------------------------------------
DlgContacts::~DlgContacts()
{
  delete ui;
}

//----------------------------------------------------------------------------------------------------------------------
void DlgContacts::onGetABook(AddressBook::Shared data)
{
  auto contacts = data->onlineContacts();
  for (auto&& item : contacts)
  {
    if (item.isObject())
    {
      auto li = new QListWidgetItem(item.toObject().value("displayName").toString());
      li->setData(Qt::UserRole, item.toObject().value("id").toString());

      ui->listWidget->addItem(li);
    }
  }
}
