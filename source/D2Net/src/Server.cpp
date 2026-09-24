#include "Server.h"

#include <algorithm>

#include <Fog.h>
#include <Storm.h>

#include <D2PacketDef.h>

#include "Client.h"
#include "D2Net.h"
#include "PacketSizeTables.h"


QServer* gpServer;
int32_t gnLocalClientGameGuid_6FC0B26C;


//D2Net.0x6FC01B30 (#10024)
int32_t __stdcall SERVER_WSAGetLastError()
{
	return WSAGetLastError();
}

//D2Net.0x6FC01B60 (#10030)
int32_t __fastcall SERVER_GetServerPacketSize(D2PacketBufferStrc* pBuffer, uint32_t nBufferSize, int32_t* pSize)
{
	if (nBufferSize == 0)
	{
		return 0;
	}

	const uint8_t nHeader = pBuffer->data[0];
	if (nHeader >= std::size(gServerPacketSizeTable))
	{
		return 0;
	}

	*pSize = gServerPacketSizeTable[nHeader];
	if (*pSize >= 0)
	{
		return *pSize;
	}

	switch (nHeader)
	{
	case 0x16u:
	{
		if (nBufferSize < 0xD)
		{
			return 0;
		}

		*pSize = *(uint16_t*)&pBuffer->data[1];
		return *pSize;
	}
	case 0x26u:
	{
		if (nBufferSize < 10)
		{
			return 0;
		}

		const char* v6 = (const char*)&pBuffer->data[10];
		const int32_t v7 = SStrLen(v6) + 11;
		if (nBufferSize < v7)
		{
			return 0;
		}

		const int32_t v8 = SStrLen(v6);
		const int32_t result = v7 + SStrLen(&v6[v8 + 1]) + 1;
		if (nBufferSize < result)
		{
			return 0;
		}

		*pSize = result;
		return *pSize;
	}
	case 0x3Eu:
	{
		if (nBufferSize < 2)
		{
			return 0;
		}

		*pSize = pBuffer->data[1];
		return *pSize;
	}
	case 0x5Bu:
	{
		if (nBufferSize < 0x22)
		{
			return 0;
		}

		*pSize = *(uint16_t*)&pBuffer->data[1];
		return *pSize;
	}
	case 0x94u:
	{
		if (nBufferSize < 9)
		{
			return 0;
		}

		*pSize = 3 * (pBuffer->data[1] + 2);
		return *pSize;
	}
	case 0x9Cu:
	case 0x9Du:
	{
		if (nBufferSize < 3)
		{
			return 0;
		}

		*pSize = pBuffer->data[2];
		return *pSize;
	}
	case 0xA6u:
	{
		if (nBufferSize < 4)
		{
			return 0;
		}

		*pSize = *(uint16_t*)&pBuffer->data[2];
		return *pSize;
	}
	case 0xA8u: // NOLINT error: switch has 2 consecutive identical branches [bugprone-branch-clone,-warnings-as-errors]
	{
		if (nBufferSize < 7)
		{
			return 0;
		}

		*pSize = pBuffer->data[6];
		return *pSize;
	}
	case 0xAAu:
	{
		if (nBufferSize < 7)
		{
			return 0;
		}

		*pSize = pBuffer->data[6];
		return *pSize;
	}
	case 0xACu:
	{
		if (nBufferSize < 0xD)
		{
			return 0;
		}

		*pSize = pBuffer->data[12];
		return *pSize;
	}
	case 0xAEu:
	{
		if (nBufferSize < 2)
		{
			return 0;
		}

		if (pBuffer->data[1])
		{
			*pSize = pBuffer->data[1] + 1;
		}
		else
		{
			*pSize = 2;
		}
		return *pSize;
	}
	case 0xB2u:
	{
		if (nBufferSize < 8)
		{
			return 0;
		}

		*pSize = pBuffer->data[1] + 7;
		return *pSize;
	}
	default:
	{
		*pSize = 0;
		return 0;
	}
	}
}

