#include <M5Core2.h>
#include "defaults.h"
#include "structs.h"

HotZone tmpBtn(SCREEN_MAIN_LOW_TEMP_UP_BTN_DIM);

bool ctrlScreenButtonDown = false;

void ctrlScreenButtonPressed(runningState_t *runningState) {
  TouchPoint_t pos = M5.Touch.getPressPoint();
  if (pos.x != -1 && ctrlScreenButtonDown == false) {
    ctrlScreenButtonDown = true;
    if (tmpBtn.inHotZone(pos)) {
      runningState->currentScreen = 0;
    }

  } else if (pos.x == -1) {
    ctrlScreenButtonDown = false;
  }
}

int drawCtrlScreen(TFT_eSprite Disbuff, runningState_t *runningState) {
  ctrlScreenButtonPressed(runningState);

  return 0;
}

int setupCtrlScreen(TFT_eSprite Disbuff, runningState_t *runningState) {

  return 0;
}