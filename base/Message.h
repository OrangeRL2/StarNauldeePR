#pragma once
//#include "dxgidebug.h"
#include <d3d12.h>

/**
 * @file Message.h
 * @brief Class for handling Windows messages
 * @author Nauldee Nawill
 */

class Message
{
public:
	static Message* GetInstance();

	bool Update();

	bool CheckError();
public:
	MSG msg{};
};

