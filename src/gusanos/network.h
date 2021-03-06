#ifndef NETWORK_H
#define NETWORK_H


#include "netstream.h"
#include <string>
#include <boost/function.hpp>
#include "luaapi/types.h"

struct LuaEventDef
{
	static LuaReference metaTable;
	
	LuaEventDef(const std::string& name_, LuaReference callb_)
	: name(name_), idx(0), callb(callb_)
	{
	}
	
	~LuaEventDef();
	
	void call(BitStream*);
	
	void call(LuaReferenceLazy, BitStream*);
	
	void* operator new(size_t count);
	
	void operator delete(void* block)
	{
		// Lua frees the memory
	}

	void operator delete(void*, void*)
	{
		// Lua frees the memory
	}
	
	void* operator new(size_t count, void* space)
	{
		return space;
	}
	
	std::string  name;
	size_t       idx;
	LuaReference callb;
	LuaReference luaReference;
};

class Network
{
public:
	friend class Client;
	friend class Server;
	
	static int const protocolVersion;
		
	enum State
	{
		StateIdle,	// Not doing anything
		StateDisconnecting, // Starting disconnection sequence
		StateDisconnected, // Disconnected
		
		StateConnecting, // Pseudo-state
		StateHosting,  // Pseudo-state
	};
	
	struct ClientEvents
	{
		enum type
		{
			LuaEvents,
			ConnectionInfo,
			Max
		};
	};
		
	struct LuaEventGroup
	{
		enum type
		{
			GusGame,
			CWormHumanInputHandler,
			Worm,
			Particle,
			Max
		};
	};
	
	Network();
	~Network();
	
	static void log(char const* msg);
	
	static void init();
	static void shutDown();
	static void registerInConsole();
	static void update();
	
	static void olxHost();
	static void olxConnect();
	static void disconnect();
	static void olxReconnect(int delay = 1);
	static void clear();
	static void olxShutdown();
	
	void olxParse(Net_ConnID src, CBytestream& bs);
	void olxParseUpdate(Net_ConnID src, CBytestream& bs);
	void olxSend(bool sendPendingOnly);
	
	static Net_ConnID getServerID();
	
	static bool isHost();
	static bool isClient();
		
	static LuaEventDef* addLuaEvent(LuaEventGroup::type, const std::string& name, LuaEventDef* event);
	static void indexLuaEvent(LuaEventGroup::type, const std::string& name);
	static LuaEventDef* indexToLuaEvent(LuaEventGroup::type type, int idx);
	static void encodeLuaEvents(BitStream* data);
	
	static void sendEncodedLuaEvents(Net_ConnID cid);
	
	static Net_Control* getNetControl();

	static void incConnCount();
	static void decConnCount();
	
	static bool isDisconnected();
	static bool isDisconnecting();
		
	int checkCRC;	
};

extern Network network;

#endif // _NETWORK_H_
