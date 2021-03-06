#!/usr/bin/env python2
# -*- coding: utf-8 -*-

# Vocoder Patch for MD380 Firmware
# Applies to version D013.020

from Patcher import Patcher

# Match all public calls.
monitormode = False
# Match all private calls.
monitormodeprivate = True

if __name__ == '__main__':
    print("Creating patches from unwrapped.img.")
    patcher = Patcher("unwrapped.img")
	
	#test gps
    #patcher.nopout((0x800C278 + 0))
    #patcher.nopout((0x800C278 + 2))
	

    # bypass vocoder copy protection on D013.020

    #patcher.nopout((0x08011444))
    #patcher.nopout((0x08011444) + 0x2)
	
	#test manual dial group callable
    #patcher.sethword(0x08023170, 0x2204)
    #patcher.sethword(0x08012912, 0x2804)
    #patcher.sethword(0x080EB1B0, 0x00FF)
    #patcher.nopout((0x08028F88))
   # patcher.nopout((0x08028F88 + 0x2))
   # patcher.nopout((0x08028F88 + 0x4))
    #patcher.nopout((0x08028F88 + 0x6))
   # patcher.nopout((0x08028F88 + 0x8))
   # patcher.nopout((0x08028F88 + 0xA))
   
    #test site roaming
    #patcher.sethword(0x0801C774, 0x2001)
    #record
    #patcher.sethword(0x0801C7A8, 0x2001)
    #Morola/PC-Audio
    #patcher.sethword(0x0801C6FE, 0x2001)
    #patcher.sethword(0x0801C718, 0x11B0) #fix a typo..
	
	#0x08098800
    # freeing ~200k for code patches
    patcher.ffrange(0x80986E8, 0x80CCF54)

    # This mirrors the RESET vector to 0x080C020, for use in booting.
    patcher.setword(0x0800C020,patcher.getword(0x0800C004), 0x00000000)

    # This makes RESET point to our stub below.
    patcher.setword(0x0800C004, 0x08098700 + 1)

    # This stub calls the target RESET vector,
    # if it's not FFFFFFFF.
    patcher.sethword(0x08098700, 0x4840)
    patcher.sethword(0x08098702, 0x2100)
    patcher.sethword(0x08098704, 0x3901)
    patcher.sethword(0x08098706, 0x4508)
    patcher.sethword(0x08098708, 0xd100)
    patcher.sethword(0x0809870a, 0x483c)
    patcher.sethword(0x0809870c, 0x4700)

    # Stores the RESET handler for our stub.
    patcher.setword(0x080987fc, patcher.getword(0x0800C020), 0xFFFFFFFF)
	
    patcher.export("patched.img")
