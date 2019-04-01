#include "global.h"

u8* Set8(u32 address)
{
	u8* offset = 0;
	offset += (address) / sizeof(u8);
	return offset;
}

u16* Set16(u32 address)
{
	u16* offset = 0;
	offset += (address) / sizeof(u16);
	return offset;
}

u32* Set32(u32 address)
{
	u32* offset = 0;
	offset += (address) / sizeof(u32);
	return offset;
}

u64* Set64(u32 address)
{
	u64* offset = 0;
	offset += (address) / sizeof(u64);
	return offset;
}