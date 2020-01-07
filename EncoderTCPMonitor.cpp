#include <QCoreApplication>
#include <QThread>
#include <QLoggingCategory>
#include <QTimerEvent>
#include "EncoderTCPMonitor.h"
#include "ProtocolUtil.h"

QLoggingCategory encMon("EncoderTCPMonitor");

EncoderTCPMonitor::EncoderTCPMonitor(const QString &host, quint16 port):
  m_radioHost(host),
  m_radioPort(port)
{
  //connect(m_socket, &QTcpSocket::readyRead, this, &EncoderTCPMonitor::readData, Qt::QueuedConnection);
  connect(m_socket, &QTcpSocket::connected, this, &EncoderTCPMonitor::isConnected, Qt::QueuedConnection);
  connect(m_socket, &QTcpSocket::disconnected, this, &EncoderTCPMonitor::isDisconected, Qt::QueuedConnection);
  connect(m_socket, &QTcpSocket::stateChanged, this, &EncoderTCPMonitor::socketChangeState, Qt::QueuedConnection);
  connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &EncoderTCPMonitor::socketError, Qt::QueuedConnection);
  connect(m_socket, &QTcpSocket::bytesWritten, this, &EncoderTCPMonitor::writen, Qt::QueuedConnection);
  m_socket->connectToHost(m_radioHost, m_radioPort);
}

void EncoderTCPMonitor::isConnected()
{
  qCDebug(encMon) << "Connect to host";
  startTimer(100);
}

void EncoderTCPMonitor::isDisconected()
{
  qCDebug(encMon) << "Disconnect from host";
}

void EncoderTCPMonitor::readData()
{
  qint64 bytes = m_socket->bytesAvailable();
  QByteArray array = m_socket->read(bytes);
  qCDebug(encMon) << "Read from socket " << bytes;

  //emit radioFrequency(array.toUInt());
  // emit radioFrequency(7100000);
}

void EncoderTCPMonitor::socketChangeState(QAbstractSocket::SocketState socketState)
{
  qDebug(encMon) << "Socket change state to " << socketState;
}

void EncoderTCPMonitor::socketError(QAbstractSocket::SocketError error)
{
  switch (error)
  {
  case QAbstractSocket::AddressInUseError:
    qCCritical(encMon) <<  "SOCKET ERROR: Address is already in use";
    break;
  case QAbstractSocket::ConnectionRefusedError:
    qCCritical(encMon) <<  "SOCKET ERROR: Connection refused";
    break;
  case QAbstractSocket::HostNotFoundError:
    qCCritical(encMon) <<  "SOCKET ERROR: Host not found";
    break;
  case QAbstractSocket::RemoteHostClosedError:
    qCCritical(encMon) <<  "SOCKET ERROR: Remote host closed";
    break;
  }

  m_socket->abort();
  m_socket->close();
  thread()->sleep(1);
  m_socket->connectToHost(m_radioHost, m_radioPort);
}

void EncoderTCPMonitor::writen(qint64 bytes)
{
  qCDebug(encMon) << "Write to socket " << bytes << " bytes";
}

void EncoderTCPMonitor::timerEvent(QTimerEvent *event)
{
  killTimer(event->timerId());

  if(m_socket== nullptr)
    return;

  for(Encoder enc: m_encoderList)
  {
    const QByteArray request = enc.getRequestText();
    if(m_socket->state() == QTcpSocket::ConnectedState)
    {
      m_socket->write(request, request.length());
      if(m_socket->waitForBytesWritten())
      {
        if(m_socket->waitForReadyRead())
        {
          qint64 bytes = m_socket->bytesAvailable();
          QByteArray array = m_socket->read(bytes);
          qCDebug(encMon) << "Read from socket " << bytes;
          EncoderData ed;
          if(ProtocolUtil::getEncoderData(ed, array))
          {
            Q_EMIT encoderData(ed);
          }
        }
        else
          qCCritical(encMon) << " Timeoute read data from socket";
      }
      else
        qCCritical(encMon) << " Timeoute write data to socket";
    }
    qApp->processEvents(QEventLoop::AllEvents, 20);
  }

  startTimer(100);
}
