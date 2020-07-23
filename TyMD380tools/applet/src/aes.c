

#define COMPILING_MAIN_C 1  // flag to show warnings in headers only ONCE
                   // (e.g. "please consider finding symbols.." in gfx.h)

#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h" // again, added because ST didn't put it here ?

#include <string.h>

char* aes_cipher(char *pkt);
char* aes_cipher2(char *pkt);
//void _exit(int status){}


/* These Motorola Basic Privacy keys are sampled manually from silent
   frames in the air, so they are imperfect and likely contain flipped
   bits.  A better method would be to extract the complete sequence from
   either motorola firmware or automatically fetch them from the first
   frame of a transmission. 
 */ 
const char* getmotorolabasickey(int i){
  switch(i&0xFF){
  case 1:
    return "\x1F\x00\x1F\x00\x1F\x00\x00";
  case 2:
    return "\xE3\x00\xE3\x00\xE3\x00\x01";
  case 3:
    return "\xFC\x00\xFC\x00\xFC\x00\x01";
  case 4:
    return "\x25\x03\x25\x03\x25\x03\x00";
  case 5:
    return "\x3A\x03\x3A\x03\x3A\x03\x00";
  case 6:
    return "\xC6\x03\xC6\x03\xC6\x03\x01";
  case 7:
    return "\xD9\x03\xD9\x03\xD9\x03\x01";
  case 8:
    return "\x4A\x05\x4A\x05\x4A\x05\x00";
  case 9:
    return "\x55\x05\x55\x05\x55\x05\x00";
  case 10:
    return "\xA9\x05\xA9\x05\xA9\x05\x01";
  case 11:
    return "\xB6\x05\xB6\x05\xB6\x05\x01";
  case 12:
    return "\x6F\x06\x6F\x06\x6F\x06\x00";
  case 13:
    return "\x70\x06\x70\x06\x70\x06\x00";
  case 14:
    return "\x8C\x06\x8C\x06\x8C\x06\x01";
  case 15:
    return "\x93\x06\x93\x06\x93\x06\x01";
  case 16:
    return "\x26\x08\x26\x18\x26\x18\x00";
//List gets sparse after here.
  case 32:
    return "\x4B\x08\x4B\x28\x4B\x28\x00";
  case 55:
    return "\xB4\x03\xB4\x33\xB4\x33\x01";
  case 63:
    return "\xFE\x06\xFE\x36\xFE\x36\x01";
  case 64:
    return "\x2B\x09\x2B\x49\x2B\x49\x00";
  case 69:
    return "\x11\x0A\x11\x4A\x11\x4A\x00";
  case 85:
    return "\x37\x02\x37\x52\x37\x52\x00";
  case 100:
    return "\x45\x02\x45\x62\x45\x62\x00";
  case 101:
    return "\x5A\x02\x5A\x62\x5A\x62\x00";
  case 114:
    return "\xA5\x09\xA5\x79\xA5\x79\x01";
  case 127:
    return "\xD5\x0F\xD5\x7F\xD5\x7F\x01";
  case 128:
    return "\x4D\x09\x4D\x89\x4D\x89\x00";
  case 144:
    return "\x6B\x01\x6B\x91\x6B\x91\x00";
  case 170:
    return "\xAF\x04\xAF\xA4\xAF\xA4\x01";
  case 176:
    return "\x20\x09\x20\xB9\x20\xB9\x00";
  case 192:
    return "\x66\x00\x66\xC0\x66\xC0\x00";
  case 200:
    return "\x2C\x05\x2C\xC5\x2C\xC5\x00";
  case 208:
    return "\x84\x00\x84\xD0\x84\xD0\x01";
  case 240:
    return "\x0B\x00\x0B\xF0\x0B\xF0\x00";
  case 250:
    return "\xA2\x05\xA2\xF5\xA2\xF5\x01";
  case 255:
    return "\x98\x06\x98\xF6\x98\xF6\x01";
  default:
    //printf("\nERROR: Motorola Basic Key %d is unknown.\n",i);
    return "\x00\x00\x00\x00\x00\x00\x00";
  }
}

/* This hook intercepts calls to aes_cipher(), which is used to turn
   the 128-bit Enhanced Privacy Key into a 49-bit sequence that gets
   XORed with the audio before transmission and after reception.
   
   By changing the output to match Motorola's Basic Privacy, we can
   patch the MD380 to be compatible with a Motorola network.
   
   The function is also used for two startup checks, presumably
   related to the ALPU-MP copy protection chip.  If those checks are
   interfered with, the radio will boot to a blank white screen.
 */
char *aes_cipher_hook(char *pkt){
  char *res;
  int i, sum=0,b=0;
 
  
  //Sum all the the first byte, looking for near-empty keys.
  for(i=1;i<16;i++)
    sum|=pkt[i];
  if(!sum){
    res = getmotorolabasickey(pkt[0]);
    for(b=0; b<7; b++){
        pkt[b]=res[b];
    }
     return pkt;
  }
  
  res=aes_cipher(pkt);

  return res;
}
/*
char *aes_cipher_hook2(char *pkt){
  char *res;
  int i, sum=0,b=0;
  char tt=pkt[0];
 
  
  //Sum all the the first byte, looking for near-empty keys.
  for(i=1;i<16;i++)
    sum|=pkt[i];

  //if(!sum){

    for(b=0; b<7; b++){
        pkt[b]=getmotorolabasickey(1)[b];
    }
    //memcpy(pkt,getmotorolabasickey(pkt[0]),7);
    
    return pkt;
  //}
  
  res=aes_cipher(pkt);

  return res;
}*/


static void do_jump(uint32_t stacktop, uint32_t entrypoint);

#define MFGR_APP_LOAD_ADDRESS     0x0800C000
#define SIDELOAD_RESET_VECTOR     8
#define SIDELOAD_APP_LOAD_ADDRESS 0x080BF000

static void abort_to_mfgr_app(void) {
	const uint32_t *app_base = (const uint32_t *)MFGR_APP_LOAD_ADDRESS;
	SCB->VTOR = MFGR_APP_LOAD_ADDRESS;
	do_jump(app_base[0], app_base[SIDELOAD_RESET_VECTOR]);
}

static void do_jump(uint32_t stacktop, uint32_t entrypoint)
{
	asm volatile(
		"msr msp, %0	\n"
		"bx	%1	\n"
		: : "r" (stacktop), "r" (entrypoint) : );
	// just to keep noreturn happy
	for (;;) ;
}

int main(void) {
  abort_to_mfgr_app();

}