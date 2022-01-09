#include <M5Core2.h>
#include "defaults.h"
#include "structs.h"

HotZone tmpBtn(SCREEN_MAIN_LOW_TEMP_UP_BTN_DIM);

bool statsScreenButtonDown = false;

void statsScreenButtonPressed(runningState_t *runningState) {
  TouchPoint_t pos = M5.Touch.getPressPoint();
  if (pos.x != -1 && statsScreenButtonDown == false) {
    statsScreenButtonDown = true;
    if (tmpBtn.inHotZone(pos)) {
      runningState->currentScreen = 0;
    }

  } else if (pos.x == -1) {
    statsScreenButtonDown = false;
  }
}

int drawStatsScreen(TFT_eSprite Disbuff, runningState_t *runningState) {
  statsScreenButtonPressed(runningState);

  return 0;
}

int setupStatsScreen(TFT_eSprite Disbuff, runningState_t *runningState) {

  return 0;
}