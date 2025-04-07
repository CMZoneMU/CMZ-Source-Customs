#include "stdafx.h"

CCustomMessage gCustomMessage;

CCustomMessage::CCustomMessage() // OK
{
	this->Init();
}

CCustomMessage::~CCustomMessage() // OK
{

}

void CCustomMessage::Init() // OK
{
	this->m_LangSelected = 0;

	memset(this->m_DefaultMessage, 0, sizeof(this->m_DefaultMessage));

	for (int n = 0;n < MAX_CUSTOM_MESSAGE;n++)
	{
		this->m_EngCustomMessageInfo[n].Index = -1;
		this->m_PorCustomMessageInfo[n].Index = -1;
		this->m_SpnCustomMessageInfo[n].Index = -1;
	}
}

void CCustomMessage::LoadEng(CUSTOM_MESSAGE_INFO* info) // OK
{
	for (int n = 0;n < MAX_CUSTOM_MESSAGE;n++)
	{
		this->SetInfoEng(info[n]);
	}
}

void CCustomMessage::LoadPor(CUSTOM_MESSAGE_INFO* info) // OK
{
	for (int n = 0;n < MAX_CUSTOM_MESSAGE;n++)
	{
		this->SetInfoPor(info[n]);
	}
}

void CCustomMessage::LoadSpn(CUSTOM_MESSAGE_INFO* info) // OK
{
	for (int n = 0;n < MAX_CUSTOM_MESSAGE;n++)
	{
		this->SetInfoSpn(info[n]);
	}
}

void CCustomMessage::SetInfoEng(CUSTOM_MESSAGE_INFO info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_CUSTOM_MESSAGE)
	{
		return;
	}

	this->m_EngCustomMessageInfo[info.Index] = info;
}

void CCustomMessage::SetInfoPor(CUSTOM_MESSAGE_INFO info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_CUSTOM_MESSAGE)
	{
		return;
	}

	this->m_PorCustomMessageInfo[info.Index] = info;
}

void CCustomMessage::SetInfoSpn(CUSTOM_MESSAGE_INFO info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_CUSTOM_MESSAGE)
	{
		return;
	}

	this->m_SpnCustomMessageInfo[info.Index] = info;
}

CUSTOM_MESSAGE_INFO* CCustomMessage::GetInfo(int index) // OK
{
	if (index < 0 || index >= MAX_CUSTOM_MESSAGE)
	{
		wsprintf(this->m_DefaultMessage, "Message %d out of bound!", index);
		return 0;
	}

	if (this->m_LangSelected == 1)
	{
		if (this->m_PorCustomMessageInfo[index].Index != index)
		{
			wsprintf(this->m_DefaultMessage, "Could not find message %d!", index);
			return 0;
		}

		return &this->m_PorCustomMessageInfo[index];
	}
	else if (this->m_LangSelected == 2)
	{
		if (this->m_SpnCustomMessageInfo[index].Index != index)
		{
			wsprintf(this->m_DefaultMessage, "Could not find message %d!", index);
			return 0;
		}

		return &this->m_SpnCustomMessageInfo[index];
	}
	else
	{
		if (this->m_EngCustomMessageInfo[index].Index != index)
		{
			wsprintf(this->m_DefaultMessage, "Could not find message %d!", index);
			return 0;
		}

		return &this->m_EngCustomMessageInfo[index];
	}
}

char* CCustomMessage::GetMessage(int index) // OK
{
	CUSTOM_MESSAGE_INFO* lpInfo = this->GetInfo(index);
	if (lpInfo == 0) { return this->m_DefaultMessage; }
	return lpInfo->Message;
}
