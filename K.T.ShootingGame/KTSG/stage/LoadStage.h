//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : LoadStage.h
//  @ Date : 2011/9/6
//  @ Author : 
//
//


#if !defined(_LOADSTAGE_H)
#define _LOADSTAGE_H
#include "Lua/LuaCell.h"
#include "ObjectFactory.h"
#include "Stage.h"

class LoadStage
{
public:
	void LoadNewStage(std::string path, Stage& toStage);
	LuaCell	m_Lua;
};

#endif  //_LOADSTAGE_H
