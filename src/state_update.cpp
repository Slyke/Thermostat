#include <Arduino.h>
#include <M5Core2.h>
#include <WiFi.h>
#include "time.h"
#include "defaults.h"
#include "structs.h"

const char* ntpServer = "time1.aliyun.com"; // "pool.ntp.org"
const long  gmtOffset_sec = 0; // 3600
const int   daylightOffset_sec = 3600;

int updateState(runningState_t *runningState, TFT_eSprite Disbuff) {
  RTC_TimeTypeDef rtcTime;
  RTC_DateTypeDef rtcDate;
    struct tm timeInfo;
  if (runningState->frameCount > 0xFE) {
    Serial.println("Frame count loop");
    runningState->frameCount = 0;
  }

  if (runningState->frameCount == 0) {
    Serial.println("NTP Time Retrieval: Start");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println("NTP Time Retrieval: Finish");

    if (getLocalTime(&timeInfo)) {
      Serial.println(&timeInfo, "NTP Retrieval: %A, %B %d %Y %H:%M:%S");
      if (timeInfo.tm_year >= 100) {
        rtcTime.Hours = timeInfo.tm_hour;
        rtcTime.Minutes = timeInfo.tm_min;
        rtcTime.Seconds = timeInfo.tm_sec;
        M5.Rtc.SetTime(&rtcTime);

        rtcDate.Year = timeInfo.tm_year + 1900;
        rtcDate.Month = timeInfo.tm_mon + 1;
        rtcDate.Date = timeInfo.tm_mday;
        M5.Rtc.SetDate(&rtcDate);

        // setTime(timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_mday, timeinfo.tm_mon+1,timeinfo.tm_year - 100);
        // time_t now;
        // time(&now);
        // RTC.set(now);
        // setTime(timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_mday, timeinfo.tm_mon+1,timeinfo.tm_year - 100);

        sprintf(runningState->timeString, "%d-%02d-%02d %02d:%02d:%02d", rtcDate.Year, rtcDate.Month, rtcDate.Date, rtcTime.Hours, rtcTime.Minutes, rtcTime.Seconds);
        Serial.printf("NTP Retrieval Store: Success '%s'\n", runningState->timeString);
      } else {
        Serial.println("NTP Retrieval Store: Failed. Reason: Year earlier than 1970.");
      }
    } else {
      Serial.println("NTP Retrieval Store: Failed");
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Attempting wifi reconnection");
      WiFi.begin(runningState->connectivity.wifiSsid, runningState->connectivity.wifiPassword);
    }
  }
  runningState->frameCount++;

  M5.Rtc.GetTime(&rtcTime);
  M5.Rtc.GetDate(&rtcDate);

  sprintf(runningState->timeString, "%d-%02d-%02d %02d:%02d:%02d", rtcDate.Year, rtcDate.Month, rtcDate.Date, rtcTime.Hours, rtcTime.Minutes, rtcTime.Seconds);

  if (WiFi.status() == WL_CONNECTED) {
    runningState->connectivity.wifi = 3;

    long rssi = abs(WiFi.RSSI());
    if (rssi < 55) {
      runningState->connectivity.wifi = 1;
    } else if (rssi < 70) {
      runningState->connectivity.wifi = 2;
    } else {
      runningState->connectivity.wifi = 3;
    }
  } else {
    runningState->connectivity.wifi = 0;
  }

  return 0;
}
