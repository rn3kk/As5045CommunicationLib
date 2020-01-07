#include <QCoreApplication>
#include <QThread>
#include <QLoggingCategory>
#include "DataExchange.h"
#include "Encoder.h"
#include "EncoderMonitor.h"

QLoggingCategory encMon("EncoderMonitor");
EncoderMonitor::EncoderMonitor():
  m_terminate(false)
{

}

void EncoderMonitor::process()
{
//  const QVector<Encoder*>& encoderList = Settings::getInstance()->getEncoderList();
//  if(encoderList.count() == 0)
//    emit finished();

//  while(!m_terminate)
//  {
//    foreach (const Encoder* e, encoderList)
//    {
//      e->sendAzInfoRequest();
//      thread()->msleep(300);
//      QCoreApplication::processEvents(QEventLoop::AllEvents);
//    }
//  }
//  emit finished();
}

void EncoderMonitor::setTerminate()
{
  qDebug(encMon) << "EncoderMonitor receive set terminate signal";
  m_terminate = true;
}

