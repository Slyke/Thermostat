#include <M5Core2.h>
#include "defaults.h"
#include "structs.h"
#include "images/wifi_32x32_strong.h"
#include "images/wifi_32x32_medium.h"
#include "images/wifi_32x32_weak.h"
#include "images/mqtt_32x32.h"
#include "images/X_32x32.h"

const int minMaxValueOffset = 185;
const int valueOffset = 110;
const int lineHeight = 20;
const int tempControlScreenEdgePadding = 25;
const int controlLetterWidth = 35;

HotZone lowTempUp(SCREEN_MAIN_LOW_TEMP_UP_BTN_DIM);
HotZone lowTempDown(SCREEN_MAIN_LOW_TEMP_DOWN_BTN_DIM);
HotZone highTempUp(SCREEN_MAIN_HIGH_TEMP_UP_BTN_DIM);
HotZone highTempDown(SCREEN_MAIN_HIGH_TEMP_DOWN_BTN_DIM);

bool mainScreenButtonDown = false;

void mainScreenButtonPressed(runningState_t *runningState) {
  TouchPoint_t pos = M5.Touch.getPressPoint();

  if (pos.x != -1 && mainScreenButtonDown == false) {
    mainScreenButtonDown = true;
    if (lowTempUp.inHotZone(pos)) {
      if (runningState->temperatures.lowTempSetting < runningState->temperatures.highTempSetting - TEMP_LOW_HIGH_DIFF_SETTING) {
        runningState->temperatures.lowTempSetting++;
      }
    }

    if (lowTempDown.inHotZone(pos)) {
      if (runningState->temperatures.lowTempSetting > MIN_TEMP_SETTING) {
        runningState->temperatures.lowTempSetting--;
      }
    }

    if (highTempUp.inHotZone(pos)) {
      if (runningState->temperatures.highTempSetting < MAX_TEMP_SETTING) {
        runningState->temperatures.highTempSetting++;
      }
    }

    if (highTempDown.inHotZone(pos)) {
      if (runningState->temperatures.highTempSetting > runningState->temperatures.lowTempSetting + TEMP_LOW_HIGH_DIFF_SETTING) {
        runningState->temperatures.highTempSetting--;
      }
    }
  } else if (pos.x == -1) {
    mainScreenButtonDown = false;
  }
}