//D2Net.0x6FC01E60 (#10031)
int32_t __fastcall SERVER_GetClientPacketSize(D2PacketBufferStrc* pBuffer, uint32_t nBufferSize, int32_t* pSize)
{
	if (nBufferSize == 0)
	{
		return 0;
	}

	const uint8_t nHeader = pBuffer->data[0];
	if (nHeader == 0xFF)
	{
		*pSize = 16;
		return 1;
	}

	if (nHeader >= std::size(gClientPacketSizeTable))
	{
		return 0;
	}

	*pSize = gClientPacketSizeTable[nHeader];
	if (*pSize >= 0)
	{
		return *pSize;
	}

	switch (nHeader)
	{
	case 0x14:
	case 0x15:
	{
		if (nBufferSize < 3)
		{
			*pSize = 0;
			return *pSize;
		}

		const char* v7 = (const char*)&pBuffer->data[3];
		const int32_t v8 = SStrLen(v7) + 4;
		if (nBufferSize < v8)
		{
			*pSize = 0;
			return *pSize;
		}

		const char* v9 = &v7[SStrLen(v7) + 1];
		const size_t v9Len = SStrLen(v9);
		const int32_t v10 = v8 + v9Len + 1;
		if (nBufferSize < v10)
		{
			*pSize = 0;
			return *pSize;
		}

		const int32_t result = v10 + v9[v9Len + 1] + 1;
		if (nBufferSize < result)
		{
			return 0;
		}

		*pSize = result;
		return *pSize;
	}
	case 0x6B:
	{
		if (nBufferSize < 6)
		{
			return 0;
		}

		*pSize = *(uint8_t*)(pBuffer + 1) + 7;
		return *pSize;
	}
	default:
	{
		*pSize = 0;
		return *pSize;
	}
	}
}

//D2Net.0x6FC01FA0 (#10039)
D2NET_CLIENT_SendFunctionType __stdcall D2NET_10039()
{
	return CLIENT_Send;
}

//D2Net.0x6FC01FB0 (#10040)
D2NET_SERVER_GetClientGameGUIDFunctionType __stdcall D2NET_10040()
{
	return SERVER_GetClientGameGUID;
}

//D2Net.0x6FC01FC0
int32_t __fastcall SERVER_ReadPacketFromBufferCallback(QServer* nUnused, D2PacketBufferStrc* pPacketBuffer, int32_t nBufferSize)
{
	D2_MAYBE_UNUSED(nUnused);
	CLIENT_ReadPacketFromBuffer(pPacketBuffer, nBufferSize);
	return 1;
}

//D2Net.0x6FC01FE0
int32_t __fastcall SERVER_ValidateClientPacket(D2PacketBufferStrc* pPacketBuffer, uint32_t nBufferSize, int32_t* a3, int32_t* a4, int32_t* a5, int32_t* a6, int32_t nUnused1, int32_t nUnused2)
{
	int32_t nSize = 0;
	if (nBufferSize == 0 || !SERVER_GetClientPacketSize(pPacketBuffer, nBufferSize, &nSize))
	{
		return 3;
	}

	const uint8_t nHeader = pPacketBuffer->data[0];
	if ((nHeader >= 0x70u && nHeader != 0xFF) || nSize < 0 || nSize > MAX_MSG_SIZE)
	{
		return 4;
	}

	if (nSize > nBufferSize)
	{
		return 3;
	}

	*a4 = 0;
	*a3 = nSize;

	if (nHeader < 0x66u)
	{
		*a5 = 1;
	}
	else if (nHeader < 0x70u)
	{
		*a5 = 0;
	}
	else
	{
		*a5 = 2;
	}

	*a6 = 100;

	if (*a5 == 1 || *a5 == 2)
	{
		return 1;
	}

	return 2;
}

//D2Net.0x6FC020B0
int32_t __fastcall sub_6FC020B0(int32_t a1, int32_t nClientId, int32_t a3, int32_t a4)
{
	uint8_t data[2] = { 0xAE, 1 };

	D2NET_10006(0, nClientId, data, sizeof(data));
	return 1;
}

//D2Net.0x6FC020E0
int32_t __fastcall sub_6FC020E0(int32_t a1, int32_t a2, int32_t a3, int32_t a4)
{
	const uint8_t data[1] = { 0x6F };

	FOG_10175(gpServer, data, sizeof(data), a2);
	return 1;
}

