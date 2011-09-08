// $Id: iwPleaseWait.h 7521 2011-09-08 20:45:55Z FloSoft $
//
// Copyright (c) 2005 - 2011 Settlers Freaks (sf-team at siedler25.org)
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
#ifndef iwPLEASEWAIT_H_INCLUDED
#define iwPLEASEWAIT_H_INCLUDED

#pragma once

#include "IngameWindow.h"

/// Bitte-Warten Fenster, welches aufgerufen wird, nachdem der Server gestartet wurde bis zum Weitergehen
class iwPleaseWait : public IngameWindow
{
public:
	/// Konstruktor von @p iwPleaseWait.
	iwPleaseWait(void);
	/// Destruktor von @p iwPleaseWait.
	~iwPleaseWait();
};

#endif // !iwPLEASEWAIT_H_INCLUDED
