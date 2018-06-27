#include "DlgShareScreen.h"
#include "VideoConfProvider.h"

#include <QJsonObject>

//======================================================================================================================
DlgShareScreen::DlgShareScreen(QWidget* parent, VideoConfProvider* video)
  : _Base(parent)
  , wtVideo_(video)
{
  ui_.setupUi(this);

  connect(video, SIGNAL(onGetMonitorsInfo(const QSharedPointer<QJsonArray>&)),
          this, SLOT(onMonitors(const QSharedPointer<QJsonArray>&)));
  connect(ui_.cmbShareMode, SIGNAL(currentIndexChanged(int)), this, SLOT(onModeChanged(int)));

  wtVideo_->getMonitorsInfo();
}

//----------------------------------------------------------------------------------------------------------------------
DlgShareScreen::~DlgShareScreen()
{
  wtVideo_->stopScreenCapture();
}

//----------------------------------------------------------------------------------------------------------------------
void DlgShareScreen::onModeChanged(int index)
{
  const auto screenIndex = ui_.cmbShareMode->itemData(index).toInt() + 1;
  wtVideo_->startScreenCapture(QString::number(screenIndex));

//  switch (index) {
//  case 1:
//    break;
//  default:
//    wtVideo_->startScreenCapture("1");
//    wtVideo_->getSelfieBroadcast();
//    break;
//  }
}

//----------------------------------------------------------------------------------------------------------------------
void DlgShareScreen::onMonitors(const QSharedPointer<QJsonArray>& data)
{
  for (auto&& item : *data)
  {
    if (item.isObject())
    {
      auto name = item.toObject().value("name").toString();
      const auto primary = item.toObject().value("primary").toBool();
      const auto index = item.toObject().value("index").toInt();

      name += primary ? " (Primary)" : " (Secondary)";
      ui_.cmbShareMode->addItem(name, index);
    }
  }
}
