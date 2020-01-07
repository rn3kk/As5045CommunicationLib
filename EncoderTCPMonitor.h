#ifndef ENCODERMONITOR_H
#define ENCODERMONITOR_H

#include <QObject>
#include <QVector>
#include <QAbstractSocket>
#include <QTcpSocket>
#include "Encoder.h"

class EncoderTCPMonitor : public QObject
{
  Q_OBJECT
public:
  EncoderTCPMonitor(const QString& host, quint16 port);

public Q_SLOTS:
  void isConnected();
  void isDisconected();
  void readData();
  void socketChangeState(QAbstractSocket::SocketState socketState);
  void socketError(QAbstractSocket::SocketError error);
  void writen(qint64 bytes);

Q_SIGNALS:
  void encoderData(EncoderData encoderData);
  void encoderStatus(void*);
  void finished();

private:
  void timerEvent(QTimerEvent *event) override;

private:
  QVector<Encoder> m_encoderList;
  const QString m_radioHost;
  quint16 m_radioPort;
  QTcpSocket* m_socket;
};

#endif // ENCODERMONITOR_H