int drawMainScreen(TFT_eSprite Disbuff, runningState_t *runningState) {
  mainScreenButtonPressed(runningState);

  int lineAt = 10;

  Disbuff.setTextSize(3);
  Disbuff.setCursor(tempControlScreenEdgePadding, lineAt - 3);
  if (runningState->temperatures.lowTempSetting <= MIN_TEMP_SETTING) {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_LABEL_OFF), BLACK);
  } else {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_TEMP_COLD), BLACK);
  }
  Disbuff.printf("<");
  Disbuff.setTextColor(WHITE, BLACK);
  Disbuff.setTextSize(2);
  Disbuff.setCursor(70, lineAt);
  Disbuff.printf("Heat ON :");
  Disbuff.setCursor(minMaxValueOffset, lineAt);
  Disbuff.printf("%d C", runningState->temperatures.lowTempSetting);
  Disbuff.setTextSize(3);
  Disbuff.setCursor(SCREEN_W - (tempControlScreenEdgePadding + 20), lineAt - 3);
  if (runningState->temperatures.highTempSetting > runningState->temperatures.lowTempSetting + TEMP_LOW_HIGH_DIFF_SETTING) {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_TEMP_HOT), BLACK);
  } else {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_LABEL_OFF), BLACK);
  }
  Disbuff.printf(">");
  Disbuff.setTextColor(WHITE, BLACK);
  Disbuff.setTextSize(2);
  lineAt += lineHeight * 2;

  Disbuff.setTextSize(8);
  Disbuff.setCursor(valueOffset - 50, lineAt - 5);
  Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_TEMP_GOOD), BLACK); // SCREEN_MAIN_TEMP_HOT, SCREEN_MAIN_TEMP_GOOD, SCREEN_MAIN_TEMP_COLD
  if (runningState->temperatures.currentTemp < runningState->temperatures.lowTempSetting) {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_TEMP_COLD), BLACK);
  } else if (runningState->temperatures.currentTemp > runningState->temperatures.highTempSetting) {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_TEMP_HOT), BLACK);
  }
  if (runningState->temperatures.currentTemp < -274) {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_LABEL_OFF), BLACK);
    Disbuff.printf("?? C");
  } else {
    Disbuff.printf("%d C", runningState->temperatures.currentTemp);
  }
  Disbuff.setTextColor(WHITE, BLACK);
  Disbuff.setTextSize(2);

  lineAt += (lineHeight * 3) + 10;
  Disbuff.setTextSize(3);
  Disbuff.setCursor(tempControlScreenEdgePadding, lineAt - 3);
  if (runningState->temperatures.highTempSetting > runningState->temperatures.lowTempSetting + TEMP_LOW_HIGH_DIFF_SETTING) {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_TEMP_COLD), BLACK);
  } else {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_LABEL_OFF), BLACK);
  }
  Disbuff.printf("<");
  Disbuff.setTextColor(WHITE, BLACK);
  Disbuff.setTextSize(2);
  Disbuff.setCursor(70, lineAt);
  Disbuff.printf("Heat OFF: ");
  Disbuff.setCursor(minMaxValueOffset, lineAt);

  Disbuff.printf("%d C", runningState->temperatures.highTempSetting);
  Disbuff.setTextSize(3);
  Disbuff.setCursor(SCREEN_W - (tempControlScreenEdgePadding + 20), lineAt - 3);
  if (runningState->temperatures.highTempSetting >= MAX_TEMP_SETTING) {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_LABEL_OFF), BLACK);
  } else {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_TEMP_HOT), BLACK);
  }
  Disbuff.printf(">");
  Disbuff.setTextColor(WHITE, BLACK);
  Disbuff.setTextSize(2);
  lineAt += lineHeight;

  lineAt = SCREEN_menuY - (lineHeight * 2);
  Disbuff.setCursor(0, lineAt);
  Disbuff.setTextSize(2);
  Disbuff.printf("Furnace :");
  Disbuff.setCursor(valueOffset, lineAt);
  if (runningState->furnace.state == 1) {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_LABEL_OFF), BLACK);
    Disbuff.printf("Off");
  } else if (runningState->furnace.state == 2) {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_LABEL_ON), BLACK);
    Disbuff.printf("On");
  } else {
    Disbuff.setTextColor(Disbuff.color565(SCREEN_MAIN_LABEL_OFF), Disbuff.color565(SCREEN_MENU_INACTIVE_BUTTON_BORDER_COLOR));
    Disbuff.printf(" ?? ");
  }
  Disbuff.setTextColor(WHITE, BLACK);

  // Stick time to the bottom
  lineAt = SCREEN_menuY - lineHeight;
  Disbuff.setCursor(0, lineAt);
  Disbuff.printf("Time :");
  Disbuff.setCursor(valueOffset - 30, lineAt);
  Disbuff.printf(runningState->timeString);

  if (runningState->connectivity.wifi == 1) {
    Disbuff.drawXBitmap(1, 45, icon_wifi_strong, icon_wifi_strong_width, icon_wifi_strong_height, Disbuff.color565(SCREEN_MAIN_WIFI_STRONG));
  } else if (runningState->connectivity.wifi == 2) {
    Disbuff.drawXBitmap(1, 45, icon_wifi_medium, icon_wifi_medium_width, icon_wifi_medium_height, Disbuff.color565(SCREEN_MAIN_WIFI_MEDIUM));
  } else if (runningState->connectivity.wifi == 3) {
    Disbuff.drawXBitmap(1, 45, icon_wifi_weak, icon_wifi_weak_width, icon_wifi_weak_height, Disbuff.color565(SCREEN_MAIN_WIFI_WEAK));
  } else if (runningState->connectivity.wifi == 4) {
    Disbuff.drawXBitmap(1, 45, icon_wifi_strong, icon_wifi_strong_width, icon_wifi_strong_height, Disbuff.color565(SCREEN_MAIN_WIFI_OFF));
    Disbuff.drawXBitmap(1, 34, icon_X, icon_X_width, icon_X_height, Disbuff.color565(icon_X_color));
  } else {
    Disbuff.drawXBitmap(1, 45, icon_wifi_strong, icon_wifi_strong_width, icon_wifi_strong_height, Disbuff.color565(SCREEN_MAIN_WIFI_UNKNOWN));
  }

  if (runningState->connectivity.mqtt == 2) {
    Disbuff.drawXBitmap(1, 80, icon_mqtt, icon_mqtt_width, icon_mqtt_height, Disbuff.color565(SCREEN_MAIN_MQTT_CONNECTED));
  } else {
    Disbuff.drawXBitmap(1, 80, icon_mqtt, icon_mqtt_width, icon_mqtt_height, Disbuff.color565(SCREEN_MAIN_MQTT_NONE));
    Disbuff.drawXBitmap(1, 80, icon_X, icon_X_width, icon_X_height, Disbuff.color565(icon_X_color));
  }

  return 0;
}

int setupMainScreen(TFT_eSprite Disbuff, runningState_t *runningState) {

  return 0;
}