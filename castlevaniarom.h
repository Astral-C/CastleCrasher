#include <castlevaniatile.h>
#ifndef CASTLEVANIAROM_H
#define CASTLEVANIAROM_H

//TODO: setup rom class to hold static values for level offsets

class CastlevaniaRom
{
public:
    QMap<qint8, QPixmap> metatiles;
    QMap<qint32, QString> levels;
    CastlevaniaRom();
};

#endif // CASTLEVANIAROM_H
