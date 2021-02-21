#include <syslog.h>
#include <unistd.h>
#include <wiringPi.h>

static const int k_gTargetGpio = 0;
static const int k_gWaitingTime = 1;

int main(void)
{
  /* Open a connection to the system logger for a program */
  openlog("slog", LOG_PID|LOG_CONS, LOG_USER);
  
  /* generate log messages */
  syslog(LOG_INFO, "Starting the `toggle_gpio` program...");
  syslog(LOG_INFO, "Outputing to pin %d at a %dms period.", k_gTargetGpio, k_gWaitingTime);
  
  /* initialise the wiringPi system. The calling program is going to be using the wiringPi pin numbering scheme */
  wiringPiSetup();
  
  /* set the mode of a pin from the wiringPi pin table to either INPUT, OUTPUT, or PWM_OUTPUT */
  pinMode(k_gTargetGpio, OUTPUT);
  
  /* Write the value HIGH or LOW (1 or 0) to the given pin which must have been previously set as an output */
  digitalWrite(k_gTargetGpio, LOW);

  while (TRUE) {
    digitalWrite(k_gTargetGpio, LOW);
    
    /* introduce a delay (milliseconds) between every change of output value */
    delay(k_gWaitingTime);
    digitalWrite(k_gTargetGpio, HIGH);
    delay(k_gWaitingTime);
  }

  closelog();
  return 0;
}
