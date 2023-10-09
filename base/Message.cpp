#include "Message.h"

Message* Message::GetInstance()
{
	static Message instance;
	return &instance;
}

bool Message::Update()
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT)
	{
		return true;
	}
	return false;

}

bool Message::CheckError()
{
	return 1;
}
