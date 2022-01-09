#ifndef STRUCTS_H
#define STRUCTS_H

struct temperatures_t {
  char lowTempSetting = 18;
  char highTempSetting = 25;
  int currentTemp = -275;
};

struct furnace_t {
  char state = 0;
};

struct device_t {
  char battery = 0;
  bool charging = 0;
};

struct connectivity_y {
  char wifi = 0;
  char mqtt = 0;
  char wifiSsid[64] = "Phox";
  char wifiPassword[128] = "thirstydiamond60";
};

struct runningState_t {
  struct temperatures_t temperatures;
  struct furnace_t furnace;
  struct device_t device;
  struct connectivity_y connectivity;
  char timeString[64] = "Unknown";
  int frameCount = 0;
  char currentScreen = 0;
};

#endif