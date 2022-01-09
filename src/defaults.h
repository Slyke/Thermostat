
#ifndef DEFAULTS_H
#define DEFAULTS_H

#define DEBUG true

// Touch
// #define NUM_EVENTS    8
#define TE_TOUCH    0x0001
#define TE_RELEASE    0x0002
#define TE_MOVE     0x0004
#define TE_GESTURE    0x0008
#define TE_TAP        0x0010
#define TE_DBLTAP    0x0020
#define TE_DRAGGED    0x0040
#define TE_PRESSED    0x0080
#define TE_ALL        0x0FFF
#define TE_BTNONLY    0x1000

#define SCREEN_W 320
#define SCREEN_H 240
#define SCREEN_menuH 50
#define SCREEN_menuW SCREEN_W - 1
#define SCREEN_menuY (SCREEN_H - SCREEN_menuH) - 1
#define SCREEN_menuX 0

#define SCREEN_MENU_BORDER_COLOR 0, 0, 200
#define SCREEN_MENU_FILL_COLOR 50, 50, 50

#define MENU_BTN_WIDTH 60
#define MENU_BTN_HEIGHT 30
#define MENU_BTN_L_PAD 15
#define MENU_BTN_TEXT_L_PAD 5
#define MENU_BTN_T_PAD 10
#define MENU_BTN_TEXT_T_PAD 8

#define SCREEN_MENU_INACTIVE_BUTTON_BORDER_COLOR 200, 200, 200
#define SCREEN_MENU_INACTIVE_BUTTON_BORDER_FILL_COLOR 100, 100, 100
#define SCREEN_MENU_INACTIVE_BUTTON_TEXT_COLOR 255, 255, 255

#define SCREEN_MENU_ACTIVE_BUTTON_BORDER_COLOR 0, 200, 100
#define SCREEN_MENU_ACTIVE_BUTTON_BORDER_FILL_COLOR 100, 200, 200

#define SCREEN_MAIN_LABEL_ON 0, 230, 100
#define SCREEN_MAIN_LABEL_OFF 75, 75, 75

#define SCREEN_MAIN_TEMP_HOT 230, 50, 50
#define SCREEN_MAIN_TEMP_GOOD 50, 230, 50
#define SCREEN_MAIN_TEMP_COLD 50, 50, 230

#define SCREEN_MAIN_WIFI_STRONG 50, 230, 50
#define SCREEN_MAIN_WIFI_MEDIUM 150, 200, 50
#define SCREEN_MAIN_WIFI_WEAK 254, 254, 254
#define SCREEN_MAIN_WIFI_OFF 75, 75, 75
#define SCREEN_MAIN_WIFI_UNKNOWN 75, 75, 75

#define SCREEN_MAIN_MQTT_CONNECTED 50, 230, 50
#define SCREEN_MAIN_MQTT_NONE 75, 75, 75

#define SCREEN_BTN_WIDTH 70
#define SCREEN_BTN_HEIGHT 50
#define SCREEN_BTN_L_PAD 1
#define SCREEN_BTN_T_PAD 1
#define SCREEN_BTN_R_PAD 1
#define SCREEN_BTN_HIGH_T_PAD 105

// x1, y1, x2, y2
#define SCREEN_MAIN_LOW_TEMP_DOWN_BTN_DIM (SCREEN_BTN_L_PAD), (SCREEN_BTN_T_PAD), (SCREEN_BTN_L_PAD + SCREEN_BTN_WIDTH), (SCREEN_BTN_T_PAD + SCREEN_BTN_HEIGHT) // Low Down
#define SCREEN_MAIN_LOW_TEMP_UP_BTN_DIM (SCREEN_W - (SCREEN_BTN_WIDTH + SCREEN_BTN_R_PAD)), (SCREEN_BTN_T_PAD), (SCREEN_W - SCREEN_BTN_R_PAD), (SCREEN_BTN_T_PAD + SCREEN_BTN_HEIGHT) // Low Up

#define SCREEN_MAIN_HIGH_TEMP_DOWN_BTN_DIM (SCREEN_BTN_L_PAD), (SCREEN_BTN_HIGH_T_PAD), (SCREEN_BTN_L_PAD + SCREEN_BTN_WIDTH), (SCREEN_BTN_HIGH_T_PAD + SCREEN_BTN_HEIGHT) // High Down
#define SCREEN_MAIN_HIGH_TEMP_UP_BTN_DIM (SCREEN_W - (SCREEN_BTN_WIDTH + SCREEN_BTN_R_PAD)), (SCREEN_BTN_HIGH_T_PAD), (SCREEN_W - SCREEN_BTN_R_PAD), (SCREEN_BTN_HIGH_T_PAD + SCREEN_BTN_HEIGHT) // High up

#define SCREEN_MENU_LENGTH 4
#define MAIN_NAV_MENU_ITEMS { "Temp", "Stat", "Ctrl", "Othr" }

#define MIN_TEMP_SETTING 10
#define MAX_TEMP_SETTING 38
#define TEMP_LOW_HIGH_DIFF_SETTING 3

// x1, y1, x2, y2
#define PARTIAL_SCREEN_NAV_TEMP_BTN_DIM 0, (SCREEN_H - SCREEN_menuY), (MENU_BTN_WIDTH + MENU_BTN_L_PAD), SCREEN_H
#define PARTIAL_SCREEN_NAV_STAT_BTN_DIM (MENU_BTN_WIDTH + MENU_BTN_L_PAD), (SCREEN_H - SCREEN_menuY), ((MENU_BTN_WIDTH + MENU_BTN_L_PAD) * 2), SCREEN_H
#define PARTIAL_SCREEN_NAV_NET_BTN_DIM ((MENU_BTN_WIDTH + MENU_BTN_L_PAD) * 2), (SCREEN_H - SCREEN_menuY), ((MENU_BTN_WIDTH + MENU_BTN_L_PAD) * 3), SCREEN_H
#define PARTIAL_SCREEN_NAV_OTHR_BTN_DIM ((MENU_BTN_WIDTH + MENU_BTN_L_PAD) * 3), (SCREEN_H - SCREEN_menuY), ((MENU_BTN_WIDTH + MENU_BTN_L_PAD) * 4), SCREEN_H

#endif