#include "DlgCreateConf.h"

#include <QJsonObject>

#include "ui_DlgCreateConf.h"

//======================================================================================================================
DlgCreateConf::DlgCreateConf(VideoConfProvider& wtVideo, QWidget* parent)
  : QDialog(parent)
  , ui(new Ui::DlgCreateConf)
  , wtVideo_(wtVideo)
{
  ui->setupUi(this);

  ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

  connect(ui->btnInclude, SIGNAL(clicked()), this, SLOT(onInclude()));
  connect(ui->btnExclude, SIGNAL(clicked()), this, SLOT(onExclude()));

  connect(ui->listAll, SIGNAL(itemActivated(QListWidgetItem*)),
          this, SLOT(onInclude()));

  connect(ui->listSelected, SIGNAL(itemActivated(QListWidgetItem*)),
          this, SLOT(onExclude()));

  connect(ui->editName, &QLineEdit::textChanged, [this]()
  {
    setOkEnabled();
  });

  wtVideo_.getAddressBook();

  connect(&wtVideo_, SIGNAL(onGetAddressBook(AddressBook::Shared)), this, SLOT(onGetABook(AddressBook::Shared)));

  connect(this, &QDialog::accepted, [this]()
  {
    QStringList selected;
    for (auto i = 0; i < ui->listSelected->count(); ++i)
    {
      selected.push_back(ui->listSelected->item(i)->data(Qt::UserRole).toString());
    }

    if (selected.size())
      wtVideo_.createConference(ui->editName->text(), 0, selected);
  });
}

//----------------------------------------------------------------------------------------------------------------------
DlgCreateConf::~DlgCreateConf()
{
  delete ui;
}

//----------------------------------------------------------------------------------------------------------------------
void DlgCreateConf::onInclude()
{
  if (auto current = ui->listAll->currentItem())
  {
    auto row = ui->listAll->row(current);
    ui->listSelected->addItem(ui->listAll->takeItem(row));

    setOkEnabled();
  }
}

//----------------------------------------------------------------------------------------------------------------------
void DlgCreateConf::onExclude()
{
  if (auto current = ui->listSelected->currentItem())
  {
    auto row = ui->listSelected->row(current);
    ui->listAll->addItem(ui->listSelected->takeItem(row));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ui->listSelected->count());
  }
}

//----------------------------------------------------------------------------------------------------------------------
void DlgCreateConf::onGetABook(AddressBook::Shared data)
{
  ui->listAll->clear();

  // Populate all addresses
  for (auto&& item : data->onlineContacts())
  {
    if (item.isObject())
    {
      auto li = new QListWidgetItem(item.toObject().value("displayName").toString());
      li->setData(Qt::UserRole, item.toObject().value("id").toString());

      ui->listAll->addItem(li);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
void DlgCreateConf::setOkEnabled()
{
  bool enabled = ui->listSelected->count() && ui->editName->text().size();
  ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(enabled);
}
