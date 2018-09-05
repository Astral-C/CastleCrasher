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
            CastlevaniaTile *tile = new CastlevaniaTile();
            tile->tileType = tType;
            tile->setPos((x*32), (y*32));
            tile->setFlag(QGraphicsItem::ItemIsSelectable, true);
            render.addItem(tile);
        }
    }

    rom.seek(pos);
}

void CastlevaniaMap::loadGraphics(){
    QList<QGraphicsItem*> tiles = render.items(Qt::SortOrder::AscendingOrder);
    for(auto tile : tiles){
        CastlevaniaTile* t = qgraphicsitem_cast<CastlevaniaTile*>(tile);
        QString filename = QString::number(t->tileType, 16).toUpper().prepend(tilePth).append(".png");
        t->setPixmap(QPixmap(filename));
    }
}

void CastlevaniaMap::clearGraphics(){
    QList<QGraphicsItem*> tiles = render.items(Qt::SortOrder::AscendingOrder);
    for(auto tile : tiles){
        CastlevaniaTile* t = qgraphicsitem_cast<CastlevaniaTile*>(tile);
        t->setPixmap(QPixmap()); //set to empty pixmap. Will discard of previous pixmap?
    }
}

void CastlevaniaMap::save(bStream::CFileStream& rom){
    rom.seek(mapOffset);
    QList<QGraphicsItem*> tiles = render.items(Qt::SortOrder::AscendingOrder);
    for(auto tile : tiles){
        CastlevaniaTile* t = qgraphicsitem_cast<CastlevaniaTile*>(tile);
        rom.writeUInt8(t->tileType);
    }
}

void CastlevaniaMap::clear(){
    mapWidth = 0;
    mapHeight = 0;
    name = "";
    mapOffset = 0;
    tilePth = "";
    render.clear();
}

CastlevaniaTile::CastlevaniaTile(QString img)
{
    //move to something else to load the pixmaps?
    //setPixmap(img);
}
