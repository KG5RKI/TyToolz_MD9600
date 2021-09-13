int __fastcall F_4315(int a1, int a2, int a3, int a4)
{
    int v4;               // r2
    int v5;               // r3
    int v6;               // r2
    int v7;               // r3
    int v8;               // r2
    int v9;               // r3
    int v10;              // r2
    int v11;              // r3
    int v12;              // r0
    unsigned __int8 v13;  // r0
    int v14;              // r0
    int result;           // r0
    int v16;              // r2
    int v17;              // r3
    int v18;              // r2
    int v19;              // r3
    int v20;              // r2
    int v21;              // r3
    int v22;              // r2
    int v23;              // r3
    int v24;              // r2
    int v25;              // r3
    int v26;              // r2
    int v27;              // r3
    int v28;              // r2
    int v29;              // r3
    int v30;              // r5
    int v31;              // r5
    unsigned __int16 v32; // r0

    sub_8024D98(word_2001CDA0, a2, a3, a4);
    word_2001CDA0 = 0;
    sub_8024D98(word_2001CDA8, (int)&word_2001CDA0, v4, v5);
    word_2001CDA8 = 0;
    sub_8024D98(word_2001CDAA, (int)&word_2001CDA8, v6, v7);
    word_2001CDAA = 0;
    sub_8024D98(word_2001CD9C, (int)&word_2001CDAA, v8, v9);
    word_2001CD9C = 0;
    if (byte_2001CF79 == 3 && ((unsigned __int8)byte_2001CC65 >> 5) & 1 || byte_2001CF79 == 4 && ((unsigned __int8)byte_2001CC65 >> 6) & 1)
    {
        gfx_set_bg_color(0xFFFFFF);
        sub_8029C7C();
        gfx_set_fg_color(0xFFFFFF);
        gfx_blockfill(0, 15, 1, 63);
        gfx_set_fg_color(0);
        gfx_select_font(&gfx_font_small);
        word_2001C440[0] = 'I';
        word_2001C442[0] = 'D';
        word_2001C444 = ':';
        word_2001C446 = 0;
        sub_802F934((unsigned __int16 *)word_2001C440, 2, 15, 3);
        if (md380_lastheard_dmrid)
            word_2001C5A4[(unsigned __int8)sub_802F744(md380_lastheard_dmrid & 0xFFFFFF, (int)word_2001C5A4)] = 0;
        else
            word_2001C5A4[0] = 0;
        gfx_drawtext2(word_2001C5A4, 20, 15, 127);
        gfx_set_fg_color(0xFFFFFF);
        gfx_set_fg_color(0);
        word_2001C440[0] = 'C';
        word_2001C442[0] = 'C';
        word_2001C444 = ':';
        word_2001C446 = 0;
        sub_802F934((unsigned __int16 *)word_2001C440, 2, 27, 3);
        word_2001C5A4[(unsigned __int8)sub_802F744((unsigned __int8)byte_2001CF57, (int)word_2001C5A4)] = 0;
        v12 = sub_802F934((unsigned __int16 *)word_2001C5A4, 20, 27, 2);
        byte_2001CEDD = sub_802F348(v12);
        gfx_set_fg_color(0xFFFFFF);
        gfx_blockfill((unsigned __int8)byte_2001CEDD, 27, (unsigned __int8)byte_2001CEDD + 5, 39);
        gfx_set_fg_color(0);
        word_2001C440[0] = ' ';
        word_2001C442[0] = ' ';
        word_2001C444 = ' ';
        word_2001C446 = ' ';
        word_2001C448[0] = ' ';
        word_2001C44A = 0;
        byte_2001CEDD = sub_802F348(0);
        sub_802F934((unsigned __int16 *)word_2001C440, (unsigned __int8)byte_2001CEDD + 5, 27, 5);
        word_2001C5A4[0] = 0;
        v13 = sub_802F348(0);
        byte_2001CEDD = v13;
        v14 = sub_802F934((unsigned __int16 *)word_2001C5A4, v13, 27, 2);
        byte_2001CEDD = sub_802F348(v14);
        gfx_set_fg_color(0xFFFFFF);
        gfx_blockfill((unsigned __int8)byte_2001CEDD, 27, (unsigned __int8)byte_2001CEDD + 5, 39);
        gfx_set_fg_color(0);
        word_2001C440[0] = 'T';
        word_2001C442[0] = 'y';
        word_2001C444 = 'p';
        word_2001C446 = 'e';
        word_2001C448[0] = ':';
        word_2001C44A = 0;
        byte_2001CEDD = sub_802F348(0);
        sub_802F934((unsigned __int16 *)word_2001C440, (unsigned __int8)byte_2001CEDD + 5, 27, 5);
        if ((unsigned __int8)byte_2001CF2A >> 4 == 1)
        {
            word_2001C5A4[0] = 'G';
            word_2001C5A6 = 0;
        }
        else if ((unsigned __int8)byte_2001CF2A >> 4 == 2)
        {
            word_2001C5A4[0] = 'P';
            word_2001C5A6 = 0;
        }
        else
        {
            word_2001C5A4[0] = 'A';
            word_2001C5A6 = 'L';
            word_2001C5A8 = 'L';
            word_2001C5AA[0] = 0;
        }
        byte_2001CEDD = sub_802F348(0);
        gfx_drawtext2(word_2001C5A4, (unsigned __int8)byte_2001CEDD, 27, 127);
        gfx_set_fg_color(0xFFFFFF);
        gfx_set_fg_color(0);
        word_2001C440[0] = 'T';
        word_2001C442[0] = 'x';
        word_2001C444 = 'C';
        word_2001C446 = 'o';
        word_2001C448[0] = 'n';
        word_2001C44A = 't';
        word_2001C44C = 'a';
        word_2001C44E = 'c';
        word_2001C450 = 't';
        word_2001C452 = ':';
        word_2001C454 = 0;
        gfx_drawtext2(word_2001C440, 2, 39, 127);
        if (md380_lastheard_dest)
            word_2001C5A4[(unsigned __int8)sub_802F744(md380_lastheard_dest & 0xFFFFFF, (int)word_2001C5A4)] = 0;
        else
            word_2001C5A4[0] = 0;
        byte_2001CEDD = sub_802F348(0);
        gfx_drawtext2(word_2001C5A4, (unsigned __int8)byte_2001CEDD, 39, 127);
        gfx_set_fg_color(0xFFFFFF);
        gfx_blockfill(2, 51, 8, 63);
        gfx_set_fg_color(0);
        word_2001C440[0] = 'T';
        word_2001C442[0] = 0;
        sub_802F934((unsigned __int16 *)word_2001C440, 2, 51, 5);
        sub_800E094(word_2001C440, dword_2001C0C4);
        gfx_drawtext4(word_2001C440, 9, 51, 63, 9);
        gfx_set_fg_color(0xFFFFFF);
        gfx_blockfill(64, 51, 73, 63);
        gfx_set_fg_color(0);
        word_2001C440[0] = 'R';
        word_2001C442[0] = 0;
        sub_802F934((unsigned __int16 *)word_2001C440, 66, 51, 5);
        sub_800E094(word_2001C440, dword_2001C0C0);
        gfx_drawtext4(word_2001C440, 74, 51, 127, 9);
        gfx_set_fg_color(0);
        result = gfx_set_bg_color(0xFFFFFF);
    }
    else if (((unsigned __int8)byte_2001BB56 >> 6) & 1)
    {
        sub_8024D98(word_2001CDA0, (int)&word_2001CD9C, v10, v11);
        word_2001CDA0 = 0;
        sub_8024D98(word_2001CDA8, (int)&word_2001CDA0, v16, v17);
        word_2001CDA8 = 0;
        sub_8024D98(word_2001CDAA, (int)&word_2001CDA8, v18, v19);
        word_2001CDAA = 0;
        sub_8024D98(word_2001CD9C, (int)&word_2001CDAA, v20, v21);
        word_2001CD9C = 0;
        gfx_set_fg_color(0);
        gfx_set_bg_color(0xFFFFFF);
        if (!word_2001CDA2)
        {
            gfx_set_fg_color(0);
            word_2001CDA2 = sub_8035080(0, 15, 128, 1, 352, 6, &unk_8033370, 14);
            word_2001CDA4 = sub_8035080(0, 15, 128, 1, 352, 6, &unk_8033370, 14);
            sub_8038F9E(word_2001CDA2, 0xFFFFFF, v22, v23);
            sub_8038F9E(word_2001CDA4, 0xFFFFFF, v24, v25);
            sub_805496C(word_2001CDA2, 0, v26, v27);
            sub_805496C(word_2001CDA4, 0, v28, v29);
        }
        sub_8029C7C();
        gfx_set_fg_color(0xFFFFFF);
        gfx_blockfill(2, 15, 157, 15);
        gfx_set_fg_color(0);
        gfx_blockfill(0, 14, 127, 14);
        if (byte_2001CF29 == 8 || byte_2001CF2A == 32 || byte_2001CF2A == 16 && ((unsigned __int8)byte_2001CC5B >> 2) & 1)
        {
            if (byte_2001CF29 == 7)
                v30 = current_contact;
            else
                v30 = md380_lastheard_dmrid;
            word_2001C5A4[(unsigned __int8)sub_802F744(v30 & 0xFFFFFF, (int)word_2001C5A4)] = 0;
            gfx_set_fg_color(0);
            gfx_drawtext2(word_2001C5A4, 0, 16, 128);
            gfx_set_fg_color(0xFFFFFF);
            gfx_blockfill(0, 31, 128, 31);
            gfx_set_fg_color(0);
        }
        else
        {
            sub_80257BC(2, 5, 0, 128, 0);
        }
        gfx_set_fg_color(0xFFFFFF);
        gfx_blockfill(59, 47, 127, 63);
        gfx_blockfill(0, 62, 25, 63);
        gfx_set_fg_color(0);
        gfx_set_bg_color(0xFFFFFF);
        if (byte_2001CE78)
        {
            gfx_set_fg_color(0xFFFFFF);
            gfx_blockfill(0, 47, 24, 63);
        }
        else
        {
            gfx_drawchar_pos('C', 0, 47);
            gfx_drawchar_pos('H', 8, 47);
            if (byte_2001CC7C >= 0)
                gfx_drawchar_pos('B', 16, 47);
            else
                gfx_drawchar_pos('A', 16, 47);
        }
        if (byte_2001CF2A == 32)
        {
            byte_2001CEA1 = 5;
            gfx_drawbmp(&unk_20000D5C, 114, 32);
            gfx_set_fg_color(0);
            gfx_drawtext2(*((_DWORD *)&unk_20000128 + dword_2001CB80 + 112), 0, 32, 113);
        }
        else if (byte_2001CF2A == 48)
        {
            byte_2001CEA1 = 4;
            gfx_drawbmp(&unk_20000D48, 114, 32);
            gfx_set_fg_color(0);
            gfx_drawtext2(*((_DWORD *)&unk_20000128 + dword_2001CB80 + 68), 0, 32, 113);
        }
        else if (byte_2001CF2A == 16 && ((unsigned __int8)byte_2001CC5B >> 2) & 1)
        {
            byte_2001CEA1 = 4;
            gfx_drawbmp(&unk_20000D48, 114, 32);
            gfx_set_fg_color(0);
            gfx_drawtext2(*((_DWORD *)&unk_20000128 + dword_2001CB80 + 281), 0, 32, 113);
        }
        else
        {
            if (word_2001CD7E)
            {
                get_contact_from_index((unsigned __int16)word_2001CD7E);
            }
            else
            {
                word_2001C5A4[0] = 32;
                word_2001C5A6 = 0;
            }
            byte_2001CEA1 = 4;
            gfx_drawbmp(&unk_20000D48, 114, 32);
            gfx_set_fg_color(0);
            gfx_drawtext2(word_2001C5A4, 0, 32, 113);
        }
        gfx_set_fg_color(0xFFFFFF);
        gfx_blockfill(60, 47, 127, 63);
        gfx_blockfill(114, 43, 127, 46);
        gfx_set_fg_color(0);
        if (byte_2001CF29 == 7)
        {
            gfx_drawbmp(&unk_80B8D38, 24, 47);
        }
        else if (byte_2001CF29 == 8)
        {
            gfx_drawbmp(&unk_80B8D24, 24, 47);
        }
        byte_2001CE97 = 1;
        if (byte_2001CF29 == 8 || byte_2001CF2A == 32 || (result = (unsigned __int8)byte_2001CF2A, byte_2001CF2A == 16) && (result = ((unsigned __int8)byte_2001CC5B >> 2) & 1) != 0)
        {
            if (byte_2001CF29 == 7)
            {
                v31 = current_contact;
            }
            else
            {
                byte_2001CC5B &= 0xFBu;
                v31 = md380_lastheard_dmrid;
            }
            if (byte_2001CF2A == 16 && ((unsigned __int8)byte_2001CC5B >> 2) & 1)
                v32 = sub_80336EC(v31);
            else
                v32 = sub_8033624(v31);
            if (v32)
                sub_802CDCC(v32);
            else
                word_2001C5A4[(unsigned __int8)sub_802F744(v31 & 0xFFFFFF, (int)word_2001C5A4)] = 0;
            gfx_set_fg_color(0);
            gfx_drawtext2(word_2001C5A4, 0, 16, 128);
            gfx_set_fg_color(0xFFFFFF);
            gfx_blockfill(0, 31, 128, 31);
            result = gfx_set_fg_color(0);
        }
    }
    else
    {
        byte_2001CE97 = 2;
        result = draw_screen_blue(0xFFFFFF);
    }
    return result;
}