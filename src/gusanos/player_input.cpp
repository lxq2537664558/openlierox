#ifndef DEDICATED_ONLY
#include "player_input.h"

#include "game.h"
#include "CWormHuman.h"
#include "gconsole.h"
#include "glua.h"
#include "lua51/luaapi/context.h"
#include "util/text.h"
#include "util/log.h"
#include "util/stringbuild.h"
#include <boost/bind.hpp>

#include <string>
#include <list>
#include <vector>

using namespace std;

string eventStart(size_t index, CWormHumanInputHandler::Actions action, list<string> const& args)
{
	if ( index < game.localPlayers.size() )
	{
		CWormHumanInputHandler& player = *game.localPlayers[index];
		
		bool ignore = false;
		
		EACH_CALLBACK(i, localplayerEvent+action)
		{
			int n = (lua.call(*i, 1), player.getLuaReference(), true)();
			if(n > 0 && lua.get<bool>(-1))
				ignore = true;
			lua.pop(n);
		}
		
		EACH_CALLBACK(i, localplayerEventAny)
		{
			int n = (lua.call(*i, 1), player.getLuaReference(), static_cast<int>(action), true)();
			if(n > 0 && lua.get<bool>(-1))
				ignore = true;
			lua.pop(n);
		}
		
		if(!ignore)
			player.actionStart(action);
	}
	return "";
}

string eventStop(size_t index, CWormHumanInputHandler::Actions action, list<string> const& args)
{
	if ( index < game.localPlayers.size() )
	{
		CWormHumanInputHandler& player = *game.localPlayers[index];
		
		bool ignore = false;
		
		EACH_CALLBACK(i, localplayerEvent+action)
		{
			int n = (lua.call(*i, 1), player.getLuaReference(), false)();
			if(n > 0 && lua.get<bool>(-1))
				ignore = true;
			lua.pop(n);
		}
		
		EACH_CALLBACK(i, localplayerEventAny)
		{
			int n = (lua.call(*i, 1), player.getLuaReference(), static_cast<int>(action), false)();
			if(n > 0 && lua.get<bool>(-1))
				ignore = true;
			lua.pop(n);
		}
		
		if(!ignore)
			player.actionStop(action);
	}
	return "";
}

void registerPlayerInput()
{
	for ( size_t i = 0; i < Game::MAX_LOCAL_PLAYERS; ++i)
	{
		static char const* actionNames[] =
		{
			"_LEFT", "_RIGHT", "_UP", "_DOWN", "_FIRE", "_JUMP", "_CHANGE"
		};
		
		for(int action = CWormHumanInputHandler::LEFT; action < CWormHumanInputHandler::ACTION_COUNT; ++action)
		{
			console.registerCommands()
				((S_("+P") << i << actionNames[action]), boost::bind(eventStart, i, (CWormHumanInputHandler::Actions)action, _1))
				((S_("-P") << i << actionNames[action]), boost::bind(eventStop, i, (CWormHumanInputHandler::Actions)action, _1))
			;
		}
	}
	console.registerCommands()
		("SAY", say);
}

string say( const list<string> &args )
{
	if ( !args.empty() )
	{
		if ( !game.localPlayers.empty() )
		{
			game.localPlayers[0]->sendChatMsg( *(args.begin()) );
		}
	}
	else
	{
		return "SAY <MESSAGE> : SENDS A MESSAGE TO THE OTHER PLAYERS ON THE SERVER";
	}
	return "";
}

#endif