//D2Net.0x6FC02110
int32_t __fastcall sub_6FC02110()
{
	uint8_t data[2] = { 0xAE, 0 };

	return D2NET_10006(0, 0, data, sizeof(data));
}

//D2Net.0x6FC02130 (#10002)
int32_t __stdcall SERVER_WaitForSingleObject(uint32_t dwMilliseconds)
{
	return FOG_WaitForSingleObject(gpServer, dwMilliseconds);
}

//D2Net.0x6FC02150 (#10003)
void __stdcall SERVER_Initialize(int32_t a1, int32_t a2)
{
	gpServer = FOG_InitializeServer(a1, 3, GAME_PORT, a2, SERVER_ValidateClientPacket, sub_6FC020B0, sub_6FC020E0, SERVER_ReadPacketFromBufferCallback);
}

//D2Net.0x6FC02190 (#10035)
int32_t __stdcall D2NET_10035(int32_t nIndex, int32_t nValue)
{
	return FOG_10186(gpServer, nIndex, nValue);
}

//D2Net.0x6FC021B0 (#10036)
void __stdcall D2NET_10036(int32_t a1, int32_t a2)
{
	FOG_10187(gpServer, a2, a1);
}

//D2Net.0x6FC021D0 (#10026)
void __stdcall SERVER_SetMaxClientsPerGame(int32_t nMaxClients)
{
	FOG_SetMaxClientsPerGame(gpServer, nMaxClients);
}

//D2Net.0x6FC021F0 (#10027)
int32_t __stdcall D2NET_10027()
{
	return FOG_10180(gpServer);
}

//D2Net.0x6FC02200 (#10023)
void __stdcall SERVER_SetHackListEnabled(BOOL bEnabled)
{
	FOG_SetHackListEnabled(gpServer, bEnabled);
}

//D2Net.0x6FC02220 (#10004)
void __stdcall SERVER_Release()
{
	const uint8_t data[1] = { 0xAF };
	FOG_10152(gpServer, data, sizeof(data));

	gpServer = nullptr;
}

// TODO: Better name
//D2Net.0x6FC02250 (#10010)
int32_t __stdcall SERVER_ReadFromMessageList1(uint8_t* pBuffer, int32_t nBufferSize)
{
	return FOG_10156(gpServer, 1, pBuffer, nBufferSize);
}

// TODO: Better name
//D2Net.0x6FC02270 (#10011)
int32_t __stdcall SERVER_ReadFromMessageList0(uint8_t* pBuffer, int32_t nBufferSize)
{
	return FOG_10156(gpServer, 0, pBuffer, nBufferSize);
}

// TODO: Better name
//D2Net.0x6FC02290 (#10012)
int32_t __stdcall SERVER_ReadFromMessageList2(uint8_t* pBuffer, int32_t nBufferSize)
{
	return FOG_10156(gpServer, 2, pBuffer, nBufferSize);
}

//D2Net.0x6FC022B0 (#10006)
uint32_t __stdcall D2NET_10006(int8_t a1, int32_t nClientId, void* pBufferArg, uint32_t nBufferSize)
{
	const uint8_t* pBuffer = (const uint8_t*)pBufferArg;

	D2_ASSERT(nBufferSize <= MAX_MSG_SIZE);

	if (sub_6FC01A00())
	{
		CLIENT_ReadPacketFromBuffer((D2PacketBufferStrc*)pBuffer, nBufferSize);
		return nBufferSize;
	}

	if (!a1 && *pBuffer == 0xAE)
	{
		return FOG_10157(gpServer, nClientId, pBuffer, nBufferSize) != 0 ? nBufferSize : 0;
	}

	FOG_10222(pBuffer, nBufferSize);
	if (a1 == 2)
	{
		return FOG_10157(gpServer, nClientId, pBuffer, nBufferSize) != 0 ? nBufferSize : 0;
	}

	uint8_t data[1036] = {};
	const uint32_t nSize = FOG_10223(&data[2], 1032, pBuffer, nBufferSize);
	D2_ASSERT(nSize);

	if (nSize + 1 < 0xF0)
	{
		data[1] = nSize + 1;
		return FOG_10157(gpServer, nClientId, &data[1], nSize + 1) != 0 ? nSize + 1 : 0;
	}

	const uint32_t v6 = nSize + 2;
	data[0] = BYTE1(v6) | 0xF0;
	data[1] = nSize + 2;
	return FOG_10157(gpServer, nClientId, data, v6) != 0 ? v6 : 0;
}

