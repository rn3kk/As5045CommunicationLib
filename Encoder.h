#ifndef REMOTEENCODER_H
#define REMOTEENCODER_H

#include <QString>
#include "As5045CommunicationLib_global.h"

struct AS5045COMMUNICATIONLIB_EXPORT EncoderData //data received from encoder
{
  EncoderData(unsigned char address, float deg, bool magnetIsOk, bool dataIsValid)
  {
    this->deg = deg;
    this->magnetIsOk = magnetIsOk;
    this->dataIsValid = dataIsValid;
    this->address = address;
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
    address = 0;
  }

  float deg;
  bool magnetIsOk;
  bool dataIsValid;
  unsigned char address;
};

class AS5045COMMUNICATIONLIB_EXPORT Encoder
{
public:
  Encoder();
  Encoder(const QString& name, const unsigned char addressAS5045, int angleShift):
    m_name(name),
    m_address(addressAS5045),
    m_angleShift(angleShift)
  {
    m_request = createRequest();
  }

  QString name() const;
  unsigned int getAddress() const;
  int getAngleShift() const;
  const QByteArray& getRequestText() const;

private:
  QByteArray createRequest() const;

private:
  QString m_name;
  unsigned char m_address;
  QByteArray m_request; //request to as5045 module for get degress
  int m_angleShift;
};

#endif // REMOTEENCODER_H
