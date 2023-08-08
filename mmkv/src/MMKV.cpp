#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#if !defined(WIN32)
#include <unistd.h>
#endif

#define LIB_NAME "MMKV"
#define MODULE_NAME "mmkv"

// Defold SDK
#include <dmsdk/sdk.h>

#include "MMKV.h"

static int Init(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    const char* path = (const char*)luaL_checkstring(L, 1);
    bool debug = lua_toboolean(L, 2);
    MMKV::initializeMMKV(string2MMKVPath_t(path), debug ? MMKVLogDebug:MMKVLogWarning);
    
    return 0;
}

static int DefaultDB(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    const char* cryptKey = (const char*)luaL_optstring(L, 1, nullptr);
    MMKV* db;
    if (cryptKey == nullptr){
        db = MMKV::defaultMMKV(MMKV_SINGLE_PROCESS);
    } else {
        std::string key = cryptKey;
        db = MMKV::defaultMMKV(MMKV_SINGLE_PROCESS, &key);
    }
    
    lua_pushlightuserdata(L, db);
    return 1;
}

static int OpenDB(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    const char* file = (const char*)luaL_checkstring(L, 1);
    const char* cryptKey = (const char*)luaL_optstring(L, 2, nullptr);
    MMKV* db;
    if (cryptKey == nullptr){
        db = MMKV::mmkvWithID(file, MMKV_SINGLE_PROCESS);
    } else {
        std::string key = cryptKey;
        db = MMKV::mmkvWithID(file, MMKV_SINGLE_PROCESS, &key);
    }
    lua_pushlightuserdata(L, db);
    return 1;
}

static int GetDouble(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    lua_Number def = luaL_optnumber(L, 3, 0.0f);
    if (db->containsKey(key)){
        lua_pushnumber(L, db->getDouble(key));
    } else {
        lua_pushnumber(L, def);
    }
    
    return 1;
}

static int GetInt(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    int32_t def = luaL_optinteger(L, 3, 0);
    if (db->containsKey(key)){
        lua_pushinteger(L, db->getInt32(key));
    } else {
        lua_pushinteger(L, def);
    }
    
    return 1;
}

static int GetUInt(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    uint32_t def = luaL_optinteger(L, 3, 0);
    if (db->containsKey(key)){
        lua_pushinteger(L, db->getUInt32(key));
    } else {
        lua_pushinteger(L, def);
    }
    
    return 1;
}

static int GetInt64(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    int64_t def = luaL_optinteger(L, 3, 0);
    if (db->containsKey(key)){
        lua_pushinteger(L, db->getInt64(key));
    } else {
        lua_pushinteger(L, def);
    }
    
    return 1;
}

static int GetUInt64(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    uint64_t def = luaL_optinteger(L, 3, 0);
    if (db->containsKey(key)){
        lua_pushinteger(L, db->getUInt64(key));
    } else {
        lua_pushinteger(L, def);
    }
    
    return 1;
}

static int SetNumber(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    lua_Number value = luaL_checknumber(L, 3);
    db->set(value, key);
    return 0;
}

static int SetInt(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    int32_t value = luaL_checkinteger(L, 3);
    db->set(value, key);
    return 0;
}

static int SetUInt(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    uint32_t value = luaL_checkinteger(L, 3);
    db->set(value, key);
    return 0;
}

static int SetInt64(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    int64_t value = luaL_checkinteger(L, 3);
    db->set(value, key);
    return 0;
}

static int SetUInt64(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    uint64_t value = luaL_checkinteger(L, 3);
    db->set(value, key);
    return 0;
}

static int SetBool(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    bool value = lua_toboolean(L, 3);
    db->set(value, key);
    return 0;
}

static int GetBool(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    bool def = lua_toboolean(L, 3);
    if (db->containsKey(key)){
        lua_pushboolean(L, db->getBool(key));
    } else {
        lua_pushboolean(L, def);
    }
    return 1;
}

static int SetString(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    const char* value = luaL_checkstring(L, 3);
    db->set(value, key);
    return 0;
}

static int GetString(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    const char* def = luaL_optstring(L, 3, nullptr);
    if (db->containsKey(key)){
        std::string result;
        db->getString(key, result);
        lua_pushstring(L, result.c_str());
    } else {
        lua_pushstring(L, def);
    }
    return 1;
}

static int SetBuffer(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    size_t l;
    const char* value = luaL_checklstring(L, 3, &l);
    db->set(mmkv::MMBuffer((void*)value, l), key);
    return 0;
}

static int GetBuffer(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    size_t l;
    const char* def = luaL_optlstring(L, 3, nullptr, &l);
    if (db->containsKey(key)){
        auto bf = db->getBytes(key);
        lua_pushlstring(L, (char*)bf.getPtr(), bf.length());
    } else {
        lua_pushlstring(L, def, l);
    }
    return 1;
}

static int HasKey(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    lua_pushboolean(L, db->containsKey(key));
    return 1;
}

static int RemoveKey(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    MMKV* db = (MMKV*)lua_touserdata(L, 1);
    const char* key = luaL_checkstring(L, 2);
    db->removeValueForKey(key);
    return 0;
}

static const luaL_reg Module_methods[] ={
    {"init", Init},
    {"db", DefaultDB},
    {"open", OpenDB},
    {"setnumber", SetNumber},
    {"setint", SetInt},
    {"getint", GetInt},
    {"setuint", SetUInt},
    {"getuint", GetUInt},
    {"setlong", SetInt64},
    {"getlong", GetInt64},
    {"setulong", SetUInt64},
    {"getulong", GetUInt64},
    {"getnumber", GetDouble},
    {"getbool", GetBool},
    {"setbool", SetBool},
    {"setbuff", SetBuffer},
    {"getbuff", GetBuffer},
    {"setstring", SetString},
    {"getstring", GetString},
    {"haskey", HasKey},
    {"remove", RemoveKey},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    
    assert(top == lua_gettop(L));
}

dmExtension::Result AppInitialize(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result Initialize(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    printf("Registered %s Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalize(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result Finalize(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(MMKV, LIB_NAME, AppInitialize, AppFinalize, Initialize, 0, 0, Finalize)