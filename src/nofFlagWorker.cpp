// $Id: nofFlagWorker.cpp 7521 2011-09-08 20:45:55Z FloSoft $
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

///////////////////////////////////////////////////////////////////////////////
// Header
#include "main.h"
#include "nofFlagWorker.h"

#include "noFlag.h"
#include "GameWorld.h"
#include "GameClientPlayer.h"
#include "SerializedGameData.h"
#include "nobBaseWarehouse.h"

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#if defined _WIN32 && defined _DEBUG && defined _MSC_VER
	#define new new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

nofFlagWorker::nofFlagWorker(const Job job,const unsigned short x, const unsigned short y,const unsigned char player,noRoadNode * goal)
: noFigure(job,x,y,player,goal), flag(0), state(STATE_FIGUREWORK)
{
	// Flagge als Ziel, dann arbeiten wir auch, ansonsten kanns aber auch nur ein Lagerhaus oder Null sein, wenn ein
	// Lagerhaus abgerissen wurde oder ausgelagert wurde etc., dann auch den nicht als Flag-Worker registrieren
	if(goal)
	{
		if(goal->GetGOT() == GOT_FLAG)
		{
			this->flag = static_cast<noFlag*>(goal);
			gwg->GetPlayer(player)->RegisterFlagWorker(this);
		}
		else
			this->flag = 0;
	}
	else
		this->flag = 0;
}

nofFlagWorker::nofFlagWorker(SerializedGameData * sgd, const unsigned obj_id)
 : noFigure(sgd,obj_id), flag(sgd->PopObject<noFlag>(GOT_FLAG)), state(State(sgd->PopUnsignedChar()))
{
}

void nofFlagWorker::Serialize_nofFlagWorker(SerializedGameData * sgd) const
{
	Serialize_noFigure(sgd);

	sgd->PushObject(flag,true);
	sgd->PushUnsignedChar(static_cast<unsigned char>(state));
}

void nofFlagWorker::Destroy_nofFlagWorker()
{ 
	Destroy_noFigure();
}

void nofFlagWorker::AbrogateWorkplace()
{
	flag = 0;
	/// uns entfernen, da wir wieder umdrehen m�ssen
	gwg->GetPlayer(player)->RemoveFlagWorker(this);
}

/// Geht wieder zur�ck zur Flagge und dann nach Hause
void nofFlagWorker::GoToFlag()
{
	// Zur Flagge zur�cklaufen

	// Bin ich an der Fahne?
	if(x == flag->GetX() && y == flag->GetY())
	{
		// nach Hause gehen
		if(nobBaseWarehouse * wh = gwg->GetPlayer(player)->FindWarehouse(flag,FW::Condition_StoreFigure,0,true,&job,false))
		{
			GoHome(wh);
			// Vorgaukeln, dass wir ein St�ck Stra�e bereits geschafft haben
			// damit wir mit WalkToGoal weiter bis zum Ziel laufen k�nnen
			cur_rs = &emulated_wanderroad;
			rs_pos = 0;
			WalkToGoal();
		}
		else 
		{
			// Weg f�hrt nicht mehr zum Lagerhaus, dann rumirren
			StartWandering();
			Wander();
		}

		
		// Da wir quasi "freiwillig" nach Hause gegangen sind ohne das Abrei�en der Flagge, auch manuell wieder
		// "abmelden"
		gwg->GetPlayer(player)->RemoveFlagWorker(this);

		state = STATE_FIGUREWORK;

		flag = 0;
		
	}
	else
	{
		// Weg suchen
		dir = gwg->FindHumanPath(x,y,flag->GetX(),flag->GetY(),40);

		// Wenns keinen gibt, rumirren, ansonsten hinlaufen
		if(dir == 0xFF)
		{
			Abrogate();
			StartWandering();
			Wander();
			state = STATE_FIGUREWORK;

			flag = 0;
		}
		else
		{
			StartWalking(dir);
		}
	}
}

