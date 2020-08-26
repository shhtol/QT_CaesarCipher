#include "caesarcipherdevice.h"

CaesarCipherDevice::CaesarCipherDevice(QObject *parent) : QIODevice(parent) {
    m_key = 0;
    m_device = 0;
}

bool CaesarCipherDevice::open(OpenMode mode) {
    if(!baseDevice())
        return false;
    if(baseDevice()->openMode() != mode)
        return false;

    return QIODevice::open(mode);
}
qint64 CaesarCipherDevice::writeData(const char *data, qint64 len) {
    QByteArray ba(data, len);
    for(int i=0;i<len;++i)
        ba.data()[i] += m_key;
    int written = m_device->write(ba);
    emit bytesWritten(written);
    return written;
}

qint64 CaesarCipherDevice::readData(char *data, qint64 maxlen) {
    QByteArray baseData = m_device->read(maxlen);
    const int s = baseData.size();
    for(int i=0;i<s;++i)
        data[i] = baseData[i]-m_key;
    return s;
}
