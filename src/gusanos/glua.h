#ifndef VERMES_GLUA_H
#define VERMES_GLUA_H

#include <string>
#include <vector>
#include "luaapi/types.h"
#include "CodeAttributes.h"

#define C_LocalPlayer_ActionCount 8

#define EACH_CALLBACK(i_, type_) for(std::vector<LuaReference>::iterator i_ = luaCallbacks.callbacks[LuaCallbacks::type_].begin(); \
			i_ != luaCallbacks.callbacks[LuaCallbacks::type_].end(); ++i_)

struct LuaCallbacks
{
	enum
	{
		atGameStart = 0,
		afterRender = 1,
		afterUpdate = 2,
		wormRender = 3,
		viewportRender = 4,
		wormDeath = 5,
		wormRemoved = 6,
		playerUpdate = 7,
		playerInit = 8,
		playerRemoved = 9,
		playerNetworkInit = 10,
		gameNetworkInit = 11,
		gameEnded = 12,
		localplayerEventAny = 13,
		localplayerInit = 14,
		localplayerEvent = 15,
		networkStateChange = localplayerEvent+C_LocalPlayer_ActionCount,
		gameError,
		max
	};
	void bind(std::string callback, LuaReference ref);
	std::vector<LuaReference> callbacks[max];
};

extern LuaCallbacks luaCallbacks;

struct LuaObject
{
	bool deleted;
	LuaReference luaReference;

	LuaObject() : deleted(false) {}
	virtual ~LuaObject() {}

	// copy semantics: each LuaObject instance has its own unique LuaReference. nothing is copied
	LuaObject(const LuaObject&) : deleted(false) {}
	LuaObject& operator=(const LuaObject&) { return *this; }

	void pushLuaReference();
	LuaReference getLuaReference();	
	virtual LuaReference getMetaTable() const;

	virtual void finalize() {}
	virtual void deleteThis();	
};

template<class T>
INLINE void luaDelete(T* p)
{
	if(p)
		p->deleteThis();
}

#endif //VERMES_GLUA_H
