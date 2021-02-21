#include <Arduino_FreeRTOS.h>

const int gkNumNodes = 4;
const int gkPriorityNormal = 1;
const int gkPriorityCoordinator = 1;
const int gkMaxCounter = 15;
const int gkDelay = 500;
const int gkPinId[] = {10, 11, 12, 13};
int gCounter = 0;

TaskHandle_t gCoordinatorHandle;
TaskHandle_t gTaskHandle[gkNumNodes];

static void LedTask(void* pvParameters);
static void CoordinatorTask(void* pvParameters);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Starting..."));

  for (int i = 0; i < gkNumNodes; ++i) {
    pinMode(gkPinId[i], OUTPUT);
    Serial.println(F("Creating normal tasks"));
    char c[2];
    c[0] = i + '0';
    c[1] = '\0';
    xTaskCreate(LedTask, c, configMINIMAL_STACK_SIZE, (void*)i, gkPriorityNormal, &gTaskHandle[i]);
  }
  Serial.println(F("Creating coordinator tasks"));
  xTaskCreate(CoordinatorTask, "c", configMINIMAL_STACK_SIZE, NULL, gkPriorityCoordinator, &gCoordinatorHandle);
  Serial.println(F("Starting scheduling"));
  Serial.flush();
  // task scheduler starts by the hook
}

void loop()
{
  Serial.println(F("Loop function"));
  Serial.flush();
  delay(20);
  vTaskResume(gCoordinatorHandle);
}

static void LedTask(void* pvParameters)
{
  while(1){
    int id = (int)(pvParameters);
    Serial.print(F("Starting to process for id: "));
    Serial.println(id);
    Serial.print(F("Checking LED "));
    Serial.println(gkPinId[id]);
    if (bitRead(gCounter, id) == 1) {
      Serial.println(F("Writing HIGH"));
      digitalWrite(gkPinId[id], HIGH);
    } else {
      Serial.println(F("Writing LOW"));
      digitalWrite(gkPinId[id], LOW);
    }
    Serial.println(F("Checking LED done"));
    Serial.print(F("Yielding the control from id: "));
    Serial.println(id);
    Serial.flush();
    vTaskResume(gCoordinatorHandle);
    vTaskSuspend(NULL); // suspend itself
  }
}


static void CoordinatorTask(void* pvParameters)
{
  while (gCounter <= gkMaxCounter) {
    // check the status
    for (int id = 0; id < gkNumNodes; ++id) {
      Serial.print(F("Checking pin "));
      Serial.println(gkPinId[id]);
      if (bitRead(gCounter, id) != digitalRead(gkPinId[id])) {
        Serial.print(F("Pin "));
        Serial.print(id);
        Serial.print(F(" is still working. Yielding..."));
        Serial.flush();
        vTaskSuspend(NULL);
      }
    }
    // delay to see the result
    delay(gkDelay);
    // yield control
    ++gCounter;
    Serial.print(F("Counter "));
    Serial.println(gCounter);
    Serial.println("Coordinator yields");
    Serial.flush();
    for (int i = 0; i < gkNumNodes; ++i) {
      vTaskResume(gTaskHandle[i]);
    }
    vTaskSuspend(NULL);
  }
}

