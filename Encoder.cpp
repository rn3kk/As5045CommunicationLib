#include "TcpUartModule.h"
#include "CommonConst.h"
#include "ProtocolUtil.h"
#include "Encoder.h"

Encoder::Encoder()
{

}

Encoder::Encoder(const QString &name, const QByteArray &address, int angleShift):
  m_name(name),
  m_address(address),
  m_angleShift(angleShift)
{

}

quint8 Encoder::getAngle()
{

}

QString Encoder::name() const
{
  return m_name;
}

QByteArray Encoder::getRequest() const
{
  unsigned char address = m_address.at(0);
  unsigned char length = 0x81;
  unsigned char data1 = 0x02;
  unsigned char crc = ProtocolUtil::createCrc(length, address, data1, 0x0, 0x0);

  QByteArray arr;
  arr.append(START_BYTE);
  arr.append(address);
  arr.append(length);
  arr.append(data1);
  arr.append(crc);
  arr.append(STOP_BYTE);

  return arr;
}

unsigned int Encoder::getAddress() const
{
  if(m_address.isNull() || m_address.isEmpty()) return 0;
  return m_address.at(0);
}

int Encoder::getAngleShift() const
{
  return m_angleShift;
}
