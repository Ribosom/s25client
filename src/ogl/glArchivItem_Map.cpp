// Copyright (c) 2005 - 2015 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.

///////////////////////////////////////////////////////////////////////////////
// Header
#include "defines.h"
#include "glArchivItem_Map.h"

#include "Settings.h"

#include "GameClient.h"
#include "SerializedGameData.h"
#include "../libsiedler2/src/ArchivItem_Raw.h"
#include "../libsiedler2/src/types.h"
#include "glAllocator.h"

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#if defined _WIN32 && defined _DEBUG && defined _MSC_VER
#define new new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
/**
 *  Konstruktor von @p glArchivItem_Map.
 *
 *  @author FloSoft
 */
glArchivItem_Map::glArchivItem_Map()
    : ArchivItem_Map()
{
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  Destruktor von @p glArchivItem_Map.
 *
 *  @author FloSoft
 */
glArchivItem_Map::~glArchivItem_Map()
{
}


///////////////////////////////////////////////////////////////////////////////
/**
 *  lädt die Mapdaten aus einer Datei.
 *
 *  @param[in] file Dateihandle der Datei
 *  @param[in] only_header Soll nur der Header gelesen werden?
 *
 *  @return liefert Null bei Erfolg, ungleich Null bei Fehler
 *
 *  @author FloSoft
 */
int glArchivItem_Map::load(std::istream& file, bool only_header)
{
    if(libsiedler2::ArchivItem_Map::load(file, only_header) != 0)
        return 1;

    alloc_inc(2);

    header = dynamic_cast<const libsiedler2::ArchivItem_Map_Header*>(get(0));
    assert(header);

    if(only_header)
        return 0;

    /* TODO: Not required anymore? Then remove it
    // Noch nicht am Ende der Datei?
    unsigned curPos = 0, fileSize = 0;
    if(!feof(file))
    {
      // Gucken, wieviel noch danach kommt
      curPos = ftell(file);
      fseek(file, 0L, SEEK_END);
      fileSize = ftell(file);
      fseek(file, i, SEEK_SET);
    }

    if((unsigned int)(fileSize - curPos) > (unsigned int)(header->getWidth() * header->getHeight() * 2))
    {
        // Wenn noch Platz ist, restliches Zeug noch auslesen
        // @todo: Shouldn't we use libsiedler2::allocator?
        libsiedler2::ArchivItem_Raw* reservations = dynamic_cast<libsiedler2::ArchivItem_Raw*>(GlAllocator().create(libsiedler2::BOBTYPE_RAW));
        if(reservations->load(file, header->getWidth() * header->getHeight()) != 0){
            delete reservations;
            return 2;
        }
        set(MAP_RESERVATIONS, reservations);

        libsiedler2::ArchivItem_Raw* owner = dynamic_cast<libsiedler2::ArchivItem_Raw*>(GlAllocator().create(libsiedler2::BOBTYPE_RAW));
        if(owner->load(file, header->getWidth() * header->getHeight()) != 0){
            delete owner;
            return 3;
        }
        set(MAP_OWNER, owner);
    }
    else*/
    {
        libsiedler2::ArchivItem_Raw* item = dynamic_cast<libsiedler2::ArchivItem_Raw*>(GlAllocator().create(libsiedler2::BOBTYPE_RAW));
        item->getData().resize(header->getWidth() * header->getHeight()); // TODO: Really required?

        set(MAP_RESERVATIONS, item);
        setC(MAP_OWNER, *item);
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  liefert einen Map-Layer zurück.
 *
 *  @param[in] type Typ des Layers.
 *
 *  @author FloSoft
 */
const std::vector<unsigned char>& glArchivItem_Map::GetLayer(MapLayer type) const
{
    const libsiedler2::ArchivItem_Raw* item = dynamic_cast<const libsiedler2::ArchivItem_Raw*>(get(type));
    assert(item);
    return item->getData();
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  liefert einen Map-Layer zurück.
 *
 *  @param[in] type Typ des Layers.
 *
 *  @author FloSoft
 */
std::vector<unsigned char>& glArchivItem_Map::GetLayer(MapLayer type)
{
    libsiedler2::ArchivItem_Raw* item = dynamic_cast<libsiedler2::ArchivItem_Raw*>(get(type));
    assert(item);
    return item->getData();
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  liefert die Mapdaten an einer bestimmten Stelle zurück.
 *
 *  @param[in] type Typ des Layers.
 *  @param[in] pos  Position in den Daten.
 *
 *  @author FloSoft
 */
unsigned char glArchivItem_Map::GetMapDataAt(MapLayer type, unsigned int pos) const
{
    return GetLayer(type)[pos];
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  setzt die Mapdaten an einer bestimmten Stelle.
 *
 *  @param[in] type  Typ des Layers.
 *  @param[in] pos   Position in den Daten.
 *  @param[in] value zu setzender Wert an der Position.
 *
 *  @author FloSoft
 */
void glArchivItem_Map::SetMapDataAt(MapLayer type, unsigned int pos, unsigned char value)
{
    GetLayer(type)[pos] = value;
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  liefert die Mapdaten an der Stelle X,Y zurück.
 *
 *  @param[in] type Typ des Layers.
 *  @param[in] x    X-Position in den Daten.
 *  @param[in] y    Y-Position in den Daten.
 *
 *  @author FloSoft
 */
unsigned char glArchivItem_Map::GetMapDataAt(MapLayer type, unsigned short x, unsigned short y) const
{
    return GetMapDataAt(type, y * header->getWidth() + x);
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  setzt die Mapdaten an der Stelle X,Y.
 *
 *  @param[in] type  Typ des Layers.
 *  @param[in] x     X-Position in den Daten.
 *  @param[in] y     Y-Position in den Daten.
 *  @param[in] value zu setzender Wert an der Position.
 *
 *  @author FloSoft
 */
void glArchivItem_Map::SetMapDataAt(MapLayer type, unsigned short x, unsigned short y, unsigned char value)
{
    SetMapDataAt(type, y * header->getWidth() + x, value);
}
