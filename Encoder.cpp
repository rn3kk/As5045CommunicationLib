#include "CommonConst.h"
#include "ProtocolUtil.h"
#include "Encoder.h"

Encoder::Encoder()
{

}

QString Encoder::name() const
{
  return m_name;
}

QByteArray Encoder::createRequest() const
{
  unsigned char address = m_address;
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
  if(m_address == 0 ) return 0;
  return m_address;
}

const QByteArray &Encoder::getRequestText() const
{
  return m_request;
}
