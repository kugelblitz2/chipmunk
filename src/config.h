#ifndef CONFIG_H
#define CONFIG_H
#include <unordered_map>

// Size of the CHIP-8 Screen
#define width 64
#define height 32
int scale = 1;

/* CHIP-8 Keyboard
╔══════════════════╗
║ 1    2    3    C ║
║ 3    4    5    D ║
║ 6    7    8    E ║
║ A    0    B    F ║
╚══════════════════╝
Keymaps: */
#define chipkey_1 '1'
#define chipkey_2 '2'
#define chipkey_3 '3'
#define chipkey_4 'q'
#define chipkey_5 'w'
#define chipkey_6 'e'
#define chipkey_7 'a'
#define chipkey_8 's'
#define chipkey_9 'd'
#define chipkey_0 'x'
#define chipkey_a 'z'
#define chipkey_b 'c'
#define chipkey_c '4'
#define chipkey_d 'r'
#define chipkey_e 'f'
#define chipkey_f 'v'

// CHIP-8 to real key lookup
extern const char chipKey[16] = {chipkey_0, chipkey_1, chipkey_2, chipkey_3,
                                chipkey_4, chipkey_5, chipkey_6, chipkey_7,
                                chipkey_8, chipkey_9, chipkey_a, chipkey_b,
                                chipkey_c, chipkey_d, chipkey_e, chipkey_f};

// CHIP-8 real key to CHIP-8 key lookup
extern std::unordered_map<char, char> keyChip
    ({{chipkey_0, 0x0}, {chipkey_1, 0x1}, {chipkey_2, 0x2}, {chipkey_3, 0x3},
    {chipkey_4, 0x4}, {chipkey_5, 0x5}, {chipkey_6, 0x6}, {chipkey_7, 0x7},
    {chipkey_8, 0x8}, {chipkey_9, 0x9}, {chipkey_a, 0xa}, {chipkey_b, 0xb},
    {chipkey_c, 0xc}, {chipkey_d, 0xd}, {chipkey_e, 0xe}, {chipkey_f, 0xf}});

#endif