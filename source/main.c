
#include "global.h"
#include "ov.h"
#include "reiwa.h"

FS_archive sdmcArchive = { 0x9, (FS_path){ PATH_EMPTY, 1, (u8*)"" } };
Handle fsUserHandle = 0;

#define CALLBACK_OVERLAY (101)

#define TICKS_PER_MSEC (268123.480)

typedef struct{
	u32 r;
	u32 g;
	u32 b;
}Color;

void drawWidget(int isBottom, u32 addr, u32 stride, u32 format, u32 colOffset) {
	u32 height = isBottom ? 320 : 400;
	char buf[30] = "By Haramaki[ptr]";
	
	Color color = {0x00,0xFF,0x00}; //Green

	//ovDrawString(仮想アドレス, ストライド, フォーマット, オフセット, 縦, 横, 赤, 緑, 青, バッファ)
	ovDrawString(addr, stride, format, height, 10, colOffset, color.r, color.g, color.b, buf);
	for(int i=0;i<17;i++)
	{
		ovDrawString(addr, stride, format, height, 50+(i*10), colOffset+30, 0, 128, 255, &reiwa[i][0]);
	}
}


/*
Overlay Callback.
isBottom: 1 for bottom screen, 0 for top screen.
addr: writable cached framebuffer virtual address.
addrB: right-eye framebuffer for top screen, undefined for bottom screen.
stride: framebuffer stride(pitch) in bytes, at least 240*bytes_per_pixel.
format: framebuffer format, see https://www.3dbrew.org/wiki/GPU/External_Registers for details.

NTR will invalidate data cache of the framebuffer before calling overlay callbacks. NTR will flush data cache after the callbacks were called and at least one overlay callback returns zero.

return 0 when the framebuffer was modified. return 1 when nothing in the framebuffer was modified.
*/

u32 overlayCallback(u32 isBottom, u32 addr, u32 addrB, u32 stride, u32 format) {
	if(!isBottom)
	{
		drawWidget(isBottom, addr, stride, format, 20);
		// In 2D mode, top screen's addrB might be invalid or equal to addr, do not draw on addrB in either situations
		if ((isBottom == 0) && (addrB) && (addrB != addr))
		{
			drawWidget(isBottom, addrB, stride, format, 20);
		}
		return 0;
	}
}

int main() {
	u32 retv;
	
	initSharedFunc();
	plgRegisterCallback(CALLBACK_OVERLAY, (void*) overlayCallback, 0);
	return 0;
}

