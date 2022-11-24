// Copyright 2022 Maximilien (Synock) Guislain


#include "Interfaces/PlayerChatInterface.h"


// Add default functionality here for any IPlayerChatInterface functions that are not pure virtual.

void IPlayerChatInterface::AddChatData(EChatColor Color, EMessageCategories Category, const FString& Message)
{
	if (IHUDChatInterface* ChatHUD = GetChatHUD())
	{
		ChatHUD->AddChatData(Color, Category, Message);
	}
}

void IPlayerChatInterface::AddChatDataType(EGlobalMessageType Type, const FString& Message)
{
	if (IHUDChatInterface* ChatHUD = GetChatHUD())
	{
		ChatHUD->AddChatDataType(Type, Message);
	}
}

void IPlayerChatInterface::AreaSpeak(const FString& Message, float Range)
{
	SelfHearingSpeak(EGlobalMessageType::Say, Message);

	Server_AreaSpeak(Message,Range);
}

void IPlayerChatInterface::SelfHearingSpeak(EGlobalMessageType Type, const FString& Message)
{
	EChatColor Color = EChatColor::White;
	switch (Type)
	{
	default:
	case EGlobalMessageType::Unknown: break;
	case EGlobalMessageType::Say:
		AddChatData(Color,  EMessageCategories::Chat, "You say, " + Message);
		break;
	case EGlobalMessageType::Group:
		AddChatData(Color, EMessageCategories::Chat, "You tell your party, " + Message);
		break;
	case EGlobalMessageType::Raid:
		AddChatData(Color, EMessageCategories::Chat, "You tell your party, " + Message);
		break;
	case EGlobalMessageType::Shout:
		AddChatData(Color, EMessageCategories::Chat, "You shout, " + Message);
		break;
	case EGlobalMessageType::OOC:
		AddChatData(Color, EMessageCategories::Chat, "You say out of character, " + Message);
		break;
	case EGlobalMessageType::Tell:
		AddChatData(Color, EMessageCategories::Chat, "You told, " + Message);
		break;
	}
}
