/*
 *  display.c
 * 
 * for high-level drawing functions.
 * 
 */

#include "display.h"

#include "md380.h"
#include "version.h"
#include "tooldfu.h"
#include "config.h"
#include "gfx.h"
#include "printf.h"
#include "string.h"
#include "addl_config.h"
#include "ambe.h"
#include "usersdb.h"
#include "dmr.h"
#include "console.h"
#include "netmon.h"
#include "radiostate.h"
#include "unclear.h"
#include "app_menu.h" // optional 'application' menu, activated by red BACK-button
#include "lcd_driver.h"
#include "codeplug.h"
#include "amenu_set_tg.h"


char eye_paltab[] = {
    0xd7, 0xd8, 0xd6, 0x00, 0x88, 0x8a, 0x85, 0x00, 0xe1, 0xe2, 0xe0, 0x00, 0xff, 0xff, 0xff, 0x00,
    0xae, 0xae, 0xaf, 0x00, 0x24, 0x4e, 0x8a, 0x00, 0x5d, 0x88, 0xbb, 0x00, 0xd1, 0xd2, 0xd4, 0x00,
    0xf4, 0xf4, 0xf4, 0x00, 0x3c, 0x66, 0x9f, 0x00, 0xdb, 0xe6, 0xf3, 0x00, 0x48, 0x73, 0xaa, 0x00,
    0xb6, 0xb8, 0xb4, 0x00, 0x5e, 0x6a, 0x77, 0x00
};
char eye_pix[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x11, 0x10, 0x00, 0x00, 0x23,
    0x41, 0x11, 0x31, 0x00, 0x01, 0x14, 0x55, 0x55, 0x61, 0x00, 0x21, 0x75, 0x88, 0x59, 0x94, 0x31, 0x3a, 0x85, 0x88, 0x56,
    0x57, 0x73, 0x21, 0x86, 0x55, 0x5b, 0x67, 0x41, 0x13, 0x48, 0x66, 0x69, 0x71, 0xc1, 0x0c, 0x13, 0x47, 0x33, 0x11, 0x10,
    0x00, 0x03, 0xdc, 0xd1, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const gfx_pal eye_pal = {14, 0, eye_paltab};
const gfx_bitmap bmp_eye = {12, 12, 6, 4, eye_pix, &eye_pal, 0};

#ifdef FW_D13_020
#define D_ICON_EYE_X 65
#define D_ICON_EYE_Y 1
#endif
#ifdef FW_S13_020
// on MD390 draw promiscous mode eye closed to S-Meter due to GPS-symbol an standard position
#define D_ICON_EYE_X 20
#define D_ICON_EYE_Y 1
#endif

void draw_eye_opt()
{
    // draw promiscous mode eye symbol 
    if( global_addl_config.promtg == 1 ) {
        //gfx_drawbmp((char *) &bmp_eye, D_ICON_EYE_X, D_ICON_EYE_Y);
    }
}

// Takes a positive(!) integer amplitude and computes 200*log10(amp),
// centi Bel, approximtely. If the given parameter is 0 or less, this
// function returns -1.  tnx to sellibitze

int intCentibel(long ampli)
{
    if( ampli <= 0 )
        return -1; // invalid
    int log_2 = 0;
    while (ampli >= 32 * 8) {
        ampli >>= 1 + 3;
        log_2 += 1 + 3;
    }
    while (ampli >= 32) {
        ampli >>= 1;
        log_2 += 1;
    }
    // 1 <= ampli < 32
    static const short fine[] = {
        -1, 0, 60, 95, 120, 140, 156, 169,
        181, 191, 200, 208, 216, 223, 229, 235,
        243, 249, 253, 258, 262, 266, 270, 274,
        278, 281, 285, 288, 291, 294, 297, 300
    };
    return (log_2 * 301 + 2) / 5 + fine[ampli];
}

#define RX_POPUP_Y_START 24
#define RX_POPUP_X_START 10


//uint32_t rgb16torgb(uint16_t color) {
//return (((color & 0xF800) << 5)*8) | (((color & 0x7E0) << 3) * 8) | (((color & 0x1F)) * 8);
//}

#define RX_POPUP_Y_START 22 // 24
#define RX_POPUP_X_START 4  // 10

void draw_rx_screen(unsigned int bg_color)
{
	static int dst;
	int src;
	int grp;
	int nameLen;
	//char *timeSlot[3];
	int primask = OS_ENTER_CRITICAL(); // for form sake

	//channel_info_t *ci = &current_channel_info;

	dst = rst_dst;
	src = rst_src;
	grp = rst_grp;

	OS_EXIT_CRITICAL(primask);

	// clear screen
	gfx_set_fg_color(bg_color);
	gfx_blockfill(0, 16, MAX_X, MAX_Y);

	gfx_set_bg_color(bg_color);
	gfx_set_fg_color(0x000000);
	gfx_select_font(gfx_font_small);

	
	gfx_select_font(gfx_font_small);

	int y_index = RX_POPUP_Y_START;

		gfx_printf_pos(RX_POPUP_X_START, y_index, "%d->TG %d %s", src, dst, (1 == 1 ? "TS2" : "TS1"));
	

	y_index += GFX_FONT_SMALL_HEIGHT;

	gfx_select_font(gfx_font_norm); // switch to large font
	gfx_printf_pos2(RX_POPUP_X_START, y_index, 10, "%s %s", "TESTING", "4321");
	y_index += GFX_FONT_NORML_HEIGHT;

				gfx_printf_pos2(RX_POPUP_X_START, y_index, 10, "DMRID: %d", src);
			

	gfx_select_font(gfx_font_norm);
	gfx_set_fg_color(0xff8032);
	gfx_set_bg_color(0xff000000);
}

/*void rx_screen_blue_hook(unsigned int bg_color)
{
//	if (nm_screen == 9)
	//	nm_screen = 0;
	//netmon_update();



	//if (global_addl_config.userscsv > 0 && !is_menu_visible()) {
		//if (global_addl_config.userscsv == 2) {
			draw_rx_screen(0xff8032);      // ta
		//}

	//}else {
	//	swapFGBG();

		//gfx_drawbmp(bmp, x, y);
	//}

}*/

void draw_ta_screen(unsigned int bg_color)
{
	/*int dst;
	int src;
	int grp;

	int primask = OS_ENTER_CRITICAL(); // for form sake

	dst = rst_dst;
	src = rst_src;
	grp = rst_grp;

	OS_EXIT_CRITICAL(primask);

	// clear screen
	gfx_set_fg_color(bg_color);
	gfx_blockfill(0, 16, MAX_X, MAX_Y);

	gfx_set_bg_color(bg_color);
	gfx_set_fg_color(0x000000);
	gfx_select_font(gfx_font_small);

	user_t usr;

	int y_index = RX_POPUP_Y_START;

	gfx_select_font(gfx_font_small);
	if (grp) {
		gfx_printf_pos(RX_POPUP_X_START, y_index, "%d -> TG %d", src, dst);
	}
	else {
		gfx_printf_pos(RX_POPUP_X_START, y_index, "%d -> %d", src, dst);
	}
	y_index += GFX_FONT_SMALL_HEIGHT;

	if (global_addl_config.userscsv > 1 && talkerAlias.length > 0)		// 2017-02-19 show Talker Alias depending on setup 0=CPS 1=DB 2=TA 3=TA & DB
	{
		gfx_select_font(gfx_font_norm);
		gfx_printf_pos2(RX_POPUP_X_START, y_index, 10, "%s", talkerAlias.text);
	}

	y_index += GFX_FONT_NORML_HEIGHT; // previous line was in big font

	gfx_select_font(gfx_font_small);

	if (usr_find_by_dmrid(&usr, src) == 0)
	{
		gfx_puts_pos(RX_POPUP_X_START, y_index, "No userdb info");
	}
	else {
		gfx_printf_pos(RX_POPUP_X_START, y_index, "%s %s", usr.callsign, usr.firstname);
	}
	y_index += GFX_FONT_SMALL_HEIGHT; // previous line was in small font

	y_index += GFX_FONT_SMALL_HEIGHT;
	y_index += GFX_FONT_SMALL_HEIGHT;

	gfx_puts_pos(RX_POPUP_X_START, y_index, usr.country);
	y_index += GFX_FONT_SMALL_HEIGHT;

	gfx_select_font(gfx_font_norm);
	gfx_set_fg_color(0xff8032);
	gfx_set_bg_color(0xff000000);*/
}
/*
#include <stdlib.h>

int main(void)
{
    long peak = 6000;
    if (peak > 0) {
	int fullscale_offset = int_centibel(32767);
	int relative_peak_cb = int_centibel(peak) - fullscale_offset;
	printf("%i.%i dBFS\en", relative_peak_cb / 10,
	       abs(relative_peak_cb % 10));
    } else {
	printf("-Inf dBFS\n");
    }
    return 0;
}
*/


/* Displays a startup demo on the device's screen, including some of
   the setting information and a picture or two. */
void display_credits()
{
    drawtext(L"TyMD380Toolz ", 160, 20);
    drawtext(L"by KK4VCZ  ", 160, 60);
    drawtext(L"and KG5RKI", 160, 100);
#ifdef MD380_d13_020
    drawtext(L"@ D13.020", 160, 140);
#endif
#ifdef MD380_d02_032
    drawtext(L"@ D02.032", 160, 140);
#endif
#ifdef MD380_s13_020
    drawtext(L"@ S13.020", 160, 140);
#endif

    //drawascii(GIT_VERSION, 160, 180);

    //drawtext(VERSIONDATE, 160, 220);
	drawtext(L"TY_NET", 165, 200);
}
