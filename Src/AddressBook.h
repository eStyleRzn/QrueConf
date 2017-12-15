#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QObject>
#include <QJsonArray>
#include <QSharedPointer>

//======================================================================================================================
// TODO Place class description here
class AddressBook : public QObject
{
  using _Base = QObject;
  Q_OBJECT
public:
  using Shared = QSharedPointer<AddressBook>;

  explicit AddressBook(const QJsonArray&, QObject* parent = 0);
  virtual ~AddressBook();

public slots:
  QJsonArray onlineContacts();

signals:

private:
  // Disable copying
  AddressBook(const AddressBook&) = delete;
  AddressBook& operator=(const AddressBook&) = delete;

  QJsonArray data_;
};

#endif // ADDRESSBOOK_H
