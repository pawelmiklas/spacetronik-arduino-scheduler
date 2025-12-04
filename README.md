# Spacetronik SPE-223HB Desk Scheduler

Automatic height control for a Spacetronik SPE-223HB desk using Arduino Nano and DS3231 RTC. Raises/lowers the desk at fixed times, and auto-raises on boot if current time is inside an active “UP” interval. Operates only on weekdays (Mon–Fri).

## Summary

- Hardware: Arduino Nano, DS3231 RTC
- Events: {hour, minute, goUp}
- goUp=true → start of UP window; next event (same hour, false) → end
- On boot: if current time ∈ UP window → raise desk once
- Main loop triggers only on exact event minutes
- Weekend skip: Sat/Sun ignored

Example windows:
09:00–09:20, 11:00–11:20, 13:00–13:20, 15:00–15:20, 17:00–17:20

Desk commands:
- UP: pulse pin 5 LOW
- DOWN: pulse pin 6 LOW
(both held HIGH otherwise)

## Notes

- Set RTC time before use
- Minimal, event-driven code using minute change as trigger

