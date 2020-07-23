#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from __future__ import print_function

import argparse
import binascii
import struct
import sys


class MD380FW(object):
    # The stream cipher of MD-380 OEM firmware updates boils down
    # to a cyclic, static XOR key block, and here it is:
    key = 'A2FABB4B908F172096364384F7AC4E55EAE5B43655B939E2D8DA18C00D095DB80E89904638D493CC2F8ECD2D22B78997512498A0CC303E957DAF4C0E682389C6323356AAE0589230E2DABCEA50FB575B73719309871A29D3BFEC87858A2B2DAA15DE57A21183DCF4B60256E508E0834959B5EB990FE0C346A779124DFA87120CBF73D95352BD38BFB4EEE443D2CED3080AD6E977EBE8D4943C3E358D40A1009239DB25E82B6E7039E286AD2F362D11418EBED5CCA39C24658723376EE5DFBFE78AFC838724FE4A0B4AB3FBCFBD65039BEE53F7BFC0637A628E11621770AB16B1BAC03A59C6D68FDDF45B144BEEDE72BF317F9679C9A4A0325BEEFCB0696CCE99D20E9485985C0756E66741CC520025545F29FC2146C95C7EF6A44E635989AF46D9CDD73323F9791F2AC0CA7A6F34E60381396FE0BF3977EE6519A056C76C8161D7E74C8DED15AEE0C84CF77CD0E07B749D9638DEBD5CB929B2373AB13B7C0C91D5433BB880196F40C6F510FBFA6EAD4EBE2A9F42C79AE9D8E5E4639D3D21187FD9C9ECDF646B82E72EA25C1E77444439E9DCEB35665BD1A2040A644256C36CD2EE61A6281F75AF7E083B240ECDCC08DF289466DE21073730199085C70DCAD13319F3B3BB3B9EC0AD5AA7B0F2876CC1E5823A56668006E4292B5E0E54EB9F0F4A646759C1404D7B1B2ED048F32A8E36F600B704F40BC0A036435C471377A8EEBED6A5E162B4ECAA718B9D3439409930B8A8F1B8B14B9E32FF6872782A394E3638779693C521E213567AF6BBEB51F577D384D1BAC4C706642BA288E8C1B9F9AE5F5020B6130E977F7301C32731E309D3F09C3F51560761FC63F986E00180121FDC682C94730473B5702BECBE34803F0CB7F624C68F9418C34E7654A81115FF5156C8A3730E8ADE7FF4FD5AC91CAFFEE9CF9C666196F591819520DA881A002A0C76766B9C0C2840A3A781F38F11F9AF33E196EF6A94B236FEDF0001C844CAF918E47C6E57946601EA32BEA05A3AE4B8B294EAA529B0546E01D51CAFAFB6FAD63C47E292EBCECD891C3DBC4A70BFFA822E91A272E61362A0541F7ECD869918284147AEC1A2E3E440016F84D71AC9C3756F7FC63DE8E46436BD642E449514AC57F08DEAE2C2FB338F60711D31A080C6F93C075CEE784CE397054C32FA24503FCB0FC19DDD943D43DC03EA8F3E4A0B8B775FD16E6CDE73662BF48194D97B7558EB668BD09A60D29B90B083E3E860929A559E8403A16280755A51A85CC8E2AA8021BF918A006EE2C41430E42015293F7CFDC2C824744C9C988CE66C90AEA0173ED5E07ED3F9059444CF4BB44EAFEE38B8D59347D8CDE3EE582979723A75FEE51A6D92F8B36D6E10A528C89C769DF7A5D647D8A62794709F3C99D3656104443C9C529DA73342F27F6E8971439EC78CAF5EBA5B9019B13BD6CD44BCEB0E43BA434DECC935'.decode('hex')

    def __init__(self, base_address=0x800c000):
        self.magic = b'OutSecurityBin'
        self.jst = b'MD-9600\x00\x00'
        self.foo = '\x30\x02\x00\x30\x00\x40\x00\x47'
        self.bar = ('\x01\x14\x02\x03\x04\x05\x06\x07'
                    '\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f'
                    '\x10\x11\x12\x13\x14\x15\x16\x17'
                    '\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f'
                    '\x20')
        self.foob = ('\x02\x00\x00\x00\x00\x00\x06\x00')
        self.start = base_address
        self.app = None
        self.footer = 'OutputBinDataEnd'
        self.header_fmt = '<16s9s7s16s33s43s8sLLL112s'
        self.footer_fmt = '<240s16s'
        self.rsrcSize = 0x59800

    def pad(self, align=512, byte=b'\xff'):
        pad_length = (align - len(self.app) % align) % align
        self.app += byte * pad_length

    def wrap(self):
        bin = b''
        header = struct.Struct(self.header_fmt)
        footer = struct.Struct(self.footer_fmt)
        self.pad()
        app = self.crypt(self.app)
        bin += header.pack(
            self.magic, self.jst, b'\xff' * 7, self.foo,
            self.bar, b'\xff' * 43, self.foob, self.rsrcSize, self.start, len(app)-self.rsrcSize,
                                  b'\xff' * 112)
        bin += self.crypt(self.app)
        bin += footer.pack(b'\xff' * 240, self.footer)
        return bin

    def unwrap(self, img):
        header = struct.Struct(self.header_fmt)
        header = header.unpack(img[:256])

        print(header)
        self.start = header[6]
        rsrc_len = header[7]
        print('rsrc_len %x' % rsrc_len)
        prg_len = header[9]
        print('prg_len %x' % prg_len)
        app_len = rsrc_len + prg_len
        print('applen %x' % app_len)
        self.app = self.crypt(img[256:256 + app_len])

        assert header[0].startswith(self.magic)
        assert header[1].startswith(self.jst)
        assert header[3].startswith(self.foo)
        #assert header[4] == self.bar
        #assert 0x8000000 <= header[6] < 0x8200000
        #assert header[7] == len(img) - 512
        header_rsrc_thingy = self.app[:rsrc_len]
        with open("RT90_header_rsrc.bin", 'wb') as f:
            f.write(header_rsrc_thingy)
        self.app = self.app[rsrc_len:]

    def crypt(self, data):
        return self.xor(data, self.key)

    @staticmethod
    def xor(a, b):
        # FIXME: optimized version
        out = b''
        l = max(len(a), len(b))
        for i in range(l):
            out += chr(ord(a[i % len(a)]) ^ ord(b[i % len(b)]))
        return out


