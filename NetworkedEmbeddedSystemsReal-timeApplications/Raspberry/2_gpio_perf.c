/* using the functionality from the 1993 edition of the POSIX.1b standard (real-time extensions) */
#define _POSIX_C_SOURCE 199309L

#include <stddef.h>
#include <sys/sysinfo.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>

static const int k_gTargetGpio = 0;
static const int k_gWaitingTime = 5;

int main(void) {
  openlog("slog", LOG_PID | LOG_CONS, LOG_USER);
  syslog(LOG_INFO, "Starting the `gpio_perf` program...");
  syslog(LOG_INFO, "Outputing to pin %d at a %dms period.", k_gTargetGpio,
         k_gWaitingTime);
  
  /* get uptime in seconds */
  struct sysinfo info;
  
  /* a simple way of getting overall system statistics */
  sysinfo(&info);
  
  /* get monotonic clock time */
  struct timespec monotime;
  
  const time_t boottime = time(NULL) - info.uptime;
  syslog(LOG_INFO, "Booted at %s.", ctime(&boottime));

  wiringPiSetup();
  pinMode(k_gTargetGpio, OUTPUT);
  digitalWrite(k_gTargetGpio, LOW);

  while (TRUE)
  {
    digitalWrite(k_gTargetGpio, LOW);
    
    /* retrieve the time of the monotonic clock, that cannot be set and represents 
       monotonic time since some unspecified starting point. */
    clock_gettime(CLOCK_MONOTONIC, &monotime);
    
    syslog(LOG_INFO, "Written LOW at %ld.", monotime.tv_nsec);
    delay(k_gWaitingTime);
    digitalWrite(k_gTargetGpio, HIGH);
    clock_gettime(CLOCK_MONOTONIC, &monotime);
    syslog(LOG_INFO, "Written HIGH at %ld.", monotime.tv_nsec);
    delay(k_gWaitingTime);
  }

  closelog();
  return 0;
}
