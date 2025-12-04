#include <Wire.h>
#include <RtcDS3231.h>

RtcDS3231<TwoWire> rtc(Wire);

const uint8_t DOWN = 6;
const uint8_t UP = 5;

struct Event {
  uint8_t hour;
  uint8_t minute;
  bool goUp;
};

Event events[] = {
  {9,  0,  true},
  {9, 20, false},
  {11, 0, true},
  {11, 20, false},
  {13, 0,  true},
  {13, 20, false},
  {15, 0,  true},
  {15, 20, false},
  {17, 0,  true},
  {17, 20, false},
};

const uint8_t EVENTS_COUNT = sizeof(events) / sizeof(events[0]);

uint8_t lastMinute = 255;

void click(uint8_t pin) {
  digitalWrite(pin, LOW);
  delay(100);
  digitalWrite(pin, HIGH);
  delay(300);
  digitalWrite(pin, LOW);
  delay(200);
  digitalWrite(pin, HIGH);
}

void raiseDesk() { click(UP); }
void lowerDesk() { click(DOWN); }

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin();
  rtc.Begin();

  pinMode(DOWN, OUTPUT);
  pinMode(UP, OUTPUT);

  digitalWrite(DOWN, HIGH);
  digitalWrite(UP, HIGH);

  RtcDateTime now = rtc.GetDateTime();
  lastMinute = now.Minute();

  Serial.println("Desk scheduler running.");
}

void loop() {
  RtcDateTime now = rtc.GetDateTime();

  uint8_t dayOfWeek = now.DayOfWeek();
  uint8_t hour = now.Hour();
  uint8_t minute = now.Minute();

  if (minute == lastMinute) {
    delay(1000);
    return;
  }

  lastMinute = minute;

  if (dayOfWeek < 1 || dayOfWeek > 5) {
    delay(1000);
    return;
  }

  static bool initialCheckDone = false;

  if (!initialCheckDone) {
    initialCheckDone = true;

    for (uint8_t i = 0; i + 1 < EVENTS_COUNT; i++) {
      const Event& start = events[i];
      const Event& end = events[i + 1];

      if (!start.goUp) {
        continue;
      }
      if (end.goUp) {
        continue;
      }
      if (end.hour != start.hour) {
        continue;
      }

      bool afterStart =
        (hour > start.hour) ||
        (hour == start.hour && minute >= start.minute);

      bool beforeEnd =
        (hour < end.hour) ||
        (hour == end.hour && minute < end.minute);

      if (afterStart && beforeEnd) {
        raiseDesk();
        delay(1000);
        return;
      }
    }
  }

  for (uint8_t i = 0; i < EVENTS_COUNT; i++) {
    const Event& ev = events[i];

    if (ev.hour != hour || ev.minute != minute) {
      continue;
    }

    if (ev.goUp) {
      raiseDesk();
    } else {
      lowerDesk();
    }

    break;
  }

  delay(1000);
}