def main():
    def hex_int(x):
        return int(x, 0)

    parser = argparse.ArgumentParser(description='Wrap and unwrap MD-380 firmware')
    parser.add_argument('--wrap', '-w', dest='wrap', action='store_true',
                        default=False,
                        help='wrap app into firmware image')
    parser.add_argument('--unwrap', '-u', dest='unwrap', action='store_true',
                        default=False,
                        help='unwrap app from firmware image')
    parser.add_argument('--addr', '-a', dest='addr', type=hex_int,
                        default=0x800c000,
                        help='base address in flash')
    parser.add_argument('--offset', '-o', dest='offset', type=hex_int,
                        default=0,
                        help='offset to skip in app binary')
    parser.add_argument('input', nargs=1, help='input file')
    parser.add_argument('output', nargs=1, help='output file')
    args = parser.parse_args()

    if not (args.wrap ^ args.unwrap):
        sys.stderr.write('ERROR: --wrap or --unwrap?')
        sys.exit(5)

    print('DEBUG: reading "%s"' % args.input[0])
    with open(args.input[0], 'rb') as f:
        input = f.read()

    

    if args.wrap:
	
        with open('RT90_header.bin', 'rb') as f:
            front = f.read()
            input = front + input;
	
        if args.offset > 0:
            print('INFO: skipping 0x%x bytes in input file' % args.offset)
        md = MD380FW(args.addr)
        md.app = input[args.offset:]
        if len(md.app) == 0:
            sys.stderr.write('ERROR: seeking beyond end of input file\n')
            sys.exit(5)
        output = md.wrap()
        print('INFO: base address 0x{0:x}'.format(md.start))
        print('INFO: length 0x{0:x}'.format(len(md.app)))

    elif args.unwrap:
        md = MD380FW()
        try:
            md.unwrap(input)
        except AssertionError:
            sys.stderr.write('WARNING: Funky header:\n')
            for i in range(0, 256, 16):
                hl = binascii.hexlify(input[i:i + 16])
                hl = ' '.join(hl[i:i + 2] for i in range(0, 32, 2))
                sys.stderr.write(hl + '\n')
            sys.stderr.write('Trying anyway.\n')
        output = md.app
        #print('INFO: base address 0x{0:x}'.format(md.start))
        print('INFO: length 0x{0:x}'.format(len(md.app)))

    print('DEBUG: writing "%s"' % args.output[0])

    with open(args.output[0], 'wb') as f:
        f.write(output)



if __name__ == "__main__":
    main()
