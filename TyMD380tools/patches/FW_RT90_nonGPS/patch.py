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
	
	
    # freeing ~200k for code patches
    patcher.ffrange(0x080BD7F0, 0x080C4800)

    # This mirrors the RESET vector to 0x080C020, for use in booting.
    patcher.setword(0x0800C020,patcher.getword(0x0800C004))

    # This makes RESET point to our stub below.
    patcher.setword(0x0800C004, 0x080BD800 + 1)

    # This stub calls the target RESET vector,
    # if it's not FFFFFFFF.
    patcher.sethword(0x080BD800, 0x4840)
    patcher.sethword(0x080BD802, 0x2100)
    patcher.sethword(0x080BD804, 0x3901)
    patcher.sethword(0x080BD806, 0x4508)
    patcher.sethword(0x080BD808, 0xd100)
    patcher.sethword(0x080BD80a, 0x483c)
    patcher.sethword(0x080BD80c, 0x4700)

    # Stores the RESET handler for our stub.
    patcher.setword(0x080BD8FC, patcher.getword(0x0800C020))
	#80BD900
    patcher.export("patched.img")
