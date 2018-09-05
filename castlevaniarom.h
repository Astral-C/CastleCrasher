#include <castlevaniatile.h>
#ifndef CASTLEVANIAROM_H
#define CASTLEVANIAROM_H

///
/// \brief The CastlevaniaRom class
/// The castlevania rom class is just used to simplify the loading of levels by loading them
/// into a QMap with a string name and a CastlevaniaMap
/// TODO: loading all of the levels into memory at once is probably a bad idea graphics wise, init graphics
/// through different function?
///

class CastlevaniaRom
{
public:

    QMap<QString, CastlevaniaMap> levels;
    CastlevaniaRom(QString path);
    CastlevaniaRom();
};

#endif // CASTLEVANIAROM_H
