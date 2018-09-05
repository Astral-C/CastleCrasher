#include "castlevaniarom.h"

CastlevaniaRom::CastlevaniaRom(){}

///
/// \todo Clean this up, maybe something less hacky?
///

CastlevaniaRom::CastlevaniaRom(QString path){
    bStream::CFileStream rom(path.toStdString(), bStream::Endianess::Little);
    CastlevaniaMap curMap;
    //So far as I know this isn't an isuse because insert should copy.
    curMap.init(128, 6, 0x1001A, "Entrance", rom);
    levels.insert("Level 1", curMap);
    curMap.clear();

    curMap.init(120, 8, 0x10865, "lvl2", rom);
    levels.insert("Level 2", curMap);
    curMap.clear();
}
