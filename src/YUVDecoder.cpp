#include "YUVDecoder.h"

QImage YUVDecoder::convert2RGB(const QByteArray& yuvData, int width, int height)
{
    QImage image(width, height, QImage::Format_RGB32);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x += 2)
        {
            int index = y * width * 2 + x * 2;
            
            int Y0 = static_cast<unsigned char>(yuvData[index]);
            int U = static_cast<unsigned char>(yuvData[index + 1]);
            int Y1 = static_cast<unsigned char>(yuvData[index + 2]);
            int V = static_cast<unsigned char>(yuvData[index + 3]);

            int R1, G1, B1;
            int R2, G2, B2;
            
            convertFormula(Y0, U, V, R1, G1, B1);   // 첫 번째 픽셀(Y0, U, V)
            convertFormula(Y1, U, V, R2, G2, B2);   // 두 번째 픽셀(Y1, U, V)
            
            image.setPixel(x, y, qRgb(R1, G1, B1));
            image.setPixel(x + 1, y, qRgb(R2, G2, B2));
        }
    }

    return image;
}

void YUVDecoder::convertFormula(int Y, int U, int V, int &R, int &G, int &B)    // YUV to RGB888 공식
{
    R = qBound(0, ((298 * (Y - 16) + 409 * (V - 128) + 128) >> 8), 255);
    G = qBound(0, ((298 * (Y - 16) - 100 * (U - 128) - 208 * (V - 128) + 128) >> 8), 255);
    B = qBound(0, ((298 * (Y - 16) + 516 * (U - 128) + 128) >> 8), 255);
}