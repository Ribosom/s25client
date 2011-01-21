// $Id: iwBuildingProductivities.h 6582 2010-07-16 11:23:35Z FloSoft $
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
#ifndef iwBUILDINGPRODUCTIVITIES_H_
#define iwBUILDINGPRODUCTIVITIES_H_

#include "IngameWindow.h"

/// Fenster, welches die Anzahl aller Geb�ude und der Baustellena auflistet
class iwBuildingProductivities : public IngameWindow
{
	/// Prozentzahlen der einzelnen Geb�ude
	std::vector<unsigned short> percents;

public:

	/// Konstruktor von @p iwMilitary.
	iwBuildingProductivities();

private:

	/// Aktualisieren der Prozente
	void UpdatePercents();

	/// Produktivit�ts-Progressbars aktualisieren
	void Msg_PaintAfter();

};


#endif //!iwBUILDINGPRODUCTIVITIES_H_
