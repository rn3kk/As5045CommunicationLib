#ifndef PROTOCOLUTIL_H
#define PROTOCOLUTIL_H

#include <QByteArray>
#include <QChar>
#include "Encoder.h"

class ProtocolUtil
{
public:
  ProtocolUtil();
  static bool getEncoderData(EncoderData& encoderData, const QByteArray& data);

  static unsigned char createCrc(const unsigned char datalen, const unsigned char address, const unsigned char data1, const unsigned char data2, const unsigned char data3);

  private:
    int getAngle(int currentAngle, int angleShift);
};

#endif // PROTOCOLUTIL_H
