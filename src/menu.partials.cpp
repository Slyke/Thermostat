#include <M5Core2.h>
#include "defaults.h"
#include "structs.h"

HotZone btnTemp(PARTIAL_SCREEN_NAV_TEMP_BTN_DIM);
HotZone btnStats(PARTIAL_SCREEN_NAV_STAT_BTN_DIM);
HotZone btnNet(PARTIAL_SCREEN_NAV_NET_BTN_DIM);
HotZone btnOthr(PARTIAL_SCREEN_NAV_OTHR_BTN_DIM);

bool navigationButtonDown = false;

void navigationButtonPressed(runningState_t *runningState) {
  TouchPoint_t pos = M5.Touch.getPressPoint();
  if (pos.x != -1 && navigationButtonDown == false) {
    navigationButtonDown = true;
    if (btnTemp.inHotZone(pos)) {
      runningState->currentScreen = 0;
    }

    if (btnStats.inHotZone(pos)) {
      runningState->currentScreen = 1;
    }

  } else if (pos.x == -1) {
    navigationButtonDown = false;
  }
}

int drawNavigation(TFT_eSprite Disbuff, runningState_t *runningState) {
  navigationButtonPressed(runningState);
  const char *mainNavMenuItems[SCREEN_MENU_LENGTH] = MAIN_NAV_MENU_ITEMS;

  Disbuff.drawRect(SCREEN_menuX, SCREEN_menuY, SCREEN_menuW, SCREEN_menuH, Disbuff.color565(SCREEN_MENU_BORDER_COLOR));
  Disbuff.fillRect(SCREEN_menuX + 1, SCREEN_menuY + 1, SCREEN_menuW - 2, SCREEN_menuH - 2, Disbuff.color565(SCREEN_MENU_FILL_COLOR));

  Disbuff.setTextSize(2);
  int currentPos = 0;

  for (int i = 0; i < SCREEN_MENU_LENGTH; i++) {
    currentPos = SCREEN_menuX + (MENU_BTN_L_PAD + MENU_BTN_WIDTH) * i;
    if (i == runningState->currentScreen) {
      Disbuff.drawRect(SCREEN_menuX + MENU_BTN_L_PAD + currentPos, SCREEN_menuY + MENU_BTN_T_PAD, MENU_BTN_WIDTH, MENU_BTN_HEIGHT, Disbuff.color565(SCREEN_MENU_ACTIVE_BUTTON_BORDER_COLOR));
      Disbuff.fillRect(SCREEN_menuX + MENU_BTN_L_PAD + currentPos + 1, SCREEN_menuY + MENU_BTN_T_PAD + 1, MENU_BTN_WIDTH - 2, MENU_BTN_HEIGHT - 2, Disbuff.color565(SCREEN_MENU_ACTIVE_BUTTON_BORDER_FILL_COLOR));
      Disbuff.setTextColor(Disbuff.color565(SCREEN_MENU_INACTIVE_BUTTON_TEXT_COLOR), Disbuff.color565(SCREEN_MENU_ACTIVE_BUTTON_BORDER_FILL_COLOR));
    } else {
      Disbuff.drawRect(SCREEN_menuX + MENU_BTN_L_PAD + currentPos, SCREEN_menuY + MENU_BTN_T_PAD, MENU_BTN_WIDTH, MENU_BTN_HEIGHT, Disbuff.color565(SCREEN_MENU_INACTIVE_BUTTON_BORDER_COLOR));
      Disbuff.fillRect(SCREEN_menuX + MENU_BTN_L_PAD + currentPos + 1, SCREEN_menuY + MENU_BTN_T_PAD + 1, MENU_BTN_WIDTH - 2, MENU_BTN_HEIGHT - 2, Disbuff.color565(SCREEN_MENU_INACTIVE_BUTTON_BORDER_FILL_COLOR));
      Disbuff.setTextColor(Disbuff.color565(SCREEN_MENU_INACTIVE_BUTTON_TEXT_COLOR), Disbuff.color565(SCREEN_MENU_INACTIVE_BUTTON_BORDER_FILL_COLOR));
    }

    Disbuff.setCursor(currentPos + MENU_BTN_L_PAD + MENU_BTN_TEXT_L_PAD, SCREEN_menuY + MENU_BTN_T_PAD + MENU_BTN_TEXT_T_PAD);
    Disbuff.printf(mainNavMenuItems[i]);
  }

  Disbuff.pushSprite(0, 0);

  return 0;
}
