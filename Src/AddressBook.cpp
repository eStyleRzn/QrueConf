#include "AddressBook.h"

#include <QJsonObject>
#include <QDebug>

#include "ServerNotifyProcessor.h"

//======================================================================================================================
AddressBook::AddressBook(const QJsonArray& data, QObject* parent)
  : _Base(parent)
  , data_(data)
{
}

//----------------------------------------------------------------------------------------------------------------------
AddressBook::~AddressBook()
{
  qDebug() << __FUNCTION__;
}

//----------------------------------------------------------------------------------------------------------------------
QJsonArray AddressBook::onlineContacts()
{
  QJsonArray res;
  for (auto&& item : data_)
  {
      if (item.isObject())
      {
        auto obj = item.toObject();
        auto d = obj.find("status");

//        qDebug() << __FUNCTION__ << obj;

        if (obj.end() != d && d.value().toInt() > 0)
        {
          QJsonObject r;
          r.insert("id", item.toObject().value(ServerNotifyProcessor::enumStrVal(ServerNotifyProcessor::EnumCallXAttrs::peerId)));
          r.insert("displayName", item.toObject().value(ServerNotifyProcessor::enumStrVal(ServerNotifyProcessor::EnumCallXAttrs::peerDn)));
          res.push_back(r);
        }
      }
  }

  return res;
}
