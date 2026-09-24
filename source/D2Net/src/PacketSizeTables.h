#pragma once

#include <cstdint>
#include <iterator>

#include <D2PacketDef.h>

// Size of each packet by header, as used by SERVER_GetServerPacketSize and SERVER_GetClientPacketSize.
// Private to D2Net: only Client.cpp and Server.cpp should include this.

constexpr int32_t VARIABLE_PACKET_SIZE = -1;

constexpr int32_t gServerPacketSizeTable[] =
{
	sizeof(D2GSPacketSrv00),
	sizeof(D2GSPacketSrv01),
	sizeof(D2GSPacketSrv02),
	sizeof(D2GSPacketSrv03),
	sizeof(D2GSPacketSrv04),
	sizeof(D2GSPacketSrv05),
	sizeof(D2GSPacketSrv06),
	sizeof(D2GSPacketSrv07),
	sizeof(D2GSPacketSrv08),
	sizeof(D2GSPacketSrv09),
	sizeof(D2GSPacketSrv0A),
	sizeof(D2GSPacketSrv0B),
	sizeof(D2GSPacketSrv0C),
	sizeof(D2GSPacketSrv0D),
	sizeof(D2GSPacketSrv0E),
	sizeof(D2GSPacketSrv0F),
	sizeof(D2GSPacketSrv10),
	sizeof(D2GSPacketSrv11),
	sizeof(D2GSPacketSrv12),
	sizeof(D2GSPacketSrv13),
	sizeof(D2GSPacketSrv14),
	sizeof(D2GSPacketSrv15),
	VARIABLE_PACKET_SIZE,
	0,
	sizeof(D2GSPacketSrv18),
	sizeof(D2GSPacketSrv19),
	sizeof(D2GSPacketSrv1A),
	sizeof(D2GSPacketSrv1B),
	sizeof(D2GSPacketSrv1C),
	//sizeof(D2GSPacketSrv1D),
	3, // 0x1D
	//sizeof(D2GSPacketSrv1E),
	4, // 0x1E
	//sizeof(D2GSPacketSrv1F),
	6, // 0x1F
	//sizeof(D2GSPacketSrv20),
	10, // 0x20
	sizeof(D2GSPacketSrv21),
	sizeof(D2GSPacketSrv22),
	sizeof(D2GSPacketSrv23),
	sizeof(D2GSPacketSrv24),
	sizeof(D2GSPacketSrv25),
	VARIABLE_PACKET_SIZE,
	sizeof(D2GSPacketSrv27),
	sizeof(D2GSPacketSrv28),
	sizeof(D2GSPacketSrv29),
	sizeof(D2GSPacketSrv2A),
	0,
	sizeof(D2GSPacketSrv2C),
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	VARIABLE_PACKET_SIZE,
	sizeof(D2GSPacketSrv3F),
	sizeof(D2GSPacketSrv40),
	0,
	sizeof(D2GSPacketSrv42),
	0,
	0,
	sizeof(D2GSPacketSrv45),
	0,
	sizeof(D2GSPacketSrv47),
	sizeof(D2GSPacketSrv48),
	0,
	0,
	0,
	sizeof(D2GSPacketSrv4C),
	sizeof(D2GSPacketSrv4D),
	//sizeof(D2GSPacketSrv4E),
	7, // 0x4E
	sizeof(D2GSPacketSrv4F),
	sizeof(D2GSPacketSrv50),
	sizeof(D2GSPacketSrv51),
	sizeof(D2GSPacketSrv52),
	sizeof(D2GSPacketSrv53),
	//sizeof(D2GSPacketSrv54),
	3, // 0x54
	0,
	0,
	//sizeof(D2GSPacketSrv57),
	14, // 0x57
	sizeof(D2GSPacketSrv58),
	sizeof(D2GSPacketSrv59),
	sizeof(D2GSPacketSrv5A),
	VARIABLE_PACKET_SIZE,
	sizeof(D2GSPacketSrv5C),
	sizeof(D2GSPacketSrv5D),
	sizeof(D2GSPacketSrv5E),
	sizeof(D2GSPacketSrv5F),
	sizeof(D2GSPacketSrv60),
	sizeof(D2GSPacketSrv61),
	sizeof(D2GSPacketSrv62),
	sizeof(D2GSPacketSrv63),
	0,
	sizeof(D2GSPacketSrv65),
	sizeof(D2GSPacketSrv66),
	sizeof(D2GSPacketSrv67),
	sizeof(D2GSPacketSrv68),
	sizeof(D2GSPacketSrv69),
	sizeof(D2GSPacketSrv6A),
	sizeof(D2GSPacketSrv6B),
	sizeof(D2GSPacketSrv6C),
	sizeof(D2GSPacketSrv6D),
	sizeof(D2GSPacketSrv6E),
	sizeof(D2GSPacketSrv6F),
	sizeof(D2GSPacketSrv70),
	sizeof(D2GSPacketSrv71),
	sizeof(D2GSPacketSrv72),
	sizeof(D2GSPacketSrv73),
	sizeof(D2GSPacketSrv74),
	sizeof(D2GSPacketSrv75),
	sizeof(D2GSPacketSrv76),
	sizeof(D2GSPacketSrv77),
	sizeof(D2GSPacketSrv78),
	sizeof(D2GSPacketSrv79),
	sizeof(D2GSPacketSrv7A),
	sizeof(D2GSPacketSrv7B),
	sizeof(D2GSPacketSrv7C),
	sizeof(D2GSPacketSrv7D),
	sizeof(D2GSPacketSrv7E),
	sizeof(D2GSPacketSrv7F),
	0,
	sizeof(D2GSPacketSrv81),
	sizeof(D2GSPacketSrv82),
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(D2GSPacketSrv89),
	sizeof(D2GSPacketSrv8A),
	sizeof(D2GSPacketSrv8B),
	sizeof(D2GSPacketSrv8C),
	sizeof(D2GSPacketSrv8D),
	sizeof(D2GSPacketSrv8E),
	sizeof(D2GSPacketSrv8F),
	sizeof(D2GSPacketSrv90),
	sizeof(D2GSPacketSrv91),
	sizeof(D2GSPacketSrv92),
	sizeof(D2GSPacketSrv93),
	VARIABLE_PACKET_SIZE,
	//sizeof(D2GSPacketSrv95),
	13,
	sizeof(D2GSPacketSrv96),
	sizeof(D2GSPacketSrv97),
	sizeof(D2GSPacketSrv98),
	sizeof(D2GSPacketSrv99),
	sizeof(D2GSPacketSrv9A),
	sizeof(D2GSPacketSrv9B),
	VARIABLE_PACKET_SIZE,
	VARIABLE_PACKET_SIZE,
	sizeof(D2GSPacketSrv9E), // 0x9E
	sizeof(D2GSPacketSrv9F), // 0x9F
	sizeof(D2GSPacketSrvA0), // 0xA0
	sizeof(D2GSPacketSrvA1), // 0xA1
	sizeof(D2GSPacketSrvA2), // 0xA2
	sizeof(D2GSPacketSrvA3),
	sizeof(D2GSPacketSrvA4),
	sizeof(D2GSPacketSrvA5),
	VARIABLE_PACKET_SIZE,
	//sizeof(D2GSPacketSrvA7),
	7, // 0xA7
	VARIABLE_PACKET_SIZE,
	//sizeof(D2GSPacketSrvA9),
	7, // 0xA9
	VARIABLE_PACKET_SIZE,
	sizeof(D2GSPacketSrvAB),
	VARIABLE_PACKET_SIZE,
	sizeof(D2GSPacketSrvAD),
	VARIABLE_PACKET_SIZE,
	//sizeof(D2GSPacketSrvAF),
	1, // 0xAF
	0,
	sizeof(D2GSPacketSrvB1),
	VARIABLE_PACKET_SIZE,
	sizeof(D2GSPacketSrvB3),
};
static_assert(std::size(gServerPacketSizeTable) == 0xB4, "Server packet headers go from 0x00 to 0xB3");

