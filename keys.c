#include <string.h>

#include "keys.h"

struct key {
    const char* regular;
    const char* shifted;
};

static struct key keys[] = {
    {NULL, NULL}, // unused
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},

    {"a", "A"},
    {"b", "B"},
    {"c", "C"},
    {"d", "D"},
    {"e", "E"},
    {"f", "F"},
    {"g", "G"},
    {"h", "H"},
    {"i", "I"},
    {"j", "J"},
    {"k", "K"},
    {"l", "L"},
    {"m", "M"},
    {"n", "N"},
    {"o", "O"},
    {"p", "P"},
    {"q", "Q"},
    {"r", "R"},
    {"s", "S"},
    {"t", "T"},
    {"u", "U"},
    {"v", "V"},
    {"w", "W"},
    {"x", "X"},
    {"y", "Y"},
    {"z", "Z"},

    {"1", "!"},
    {"2", "@"},
    {"3", "#"},
    {"4", "$"},
    {"5", "%"},
    {"6", "^"},
    {"7", "&"},
    {"8", "*"},
    {"9", "("},
    {"0", ")"},

    {"{enter}\n", NULL},
    {"{esc}", NULL},
    {"{backspace}", NULL},
    {"{tab}", NULL},
    {"{space}", NULL},
    {"-", "_"},
    {"=", "+"},
    {"[", "{"},
    {"]", "}"},
    {"\\", "|"},
    {"{number}", NULL},
    {";", ":"},
    {"'", "\""},
    {"`", "~"},
    {",", "<"},
    {".", ">"},
    {"/", "?"},
    {"{caps lock}", NULL},
    {"{f1}", NULL},
    {"{f2}", NULL},
    {"{f3}", NULL},
    {"{f4}", NULL},
    {"{f5}", NULL},
    {"{f6}", NULL},
    {"{f7}", NULL},
    {"{f8}", NULL},
    {"{f9}", NULL},
    {"{f10}", NULL},
    {"{f11}", NULL},
    {"{f12}", NULL},
    {"{printscreen}", NULL},
    {"{scroll lock}", NULL},
    {"{pause}", NULL},
    {"{insert}", NULL},
    {"{home}", NULL},
    {"{page up}", NULL},
    {"{delete}", NULL},
    {"{end}", NULL},
    {"{page down}", NULL},
    {"{right}", NULL},
    {"{left}", NULL},
    {"{down}", NULL},
    {"{up}", NULL},
    {"{num lock}", NULL},
    {"{num /}", NULL},
    {"{num *}", NULL},
    {"{num -}", NULL},
    {"{num +}", NULL},
    {"{num enter}\n", NULL},
    {"{num 1}", NULL},
    {"{num 2}", NULL},
    {"{num 3}", NULL},
    {"{num 4}", NULL},
    {"{num 5}", NULL},
    {"{num 6}", NULL},
    {"{num 7}", NULL},
    {"{num 8}", NULL},
    {"{num 9}", NULL},
    {"{num 0}", NULL},
    {"{num .}", NULL},
};

void decode_key(int k, int modifiers, char* buffer) {
    struct key* key = &keys[k];

    // TODO: Check length of buffer
    *buffer = '\0';

    if (modifiers & (KEY_LEFT_CTRL | KEY_RIGHT_CTRL)) {
        strcat(buffer, "{ctrl}");
    }
    if (modifiers & (KEY_LEFT_ALT | KEY_RIGHT_ALT)) {
        strcat(buffer, "{alt}");
    }
    if (modifiers & (KEY_LEFT_GUI | KEY_RIGHT_GUI)) {
        strcat(buffer, "{gui}");
    }

    if (modifiers & (KEY_LEFT_SHIFT | KEY_RIGHT_SHIFT)) {
        if (key->shifted != NULL) {
            strcat(buffer, key->shifted);
        } else {
            strcat(buffer, "{shift}");
            strcat(buffer, key->regular);
        }
    } else {
        strcat(buffer, key->regular);
    }
}
