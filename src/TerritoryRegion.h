// $Id: TerritoryRegion.h 6582 2010-07-16 11:23:35Z FloSoft $
//
// Copyright (c) 2005 - 2010 Settlers Freaks (sf-team at siedler25.org)
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

#ifndef TERRITORY_REGION_H_
#define TERRITORY_REGION_H_

/// TerritoryRegion ist ein Rechteck aus der Karte quasi "ausgeschnitten", die f�r die Berechnung bei Milit�rgeb�uden-
/// aktionen (Neubau, �bernahme, Abriss) ben�tigt wird von RecalcTerritory

class noBaseBuilding;
class GameWorldBase;

class TerritoryRegion
{
	/// Lage des Ausschnittes in der Karte
	const int x1, y1, x2, y2;
	/// Gr��e der Karte (wird aus x1,y1...) berechnet
	const unsigned short width,height;

	/// Beschreibung eines Knotenpunktes
	struct TRNode
	{
		/// Spieler-index (+1, da 0 = besitzlos!)
		unsigned char owner;
		/// Entfernung vom Milit�rgeb�ude
		unsigned char radius;
	} * nodes;
	
	const GameWorldBase * const gwb;

private:

	/// Testet einen Punkt, ob der neue Spieler ihn �bernehmen kann und �bernimmt ihn ggf.
	void TestNode( int x, int y,const unsigned char player, const unsigned char radius);
	/// Unterfunktionen von AdjustBorders, vergleicht 2 Punkte, ob sie von unterschiedlichen Spielern sind und setzt
	/// Punkt ggf. zu gar keinem Spieler, 2. Funktion wird f�r Punkte im 2er Abstand verwendet, da es dort ein bisschen anders l�uft!
	void AdjustNodes(const unsigned short x1, const unsigned short y1, const unsigned short x2, const unsigned short y2);
	void AdjustNodes2(const unsigned short x1, const unsigned short y1, const unsigned short x2, const unsigned short y2);

public:


	TerritoryRegion(const int x1, const int y1, const int x2, const int y2, const GameWorldBase * const gwb);
	~TerritoryRegion();

	/// Berechnet ein Milit�rgeb�ude mit ein
	void CalcTerritoryOfBuilding(const noBaseBuilding * const building);

	// Liefert den Besitzer eines Punktes (mit absoluten Koordinaten, werden automatisch in relative umgerechnet!)
	unsigned char GetOwner(const int x, const int y)
	{ return nodes[(y-y1)*(x2-x1)+(x-x1)].owner; }
	/// Liefert Radius mit dem der Punkt besetzt wurde
	unsigned char GetRadius(const int x, const int y) const
	{ return nodes[(y-y1)*(x2-x1)+(x-x1)].radius; }

	// Korrigiert die Grenzen (schneidet vom aktuellen Territorium immer noch die �u�eren Punkte ab f�r die Grenzpf�hle)
	void AdjustBorders();


};

#endif

