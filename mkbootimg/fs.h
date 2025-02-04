/*
 * mkbootimg/fs.h
 *
 * Copyright (C) 2017 - 2021 bzt (bztsrc@gitlab)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This file is part of the BOOTBOOT Protocol package.
 * @brief File system drivers registry
 *
 */

void cpio_open(gpt_t *gpt_entry);
void cpio_add(struct stat *st, char *name, unsigned char *content, int size);
void cpio_close();

void tar_open(gpt_t *gpt_entry);
void tar_add(struct stat *st, char *name, unsigned char *content, int size);
void tar_close();

void fsz_open(gpt_t *gpt_entry);
void fsz_add(struct stat *st, char *name, unsigned char *content, int size);
void fsz_close();

void ech_open(gpt_t *gpt_entry);
void ech_add(struct stat *st, char *name, unsigned char *content, int size);
void ech_close();

void mnx_open(gpt_t *gpt_entry);
void mnx_add(struct stat *st, char *name, unsigned char *content, int size);
void mnx_close();

void fat_open(gpt_t *gpt_entry);
void fat_add(struct stat *st, char *name, unsigned char *content, int size);
void fat_close();

void ext_open(gpt_t *gpt_entry);
void ext_add(struct stat *st, char *name, unsigned char *content, int size);
void ext_close();

void len_open(gpt_t *gpt_entry);
void len_add(struct stat *st, char *name, unsigned char *content, int size);
void len_close();

void jamesm_open(gpt_t *gpt_entry);
void jamesm_add(struct stat *st, char *name, unsigned char *content, int size);
void jamesm_close();

