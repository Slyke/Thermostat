#include <Arduino.h>
#include <M5Core2.h>

#include <WiFi.h>
#include "structs.h"
#include "menu.partials.h"
#include "defaults.h"
#include "screen.main.h"
#include "screen.stats.h"
#include "screen.ctrl.h"
#include "state_update.h"

struct runningState_t runningState;

// M5.Lcd.setBrightness(0); M5.Axp.SetLcdVoltage(i); // 2500-3300
// M5.Lcd.wakeup();
// M5.Lcd.sleep();
// M5.Lcd.setRotation()

TFT_eSprite Disbuff = TFT_eSprite(&M5.Lcd);

void setup() {
  // M5.begin(bool LCDEnable = true, bool SDEnable = true, bool SerialEnable = true, bool I2CEnable = false, mbus_mode_t mode = kMBusModeOutput);
  M5.begin(true, false, true, true);
  // M5.Power.begin();
  // M5.begin();
  
  Disbuff.createSprite(SCREEN_W, SCREEN_H);
  M5.Lcd.setBrightness(1);
  // Disbuff.setFreeFont(&EVA_20px);
  // M5.Lcd.invertDisplay(true);
  Serial.begin(115200);
  M5.Axp.SetLcdVoltage(2700); // 2500-3300
  Serial.println("setup()");
  
  WiFi.begin(runningState.connectivity.wifiSsid, runningState.connectivity.wifiPassword);
  char wifiTry = 0;
  runningState.frameCount = 0;
  Disbuff.print("Booting");
  Disbuff.pushSprite(0, 0);
  while(WiFi.status() != WL_CONNECTED && wifiTry < 3) {
    delay(100);
    Disbuff.print(".");
    Disbuff.pushSprite(0, 0);
    wifiTry++;
  }
}

void loop() {
  Disbuff.fillSprite(TFT_BLACK);
  // Disbuff.fillSprite(RED);
  // Disbuff.pushSprite(0, 0);
  // Disbuff.setRotation(1);
  // Disbuff.setBrightness(0);
  // delay(3000);
  switch (runningState.currentScreen) {
    case 0:
      drawMainScreen(Disbuff, &runningState);
      break;

    case 1:
      drawStatsScreen(Disbuff, &runningState);
      break;

    case 2:
      drawCtrlScreen(Disbuff, &runningState);
      break;

    default:
      drawMainScreen(Disbuff, &runningState);
  }
  drawNavigation(Disbuff, &runningState);
  Disbuff.pushSprite(0, 0);
  M5.update();
  updateState(&runningState, Disbuff);
  // delay(25);
}