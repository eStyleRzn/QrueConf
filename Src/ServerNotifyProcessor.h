#ifndef SERVERNOTIFYPROCESSOR_H
#define SERVERNOTIFYPROCESSOR_H

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QJsonValue>
#include <QMetaEnum>

//======================================================================================================================
// TODO Place class description here
class ServerNotifyProcessor : public QObject
{
  using _Base = QObject;
  Q_OBJECT
public:
  // ITrueConfCallX Interface functions enumeration
  enum class EnumICallX
  {
    getAbook,
    getMonitorsInfo
  };
  Q_ENUM(EnumICallX)

  enum class EnumCallXAttrs { ok, abook, event, peerId, peerDn, monitors };
  Q_ENUM(EnumCallXAttrs)

  template<typename T>
  static  const char* enumStrVal(const T value)
  {
    return QMetaEnum::fromType<T>().valueToKey(static_cast<int>(value));
  }

  static const QVector<QString> EnumCallXConfModes;

  static void incomingCall(const QString& data, QString& callerID, QString& callerInfo);
  static void getAbook(const QString& input, QJsonArray& output);
  static void getMonitorsInfo(const QString& input, QJsonArray& output);

private:
  static bool validateInput(const QString& data, QJsonObject& out);

  // Disable object creation. At the moment we do not havr to  instantiate this class
  ServerNotifyProcessor(QObject* parent = 0);
  virtual ~ServerNotifyProcessor() final {}

  // Disable copying
  ServerNotifyProcessor(const ServerNotifyProcessor&) = delete;
  ServerNotifyProcessor& operator=(const ServerNotifyProcessor&) = delete;
};

#endif // SERVERNOTIFYPROCESSOR_H
