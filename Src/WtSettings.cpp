#include "WtSettings.h"

#include <QDebug>

#include "VideoConfProvider.h"

//======================================================================================================================
WtSettings::WtSettings(VideoConfProvider& parent)
  : QWidget(&parent)
  , ui(new Ui::WtSettings)
  , wtVideo_(parent)
{
  ui->setupUi(this);

  ui->editHost->setText("192.168.69.147:4307");
  ui->editLogin->setText("test3");
  ui->editPassword->setText("123456aB");

  connect(ui->cmbCamera, SIGNAL(currentIndexChanged(int)), this, SLOT(onCameraChanged(int)));
  connect(ui->cmbMicrophone, SIGNAL(currentIndexChanged(int)), this, SLOT(onMicChanged(int)));
  connect(ui->cmbSpeaker, SIGNAL(currentIndexChanged(int)), this, SLOT(onSpeakerChanged(int)));

  connect(ui->btnSubmitHost, &QAbstractButton::clicked, [this]()
  {
    emit serverConnect(ui->editHost->text(), ui->editLogin->text(), ui->editPassword->text());
  });

  connect(ui->btnRestart, &QAbstractButton::clicked, [this]()
  {
    wtVideo_.restart();
  });

  populateCameras();
  populateMics();
  populateSpeakers();
}

//----------------------------------------------------------------------------------------------------------------------
WtSettings::~WtSettings()
{
  delete ui;
}

//----------------------------------------------------------------------------------------------------------------------
void WtSettings::onCameraChanged(int index)
{
  wtVideo_.setCameraByIndex(index);
}

//----------------------------------------------------------------------------------------------------------------------
void WtSettings::onMicChanged(int index)
{
  wtVideo_.setMicByIndex(index);
}

//----------------------------------------------------------------------------------------------------------------------
void WtSettings::onSpeakerChanged(int index)
{
  wtVideo_.setSpeakerByIndex(index);
}

//----------------------------------------------------------------------------------------------------------------------
void WtSettings::populateCameras()
{
  qDebug() << __FUNCTION__ << "Cameras found: " << wtVideo_.getCameraCount();

  bool set = false;
  for (int i = 0; i < wtVideo_.getCameraCount(); ++i)
  {
    set = true;
    ui->cmbCamera->addItem(wtVideo_.getCameraByIndex(i), i);
  }

  if (set)
    ui->cmbCamera->setCurrentIndex(0);
}

//----------------------------------------------------------------------------------------------------------------------
void WtSettings::populateMics()
{
  qDebug() << __FUNCTION__ << "Microphones found: " << wtVideo_.getMicCount();

  bool set = false;
  for (int i = 0; i < wtVideo_.getMicCount(); ++i)
  {
    set = true;
    ui->cmbMicrophone->addItem(wtVideo_.getMicByIndex(i), i);
  }

  if (set)
    ui->cmbMicrophone->setCurrentIndex(0);
}

//----------------------------------------------------------------------------------------------------------------------
void WtSettings::populateSpeakers()
{
  qDebug() << __FUNCTION__ << "Speakers found: " << wtVideo_.getSpeakerCount();

  bool set = false;
  for (int i = 0; i < wtVideo_.getSpeakerCount(); ++i)
  {
    set = true;
    ui->cmbSpeaker->addItem(wtVideo_.getSpeakerByIndex(i), i);
  }

  if (set)
    ui->cmbSpeaker->setCurrentIndex(0);
}

