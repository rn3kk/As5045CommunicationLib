#ifndef REMOTEENCODER_H
#define REMOTEENCODER_H

#include <QString>

class DataFromEncoder
{

};

class Encoder
{
public:
  Encoder();
  Encoder(const QString& name, const QByteArray& address, int angleShift);

  quint8 getAngle();
  QString name() const;
  unsigned int getAddress() const;
  int getAngleShift() const;

private:
  QByteArray getRequest() const;

private:
  QString m_name;
  QByteArray m_address;  
  int m_angleShift;
};

#endif // REMOTEENCODER_H
