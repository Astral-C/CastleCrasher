#include "castlevaniatile.h"
#include <iostream>

CastlevaniaMap::CastlevaniaMap(){}
CastlevaniaTile::CastlevaniaTile(){}

//area name is set for now
//todo: fix this and/or the ui
void CastlevaniaMap::init(int w, int h, int offset, QString areaName, bStream::CFileStream& rom)
{
    mapWidth = w;
    mapHeight = h;

    long pos = rom.tell();
    rom.seek(offset);
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            uint8_t tileType = rom.readUInt8();
            QString filename = QString::number(tileType, 16).toUpper().prepend(":/levels/" + areaName + "/").append(".png");
            CastlevaniaTile *tile = new CastlevaniaTile(tileType, filename);
            tile->setPos((x*32), (y*32));
            tile->setData(0, tile->pixmap()); //this is gross.
            tile->setFlag(QGraphicsItem::ItemIsSelectable, true);
            render.addItem(tile);
        }
    }

    rom.seek(pos);
}

CastlevaniaTile::CastlevaniaTile(uint8_t type, QString img)
{
    id = type;
    setPixmap(img);
}