//D2Net.0x6FC02410 (#10014)
void __stdcall SERVER_GetIpAddressStringFromClientId(int32_t nClientId, char* szBuffer, int32_t nBufferSize)
{
	FOG_10159(gpServer, nClientId, szBuffer, nBufferSize);
}

//D2Net.0x6FC02430 (#10038)
int32_t __stdcall SERVER_GetIpAddressFromClientId(int32_t nClientId)
{
	return FOG_10158(gpServer, nClientId);
}

//D2Net.0x6FC02450 (#10037)
SOCKET __stdcall SERVER_GetSocketFromClientId(int32_t nClientId)
{
	return FOG_10161(gpServer, nClientId);
}

//D2Net.0x6FC02470 (#10015)
void __stdcall D2NET_10015(int32_t nClientId, const char* szFile, int32_t nLine)
{
	FOG_10162(gpServer, nClientId, szFile, nLine);
}

//D2Net.0x6FC02490 (#10032)
void __stdcall D2NET_10032(int32_t nClientId, const char* szFile, int32_t nLine)
{
	FOG_10163(gpServer, nClientId, szFile, nLine);
}

//D2Net.0x6FC024B0 (#10033)
int32_t __stdcall D2NET_10033(int32_t a1, int32_t a2, int32_t a3)
{
	return FOG_10164(gpServer, a1, a2, a3);
}

//D2Net.0x6FC024D0 (#10034)
int32_t __stdcall D2NET_10034(int32_t nClientId, int32_t a2, int32_t a3)
{
	return FOG_10166(gpServer, nClientId, a2, a3);
}

//D2Net.0x6FC024F0 (#10016)
void __stdcall D2NET_10016(int32_t nClientId)
{
	FOG_10165(gpServer, nClientId, __FILE__, __LINE__);
}

//D2Net.0x6FC02510 (#10018)
void __stdcall D2NET_10018(int32_t a1)
{
	if (!gpServer)
	{
		return;
	}

	FOG_10170(gpServer, a1);
}

//D2Net.0x6FC02530 (#10019)
int32_t __stdcall D2NET_10019(D2NET_Unk_Callback pfCallback)
{
	return FOG_10171(gpServer, pfCallback);
}

//D2Net.0x6FC02550 (#10020)
int32_t __stdcall SERVER_SetClientGameGUID(int32_t nClientId, int32_t dwGameGuid)
{
	if (nClientId)
	{
		return FOG_10172(gpServer, nClientId, dwGameGuid);
	}

	gnLocalClientGameGuid_6FC0B26C = dwGameGuid;

	return dwGameGuid;
}

//D2Net.0x6FC02580 (#10021)
int32_t __stdcall SERVER_GetClientGameGUID(int32_t nClientId)
{
	if (nClientId)
	{
		return FOG_10173(gpServer, nClientId);
	}

	return gnLocalClientGameGuid_6FC0B26C;
}

//D2Net.0x6FC025A0
int32_t __fastcall SERVER_EnqueuePacketToMessageList(const uint8_t* pBuffer, int32_t nBufferSize)
{
	D2_ASSERT(nBufferSize <= MAX_MSG_SIZE);

	return FOG_10175(gpServer, pBuffer, nBufferSize, 0) != 0;
}

//D2Net.0x6FC025F0 (#10022)
int32_t __stdcall D2NET_10022(uint32_t dwMilliseconds)
{
	return FOG_10177(gpServer, dwMilliseconds);
}

//D2Net.0x6FC02610 (#10028)
int32_t __stdcall D2NET_10028_Return()
{
	return FOG_10182_Return(gpServer);
}

//D2Net.0x6FC02620 (#10029)
int32_t __stdcall D2NET_10029_Return(int32_t nUnused)
{
	return FOG_10183_Return(gpServer, nUnused);
}