/*** specify file system drivers and GPT file system types here ***/
/* for simplicity, first list the ones with drivers, and types only afterwards */
fsdrv_t fsdrv[] = {
    /* not on partitions, initrd only */
    { "jamesm",                  {0}, jamesm_open, jamesm_add, jamesm_close },
    { "cpio",                    {0}, cpio_open, cpio_add, cpio_close },
    /* for both partitions and initrds */
    { "tar",                     { 0x65706154, 0x4120, 0x6372, { 0x68,0x69,0x76,0x65,0x20,0x46,0x53,0x20} }, tar_open, tar_add, tar_close },
    { "echfs",                   { 0x66686365, 0x6973, 0x7673, { 0x65,0x72,0x79,0x6C,0x61,0x6D,0x65,0x00} }, ech_open, ech_add, ech_close },
    { "minix",                   { 0xB7AADF00, 0xDE27, 0x11CA, { 0xA5,0x74,0x56,0x72,0x69,0x6A,0x65,0x55} }, mnx_open, mnx_add, mnx_close },
    { "fat",                     { 0xEBD0A0A2, 0xB9E5, 0x4433, { 0x87,0xC0,0x68,0xB6,0xB7,0x26,0x99,0xC7} }, fat_open, fat_add, fat_close },
    { "ext2",                    { 0x0FC63DAF, 0x8483, 0x4772, { 0x8E,0x79,0x3D,0x69,0xD8,0x47,0x7D,0xE4} }, ext_open, ext_add, ext_close },
    { "lean",                    { 0xBB5A91B0, 0x977E, 0x11DB, { 0xB6,0x06,0x08,0x00,0x20,0x0C,0x9A,0x66} }, len_open, len_add, len_close },
    { "FS/Z",                    { 0x5A2F534F, 0x0000, 0x5346, { 0x2F,0x5A,0x00,0x00,0x00,0x00,0x00,0x00} }, fsz_open, fsz_add, fsz_close },
    /* partition type only, without drivers */
    { "OS/Z usr (x86_64)",       { 0x5A2F534F, 0x8664, 0x5346, { 0x2F,0x5A,0x00,0x00,0x75,0x73,0x72,0x00} }, NULL, NULL, NULL },
    { "OS/Z usr (AArch64)",      { 0x5A2F534F, 0xAA64, 0x5346, { 0x2F,0x5A,0x00,0x00,0x75,0x73,0x72,0x00} }, NULL, NULL, NULL },
    { "OS/Z usr (RiscV64)",      { 0x5A2F534F, 0x5064, 0x5346, { 0x2F,0x5A,0x00,0x00,0x75,0x73,0x72,0x00} }, NULL, NULL, NULL },
    { "OS/Z var",                { 0x5A2F534F, 0x0000, 0x5346, { 0x2F,0x5A,0x00,0x00,0x76,0x61,0x72,0x00} }, NULL, NULL, NULL },
    { "OS/Z home",               { 0x5A2F534F, 0x0000, 0x5346, { 0x2F,0x5A,0x00,0x00,0x68,0x6F,0x6D,0x65} }, NULL, NULL, NULL },
    { "OS/Z swap",               { 0x5A2F534F, 0x0000, 0x5346, { 0x2F,0x5A,0x00,0x00,0x73,0x77,0x61,0x70} }, NULL, NULL, NULL },
    { "ZFS",                     { 0x6A898CC3, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "ntfs",                    { 0xEBD0A0A2, 0xB9E5, 0x4433, { 0x87,0xC0,0x68,0xB6,0xB7,0x26,0x99,0xC7} }, NULL, NULL, NULL },
    { "ufs",                     { 0x516E7CB6, 0x6ECF, 0x11D6, { 0x8F,0xF8,0x00,0x02,0x2D,0x09,0x71,0x2B} }, NULL, NULL, NULL },
    { "p9",                      { 0xC91818F9, 0x8025, 0x47AF, { 0x89,0xD2,0xF0,0x30,0xD7,0x00,0x0C,0x2C} }, NULL, NULL, NULL },
    { "Intel Fast Flash",        { 0xD3BFE2DE, 0x3DAF, 0x11DF, { 0xBA,0x40,0xE3,0xA5,0x56,0xD8,0x95,0x93} }, NULL, NULL, NULL },
    { "Sony boot partition",     { 0xF4019732, 0x066E, 0x4E12, { 0x82,0x73,0x34,0x6C,0x56,0x41,0x49,0x4F} }, NULL, NULL, NULL },
    { "Lenovo boot partition",   { 0xBFBFAFE7, 0xA34F, 0x448A, { 0x9A,0x5B,0x62,0x13,0xEB,0x73,0x6C,0x22} }, NULL, NULL, NULL },
    { "PowerPC PReP boot",       { 0x9E1A2D38, 0xC612, 0x4316, { 0xAA,0x26,0x8B,0x49,0x52,0x1E,0x5A,0x8B} }, NULL, NULL, NULL },
    { "ONIE boot",               { 0x7412F7D5, 0xA156, 0x4B13, { 0x81,0xDC,0x86,0x71,0x74,0x92,0x93,0x25} }, NULL, NULL, NULL },
    { "ONIE config",             { 0xD4E6E2CD, 0x4469, 0x46F3, { 0xB5,0xCB,0x1B,0xFF,0x57,0xAF,0xC1,0x49} }, NULL, NULL, NULL },
    { "Microsoft reserved",      { 0xE3C9E316, 0x0B5C, 0x4DB8, { 0x81,0x7D,0xF9,0x2D,0xF0,0x02,0x15,0xAE} }, NULL, NULL, NULL },
    { "Microsoft basic data",    { 0xEBD0A0A2, 0xB9E5, 0x4433, { 0x87,0xC0,0x68,0xB6,0xB7,0x26,0x99,0xC7} }, NULL, NULL, NULL },
    { "Microsoft LDM metadata",  { 0x5808C8AA, 0x7E8F, 0x42E0, { 0x85,0xD2,0xE1,0xE9,0x04,0x34,0xCF,0xB3} }, NULL, NULL, NULL },
    { "Microsoft LDM data",      { 0xAF9B60A0, 0x1431, 0x4F62, { 0xBC,0x68,0x33,0x11,0x71,0x4A,0x69,0xAD} }, NULL, NULL, NULL },
    { "Windows recovery",        { 0xDE94BBA4, 0x06D1, 0x4D40, { 0xA1,0x6A,0xBF,0xD5,0x01,0x79,0xD6,0xAC} }, NULL, NULL, NULL },
    { "IBM General Parallel Fs", { 0x37AFFC90, 0xEF7D, 0x4E96, { 0x91,0xC3,0x2D,0x7A,0xE0,0x55,0xB1,0x74} }, NULL, NULL, NULL },
    { "Microsoft Storage Spaces",{ 0xE75CAF8F, 0xF680, 0x4CEE, { 0xAF,0xA3,0xB0,0x01,0xE5,0x6E,0xFC,0x2D} }, NULL, NULL, NULL },
    { "HP-UX data",              { 0x75894C1E, 0x3AEB, 0x11D3, { 0xB7,0xC1,0x7B,0x03,0xA0,0x00,0x00,0x00} }, NULL, NULL, NULL },
    { "HP-UX service",           { 0xE2A1E728, 0x32E3, 0x11D6, { 0xA6,0x82,0x7B,0x03,0xA0,0x00,0x00,0x00} }, NULL, NULL, NULL },
    { "Linux swap",              { 0x0657FD6D, 0xA4AB, 0x43C4, { 0x84,0xE5,0x09,0x33,0xC8,0x4B,0x4F,0x4F} }, NULL, NULL, NULL },
    { "Linux filesystem",        { 0x0FC63DAF, 0x8483, 0x4772, { 0x8E,0x79,0x3D,0x69,0xD8,0x47,0x7D,0xE4} }, NULL, NULL, NULL },
    { "Linux server data",       { 0x3B8F8425, 0x20E0, 0x4F3B, { 0x90,0x7F,0x1A,0x25,0xA7,0x6F,0x98,0xE8} }, NULL, NULL, NULL },
    { "Linux root (x86)",        { 0x44479540, 0xF297, 0x41B2, { 0x9A,0xF7,0xD1,0x31,0xD5,0xF0,0x45,0x8A} }, NULL, NULL, NULL },
    { "Linux root (ARM)",        { 0x69DAD710, 0x2CE4, 0x4E3C, { 0xB1,0x6C,0x21,0xA1,0xD4,0x9A,0xBE,0xD3} }, NULL, NULL, NULL },
    { "Linux root (x86-64)",     { 0x4F68BCE3, 0xE8CD, 0x4DB1, { 0x96,0xE7,0xFB,0xCA,0xF9,0x84,0xB7,0x09} }, NULL, NULL, NULL },
    { "Linux root (ARM-64)",     { 0xB921B045, 0x1DF0, 0x41C3, { 0xAF,0x44,0x4C,0x6F,0x28,0x0D,0x3F,0xAE} }, NULL, NULL, NULL },
    { "Linux root (IA-64)",      { 0x993D8D3D, 0xF80E, 0x4225, { 0x85,0x5A,0x9D,0xAF,0x8E,0xD7,0xEA,0x97} }, NULL, NULL, NULL },
    { "Linux reserved",          { 0x8DA63339, 0x0007, 0x60C0, { 0xC4,0x36,0x08,0x3A,0xC8,0x23,0x09,0x08} }, NULL, NULL, NULL },
    { "Linux home",              { 0x933AC7E1, 0x2EB4, 0x4F13, { 0xB8,0x44,0x0E,0x14,0xE2,0xAE,0xF9,0x15} }, NULL, NULL, NULL },
    { "Linux RAID",              { 0xA19D880F, 0x05FC, 0x4D3B, { 0xA0,0x06,0x74,0x3F,0x0F,0x84,0x91,0x1E} }, NULL, NULL, NULL },
    { "Linux LVM",               { 0xE6D6D379, 0xF507, 0x44C2, { 0xA2,0x3C,0x23,0x8F,0x2A,0x3D,0xF9,0x28} }, NULL, NULL, NULL },
    { "Linux extended boot",     { 0xBC13C2FF, 0x59E6, 0x4262, { 0xA3,0x52,0xB2,0x75,0xFD,0x6F,0x71,0x72} }, NULL, NULL, NULL },
    { "FreeBSD data",            { 0x516E7CB4, 0x6ECF, 0x11D6, { 0x8F,0xF8,0x00,0x02,0x2D,0x09,0x71,0x2B} }, NULL, NULL, NULL },
    { "FreeBSD boot",            { 0x83BD6B9D, 0x7F41, 0x11DC, { 0xBE,0x0B,0x00,0x15,0x60,0xB8,0x4F,0x0F} }, NULL, NULL, NULL },
    { "FreeBSD swap",            { 0x516E7CB5, 0x6ECF, 0x11D6, { 0x8F,0xF8,0x00,0x02,0x2D,0x09,0x71,0x2B} }, NULL, NULL, NULL },
    { "FreeBSD UFS",             { 0x516E7CB6, 0x6ECF, 0x11D6, { 0x8F,0xF8,0x00,0x02,0x2D,0x09,0x71,0x2B} }, NULL, NULL, NULL },
    { "FreeBSD ZFS",             { 0x516E7CBA, 0x6ECF, 0x11D6, { 0x8F,0xF8,0x00,0x02,0x2D,0x09,0x71,0x2B} }, NULL, NULL, NULL },
    { "FreeBSD Vinum",           { 0x516E7CB8, 0x6ECF, 0x11D6, { 0x8F,0xF8,0x00,0x02,0x2D,0x09,0x71,0x2B} }, NULL, NULL, NULL },
    { "Apple HFS/HFS+",          { 0x48465300, 0x0000, 0x11AA, { 0xAA,0x11,0x00,0x30,0x65,0x43,0xEC,0xAC} }, NULL, NULL, NULL },
    { "Apple APFS",              { 0x7C3457EF, 0x0000, 0x11AA, { 0xAA,0x11,0x00,0x30,0x65,0x43,0xEC,0xAC} }, NULL, NULL, NULL },
    { "Apple UFS",               { 0x55465300, 0x0000, 0x11AA, { 0xAA,0x11,0x00,0x30,0x65,0x43,0xEC,0xAC} }, NULL, NULL, NULL },
    { "Apple RAID",              { 0x52414944, 0x0000, 0x11AA, { 0xAA,0x11,0x00,0x30,0x65,0x43,0xEC,0xAC} }, NULL, NULL, NULL },
    { "Apple RAID offline",      { 0x52414944, 0x5F4F, 0x11AA, { 0xAA,0x11,0x00,0x30,0x65,0x43,0xEC,0xAC} }, NULL, NULL, NULL },
    { "Apple boot",              { 0x426F6F74, 0x0000, 0x11AA, { 0xAA,0x11,0x00,0x30,0x65,0x43,0xEC,0xAC} }, NULL, NULL, NULL },
    { "Apple label",             { 0x4C616265, 0x6C00, 0x11AA, { 0xAA,0x11,0x00,0x30,0x65,0x43,0xEC,0xAC} }, NULL, NULL, NULL },
    { "Apple TV recovery",       { 0x5265636F, 0x7665, 0x11AA, { 0xAA,0x11,0x00,0x30,0x65,0x43,0xEC,0xAC} }, NULL, NULL, NULL },
    { "Apple Core storage",      { 0x53746F72, 0x6167, 0x11AA, { 0xAA,0x11,0x00,0x30,0x65,0x43,0xEC,0xAC} }, NULL, NULL, NULL },
    { "Solaris boot",            { 0x6A82CB45, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "Solaris root",            { 0x6A85CF4D, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "Solaris /usr & Apple ZFS",{ 0x6A898CC3, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "Solaris swap",            { 0x6A87C46F, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "Solaris backup",          { 0x6A8B642B, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "Solaris /var",            { 0x6A8EF2E9, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "Solaris /home",           { 0x6A90BA39, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "Solaris alternate sector",{ 0x6A9283A5, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "Solaris reserved 1",      { 0x6A945A3B, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "Solaris reserved 2",      { 0x6A9630D1, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "Solaris reserved 3",      { 0x6A980767, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "Solaris reserved 4",      { 0x6A96237F, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "Solaris reserved 5",      { 0x6A8D2AC7, 0x1DD2, 0x11B2, { 0x99,0xA6,0x08,0x00,0x20,0x73,0x66,0x31} }, NULL, NULL, NULL },
    { "NetBSD swap",             { 0x49F48D32, 0xB10E, 0x11DC, { 0xB9,0x9B,0x00,0x19,0xD1,0x87,0x96,0x48} }, NULL, NULL, NULL },
    { "NetBSD FFS",              { 0x49F48D5A, 0xB10E, 0x11DC, { 0xB9,0x9B,0x00,0x19,0xD1,0x87,0x96,0x48} }, NULL, NULL, NULL },
    { "NetBSD LFS",              { 0x49F48D82, 0xB10E, 0x11DC, { 0xB9,0x9B,0x00,0x19,0xD1,0x87,0x96,0x48} }, NULL, NULL, NULL },
    { "NetBSD concatenated",     { 0x2DB519C4, 0xB10E, 0x11DC, { 0xB9,0x9B,0x00,0x19,0xD1,0x87,0x96,0x48} }, NULL, NULL, NULL },
    { "NetBSD encrypted",        { 0x2DB519EC, 0xB10E, 0x11DC, { 0xB9,0x9B,0x00,0x19,0xD1,0x87,0x96,0x48} }, NULL, NULL, NULL },
    { "NetBSD RAID",             { 0x49F48DAA, 0xB10E, 0x11DC, { 0xB9,0x9B,0x00,0x19,0xD1,0x87,0x96,0x48} }, NULL, NULL, NULL },
    { "ChromeOS kernel",         { 0xFE3A2A5D, 0x4F32, 0x41A7, { 0xB7,0x25,0xAC,0xCC,0x32,0x85,0xA3,0x09} }, NULL, NULL, NULL },
    { "ChromeOS root fs",        { 0x3CB8E202, 0x3B7E, 0x47DD, { 0x8A,0x3C,0x7F,0xF2,0xA1,0x3C,0xFC,0xEC} }, NULL, NULL, NULL },
    { "ChromeOS reserved",       { 0x2E0A753D, 0x9E48, 0x43B0, { 0x83,0x37,0xB1,0x51,0x92,0xCB,0x1B,0x5E} }, NULL, NULL, NULL },
    { "MidnightBSD data",        { 0x85D5E45A, 0x237C, 0x11E1, { 0xB4,0xB3,0xE8,0x9A,0x8F,0x7F,0xC3,0xA7} }, NULL, NULL, NULL },
    { "MidnightBSD boot",        { 0x85D5E45E, 0x237C, 0x11E1, { 0xB4,0xB3,0xE8,0x9A,0x8F,0x7F,0xC3,0xA7} }, NULL, NULL, NULL },
    { "MidnightBSD swap",        { 0x85D5E45B, 0x237C, 0x11E1, { 0xB4,0xB3,0xE8,0x9A,0x8F,0x7F,0xC3,0xA7} }, NULL, NULL, NULL },
    { "MidnightBSD UFS",         { 0x0394EF8B, 0x237E, 0x11E1, { 0xB4,0xB3,0xE8,0x9A,0x8F,0x7F,0xC3,0xA7} }, NULL, NULL, NULL },
    { "MidnightBSD ZFS",         { 0x85D5E45D, 0x237C, 0x11E1, { 0xB4,0xB3,0xE8,0x9A,0x8F,0x7F,0xC3,0xA7} }, NULL, NULL, NULL },
    { "MidnightBSD Vinum",       { 0x85D5E45C, 0x237C, 0x11E1, { 0xB4,0xB3,0xE8,0x9A,0x8F,0x7F,0xC3,0xA7} }, NULL, NULL, NULL },
    { "VMware VMFS",             { 0xAA31E02A, 0x400F, 0x11DB, { 0x95,0x90,0x00,0x0C,0x29,0x11,0xD1,0xB8} }, NULL, NULL, NULL },
    { "VMware Diagnostic",       { 0x9D275380, 0x40AD, 0x11DB, { 0xBF,0x97,0x00,0x0C,0x29,0x11,0xD1,0xB8} }, NULL, NULL, NULL },
    { "VMware Virtual SAN",      { 0x381CFCCC, 0x7288, 0x11E0, { 0x92,0xEE,0x00,0x0C,0x29,0x11,0xD0,0xB2} }, NULL, NULL, NULL },
    { "VMware Virsto",           { 0x77719A0C, 0xA4A0, 0x11E3, { 0xA4,0x7E,0x00,0x0C,0x29,0x74,0x5A,0x24} }, NULL, NULL, NULL },
    { "VMware Reserved",         { 0x9198EFFC, 0x31C0, 0x11DB, { 0x8F,0x78,0x00,0x0C,0x29,0x11,0xD1,0xB8} }, NULL, NULL, NULL },
    { "OpenBSD data",            { 0x824CC7A0, 0x36A8, 0x11E3, { 0x89,0x0A,0x95,0x25,0x19,0xAD,0x3F,0x61} }, NULL, NULL, NULL },
    { "QNX6 file system",        { 0xCEF5A9AD, 0x73BC, 0x4601, { 0x89,0xF3,0xCD,0xEE,0xEE,0xE3,0x21,0xA1} }, NULL, NULL, NULL },
    { "Plan 9 partition",        { 0xC91818F9, 0x8025, 0x47AF, { 0x89,0xD2,0xF0,0x30,0xD7,0x00,0x0C,0x2C} }, NULL, NULL, NULL },
    { "HiFive Unleashed FSBL",   { 0x5B193300, 0xFC78, 0x40CD, { 0x80,0x02,0xE8,0x6C,0x45,0x58,0x0B,0x47} }, NULL, NULL, NULL },
    { "HiFive Unleashed BBL",    { 0x2E54B353, 0x1271, 0x4842, { 0x80,0x6F,0xE4,0x36,0xD6,0xAF,0x69,0x85} }, NULL, NULL, NULL },
    { NULL,                      {0}, NULL, NULL, NULL }
};
/***********************************************/
