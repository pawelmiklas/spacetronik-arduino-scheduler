// Each stage should be invoked independently

// Test DS3231
// Checking RTC...
// RTC now: 2025-11-27 10:34:12

#include <Wire.h>
#include <RtcDS3231.h>

RtcDS3231<TwoWire> rtc(Wire);

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.begin();
  rtc.Begin();

  Serial.println("Checking RTC...");

  if (!rtc.IsDateTimeValid()) {
    Serial.println("RTC time invalid — setting default time.");

    // Set to compile time (LOCAL)
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    rtc.SetDateTime(compiled);
  }

  if (!rtc.GetIsRunning()) {
    Serial.println("RTC oscillator was stopped — starting it.");
    rtc.SetIsRunning(true);
  }

  RtcDateTime now = rtc.GetDateTime();

  char buf[32];
  snprintf(buf, sizeof(buf), "%04u-%02u-%02u %02u:%02u:%02u",
           now.Year(), now.Month(), now.Day(),
           now.Hour(), now.Minute(), now.Second());

  Serial.print("RTC now: ");
  Serial.println(buf);
}

void loop() {}


// Set DS3231 to correct local time

#include <Wire.h>
#include <RtcDS3231.h>

RtcDS3231<TwoWire> rtc(Wire);

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.begin();
  rtc.Begin();

  Serial.println("Setting RTC to compile-time...");

  RtcDateTime compiled(__DATE__, __TIME__);
  rtc.SetDateTime(compiled);

  Serial.println("RTC set successfully!");

  // Confirm
  RtcDateTime now = rtc.GetDateTime();
  char buf[32];
  snprintf(buf, sizeof(buf), "%04u-%02u-%02u %02u:%02u:%02u",
           now.Year(), now.Month(), now.Day(),
           now.Hour(), now.Minute(), now.Second());
  Serial.println(buf);
}

void loop() {}

// Verify RTC is correct

#include <Wire.h>
#include <RtcDS3231.h>

RtcDS3231<TwoWire> rtc(Wire);

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.begin();
  rtc.Begin();

  Serial.println("Checking RTC after setting...");
  RtcDateTime now = rtc.GetDateTime();

  char buf[32];
  snprintf(buf, sizeof(buf), "%04u-%02u-%02u %02u:%02u:%02u",
           now.Year(), now.Month(), now.Day(),
           now.Hour(), now.Minute(), now.Second());

  Serial.println(buf);
}

void loop() {}


