#ifndef DLGCONTACTS_H
#define DLGCONTACTS_H

#include <QDialog>
#include <QVariant>
#include <QJsonArray>

#include "VideoConfProvider.h"

namespace Ui {
class DlgContacts;
}

//======================================================================================================================
class DlgContacts : public QDialog
{
  Q_OBJECT
  using _Base = QDialog;
public:
  explicit DlgContacts(VideoConfProvider&, QWidget* parent = nullptr);
  virtual ~DlgContacts();

  QVariant selectedContactID() { return selected_; }

private slots:
  void onGetABook(AddressBook::Shared);

private:
  // Disable copying
  DlgContacts(const DlgContacts&) = delete;
  DlgContacts& operator=(const DlgContacts&) = delete;

  Ui::DlgContacts *ui;
  QVariant selected_;
  VideoConfProvider& wtVideo_;
};

#endif // DLGCONTACTS_H