constexpr int32_t gClientPacketSizeTable[] =
{
	0,
	sizeof(D2GSPacketClt01),
	sizeof(D2GSPacketClt02),
	sizeof(D2GSPacketClt03),
	sizeof(D2GSPacketClt04),
	sizeof(D2GSPacketClt05),
	sizeof(D2GSPacketClt06),
	sizeof(D2GSPacketClt07),
	sizeof(D2GSPacketClt08),
	sizeof(D2GSPacketClt09),
	sizeof(D2GSPacketClt0A),
	sizeof(D2GSPacketClt0B),
	sizeof(D2GSPacketClt0C),
	sizeof(D2GSPacketClt0D),
	sizeof(D2GSPacketClt0E),
	sizeof(D2GSPacketClt0F),
	sizeof(D2GSPacketClt10),
	sizeof(D2GSPacketClt11),
	sizeof(D2GSPacketClt12),
	sizeof(D2GSPacketClt13),
	VARIABLE_PACKET_SIZE,
	VARIABLE_PACKET_SIZE,
	sizeof(D2GSPacketClt16),
	sizeof(D2GSPacketClt17),
	sizeof(D2GSPacketClt18),
	sizeof(D2GSPacketClt19),
	//sizeof(D2GSPacketClt1A),
	9, // 0x1A
	//sizeof(D2GSPacketClt1B),
	9, // 0x1B
	//sizeof(D2GSPacketClt1C),
	3, // 0x1C
	//sizeof(D2GSPacketClt1D),
	9, // 0x1D
	//sizeof(D2GSPacketClt1E),
	9, // 0x1E
	//sizeof(D2GSPacketClt1F),
	17, // 0x1F
	sizeof(D2GSPacketClt20),
	//sizeof(D2GSPacketClt21),
	9, // 0x21
	//sizeof(D2GSPacketClt22),
	5, // 0x22
	sizeof(D2GSPacketClt23),
	//sizeof(D2GSPacketClt24),
	5, // 0x24
	//sizeof(D2GSPacketClt25),
	9, // 0x25
	sizeof(D2GSPacketClt26),
	sizeof(D2GSPacketClt27),
	//sizeof(D2GSPacketClt28),
	9, // 0x28
	sizeof(D2GSPacketClt29),
	sizeof(D2GSPacketClt2A),
	0,
	0,
	//sizeof(D2GSPacketClt2D),
	1, // 0x2D
	//sizeof(D2GSPacketClt2E),
	3, // 0x2E
	//sizeof(D2GSPacketClt2F),
	9, // 0x2F
	//sizeof(D2GSPacketClt30),
	9, // 0x30
	sizeof(D2GSPacketClt31),
	sizeof(D2GSPacketClt32),
	sizeof(D2GSPacketClt33),
	//sizeof(D2GSPacketClt34),
	5, // 0x34
	//sizeof(D2GSPacketClt35),
	17, // 0x35
	//sizeof(D2GSPacketClt36),
	9, // 0x36
	//sizeof(D2GSPacketClt37),
	5, // 0x37
	sizeof(D2GSPacketClt38),
	//sizeof(D2GSPacketClt39),
	5, // 0x39
	sizeof(D2GSPacketClt3A),
	sizeof(D2GSPacketClt3B),
	sizeof(D2GSPacketClt3C),
	sizeof(D2GSPacketClt3D),
	//sizeof(D2GSPacketClt3E),
	5, // 0x3E
	//sizeof(D2GSPacketClt3F),
	3, // 0x3F
	//sizeof(D2GSPacketClt40),
	1, // 0x40
	sizeof(D2GSPacketClt41),
	sizeof(D2GSPacketClt42),
	//sizeof(D2GSPacketClt43),
	1, // 0x43
	sizeof(D2GSPacketClt44),
	sizeof(D2GSPacketClt45),
	//sizeof(D2GSPacketClt46),
	13, // 0x46
	//sizeof(D2GSPacketClt47),
	13, // 0x47
	//sizeof(D2GSPacketClt48),
	1, // 0x48
	sizeof(D2GSPacketClt49),
	0,
	//sizeof(D2GSPacketClt4B),
	9, // 0x4B
	//sizeof(D2GSPacketClt4C),
	5, // 0x4C
	//sizeof(D2GSPacketClt4D),
	3, // 0x4D
	0,
	sizeof(D2GSPacketClt4F),
	//sizeof(D2GSPacketClt50),
	9, // 0x50
	sizeof(D2GSPacketClt51),
	//sizeof(D2GSPacketClt52),
	5, // 0x52
	//sizeof(D2GSPacketClt53),
	1, // 0x53
	//sizeof(D2GSPacketClt54),
	1, // 0x54
	0,
	0,
	0,
	sizeof(D2GSPacketClt58),
	sizeof(D2GSPacketClt59),
	0,
	0,
	0,
	sizeof(D2GSPacketClt5D),
	sizeof(D2GSPacketClt5E),
	//sizeof(D2GSPacketClt5F),
	5, // 0x5F
	//sizeof(D2GSPacketClt60),
	1, // 0x60
	//sizeof(D2GSPacketClt61),
	3, // 0x61
	//sizeof(D2GSPacketClt62),
	5, // 0x62
	sizeof(D2GSPacketClt63),
	sizeof(D2GSPacketClt64),
	sizeof(D2GSPacketClt65),
	sizeof(D2GSPacketClt66),
	sizeof(D2GSPacketClt67),
	sizeof(D2GSPacketClt68),
	sizeof(D2GSPacketClt69),
	sizeof(D2GSPacketClt6A),
	VARIABLE_PACKET_SIZE,
	sizeof(D2GSPacketClt6C),
	sizeof(D2GSPacketClt6D),
	0,
	sizeof(D2GSPacketClt6F),
};
static_assert(std::size(gClientPacketSizeTable) == 0x70, "Client packet headers go from 0x00 to 0x6F");
