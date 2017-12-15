#include "ServerNotifyProcessor.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>

//======================================================================================================================
const QVector<QString> ServerNotifyProcessor::EnumCallXConfModes{"symmetric", "asymmetric", "role-based"};

//----------------------------------------------------------------------------------------------------------------------
void ServerNotifyProcessor::incomingCall(const QString& data, QString& callerID, QString& callerInfo)
{
  QJsonObject obj;
  if (validateInput(data, obj))
  {
    callerID = obj.value(enumStrVal<EnumCallXAttrs>(EnumCallXAttrs::peerId)).toString();
    callerInfo = obj.value(enumStrVal<EnumCallXAttrs>(EnumCallXAttrs::peerDn)).toString();
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ServerNotifyProcessor::getAbook(const QString& input, QJsonArray& output)
{
  QJsonObject obj;
  if (validateInput(input, obj))
  {
    using ICallX = EnumICallX;
    using CallXAttrs = EnumCallXAttrs;

    QJsonObject::const_iterator it;

    output = obj.find(enumStrVal<CallXAttrs>(CallXAttrs::abook)).value().toArray();
  }
}

//----------------------------------------------------------------------------------------------------------------------
ServerNotifyProcessor::ServerNotifyProcessor(QObject *parent)
  : _Base(parent)
{
}

//----------------------------------------------------------------------------------------------------------------------
bool ServerNotifyProcessor::validateInput(const QString& data, QJsonObject& out)
{
  QJsonDocument json = QJsonDocument::fromJson(data.toUtf8());

  if (json.isEmpty())
  {
    Q_ASSERT_X(false, __FUNCTION__, "Logic error");
    return false;
  }

  if (json.isObject())
  {
    // TODO avoid data coping
    out = json.object();
    return true;
  }
  else
  {
    Q_ASSERT_X(false, __FUNCTION__, "Invalid input type");
    return false;
  }
}
