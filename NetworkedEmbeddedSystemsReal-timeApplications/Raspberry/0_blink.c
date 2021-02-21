#include <syslog.h>
#include <unistd.h>
#include <wiringPi.h>

static const int k_gBlinkLed = 0;
static const int k_gWaitingTime = 1000;

int main(void)
{
  openlog("slog", LOG_PID|LOG_CONS, LOG_USER);
  syslog(LOG_INFO, "Starting the `blink` program...");

  wiringPiSetup();
  pinMode(k_gBlinkLed, OUTPUT);
  while (TRUE) {
    syslog(LOG_INFO, "Writing %d to pin %d.", HIGH, k_gBlinkLed);
    digitalWrite(k_gBlinkLed, HIGH);
    delay(k_gWaitingTime);
    syslog(LOG_INFO, "Writing %d to pin %d.", LOW, k_gBlinkLed);
    digitalWrite(k_gBlinkLed, LOW);
    delay(k_gWaitingTime);
  }

  closelog();
  return 0;
}
