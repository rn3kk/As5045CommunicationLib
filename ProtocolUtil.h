#ifndef PROTOCOLUTIL_H
#define PROTOCOLUTIL_H

#include <QByteArray>
#include <QChar>

struct EncoderData
{
  EncoderData(QChar address, float deg, bool magnetIsOk, bool dataIsValid)
  {
    this->deg = deg;    
    this->magnetIsOk = magnetIsOk;
    this->dataIsValid = dataIsValid;
    this->m_address = address;
  }
  EncoderData(const EncoderData& data)
  {
    deg=data.deg;
    magnetIsOk=data.magnetIsOk;
    dataIsValid=data.dataIsValid;
  }

  EncoderData()
  {
    deg=-1;
    magnetIsOk=false;
    dataIsValid=false;
  }

  float deg;
  bool magnetIsOk;
  bool dataIsValid;
  QChar m_address;
};

class ProtocolUtil
{
public:
  ProtocolUtil();  

  EncoderData getEncoderData(const QByteArray& data);

  static unsigned char createCrc(const unsigned char datalen, const unsigned char address, const unsigned char data1, const unsigned char data2, const unsigned char data3);

  private:
    int getAngle(int currentAngle, int angleShift);
};

#endif // PROTOCOLUTIL_H
