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
    name = areaName;
    mapOffset = offset;
    tilePth = QString(":/levels/" + areaName + "/");

    long pos = rom.tell();
    rom.seek(offset);
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            uint8_t tType = rom.readUInt8();
            QString filename = QString::number(tType, 16).toUpper().prepend(tilePth).append(".png");
            CastlevaniaTile *tile = new CastlevaniaTile(filename);
            tile->tileType = tType;
            tile->setPos((x*32), (y*32));
            tile->setFlag(QGraphicsItem::ItemIsSelectable, true);
            render.addItem(tile);
        }
    }

    rom.seek(pos);
}

void CastlevaniaMap::save(bStream::CFileStream& rom){
    rom.seek(mapOffset);
    QList<QGraphicsItem*> tiles = render.items(Qt::SortOrder::AscendingOrder);
    for(auto tile : tiles){
        CastlevaniaTile* t = qgraphicsitem_cast<CastlevaniaTile*>(tile);
        rom.writeUInt8(t->tileType);
    }
}

CastlevaniaTile::CastlevaniaTile(QString img)
{
    setPixmap(img);
}
