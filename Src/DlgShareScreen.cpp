#include "DlgShareScreen.h"

#include <QJsonObject>
#include <QScreen>
#include <QPushButton>
#include <QDebug>

#include "VideoConfProvider.h"
#include "ScreenshotThumb.h"

//======================================================================================================================
DlgShareScreen::DlgShareScreen(QWidget* parent, VideoConfProvider* video)
  : _Base(parent)
  , wtVideo_(video)
{
  ui_.setupUi(this);

  if (auto b = ui_.buttonBox->button(QDialogButtonBox::Ok))
  {
    b->setText(tr("Показать"));
  }

  connect(video, SIGNAL(onGetMonitorsInfo(const QSharedPointer<QJsonArray>&)),
          this, SLOT(onScreens(const QSharedPointer<QJsonArray>&)));

  wtVideo_->getMonitorsInfo();
}

//----------------------------------------------------------------------------------------------------------------------
DlgShareScreen::~DlgShareScreen()
{
//  wtVideo_->stopScreenCapture();

//  QWidgetList widgets = qApp->topLevelWidgets();
//  for (auto&& wt : widgets)
//  {
//    wt->setWindowState(Qt::WindowNoState);
//  }
}

//----------------------------------------------------------------------------------------------------------------------
int DlgShareScreen::selectedScreen() const
{
  return selectedScreen_;
}

//----------------------------------------------------------------------------------------------------------------------
void DlgShareScreen::onScreens(const QSharedPointer<QJsonArray>& data)
{
  screensInfo_ = data;

  for (int i = 0; i < screensInfo_->size(); ++i)
  {
    QJsonValueRef item = (*screensInfo_)[i];
    if (item.isObject())
    {
      auto screen = getScreen(item);

      if (screen)
      {
        auto label = new ScreenshotThumb(*screen, item.toObject().value("index").toInt(), this);
        ui_.gridLayout->addWidget(label, 0, i, 1, 1);

        connect(label, SIGNAL(clicked()), this, SLOT(onScreenThumbClicked()));
        connect(label, SIGNAL(selected(int)), this, SLOT(onScreenSelected(int)));
        connect(this, SIGNAL(selectDisplay(bool)), label, SLOT(select(bool)));

        const auto primary = item.toObject().value("primary").toBool();

        if (primary)
        {
          label->select(true);
        }
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
void DlgShareScreen::onScreenThumbClicked()
{
  // Unselect all the displays
  emit selectDisplay(false);

  if (auto label = dynamic_cast<ScreenshotThumb*>(sender()))
  {
    const bool ok = label->select(true);
    Q_ASSERT_X(ok, __FUNCTION__, "Logic error");
  }
}

//----------------------------------------------------------------------------------------------------------------------
void DlgShareScreen::onScreenSelected(int s)
{
  selectedScreen_ = s;
}

//----------------------------------------------------------------------------------------------------------------------
QScreen* DlgShareScreen::getScreen(const QJsonValueRef& item) const
{
  const auto monitorGeometry = item.toObject().value("geomMonitor").toObject();
  const auto itemX = monitorGeometry.value("x").toInt();
  const auto itemY = monitorGeometry.value("y").toInt();

  for (auto&& screen : qApp->screens())
  {
    // qDebug() << __FUNCTION__ << screen->virtualGeometry() << screen->geometry();

    auto screenX = screen->geometry().x();
    auto screenY = screen->geometry().y();
    if ( itemX == screenX && itemY == screenY)
    {
      return screen;
    }
  }

//  // Return at least primary monitor
//  const auto primary = item.toObject().value("primary").toBool();

//  if (primary)
//    return qApp->primaryScreen();

  return nullptr;
}
