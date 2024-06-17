#ifndef YUVDECODER_H
#define YUVDECODER_H

#include <QImage>

class YUVDecoder
{
public:
    QImage convert2RGB(const QByteArray& rawData, int width, int height);
    
    void convertFormula(int Y, int U, int V, int &R, int &G, int &B);
};

#endif