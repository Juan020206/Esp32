#include "data.h"
QueueHandle_t myQueue,myQueue2,myQueue3;
SemaphoreHandle_t pista1,pista2,pista3;
const char* nombresAviones[] = {"AVION1", "AVION2", "AVION3", "AVION4", "AVION5"};//Le asocio un puntero de char donde despues voy a indentificarlos como palabras 
void setup() {
  
  myQueue = xQueueCreate(5, sizeof(AvionCommand));
  pista1 = xSemaphoreCreateMutex(); 
  pista2 = xSemaphoreCreateMutex(); 
  pista3 = xSemaphoreCreateMutex(); 
  Serial.begin(115200);
  delay(3000);

  xTaskCreatePinnedToCore(
    Avion,     // Referencia a la funcion que vamos a ejecutar
    "Task_Core1",  // Nombre para la funcion, sirve solamente para propositos de debugging
    4096,          // Tamaño del stack la tarea
    NULL,          // Parametro que recibe la funcion que le vamos a pasar
    1,             // Prioridad de la tarea
    NULL,          // no es importante
    0              // El core donde queremos que corra la task (0/1)
  );


  xTaskCreatePinnedToCore(
    Torre,     // Referencia a la funcion que vamos a ejecutar
    "Task_Core4",  // Nombre para la funcion, sirve solamente para propositos de debugging
    4096,          // Tamaño del stack la tarea
    NULL,          // Parametro que recibe la funcion que le vamos a pasar
    1,             // Prioridad de la tarea
    NULL,          // no es importante
    1              // El core donde queremos que corra la task (0/1)
  );


}

void Avion(void *parameter){
  for (;;) {
    AvionCommand avionrandom= randomCommand();
    xQueueSend(myQueue, &avionrandom, portMAX_DELAY);
  }
}
void Torre(void *parameter){
  for (;;) {
    AvionCommand control;
    Serial.printf("Avion solicita aterrizar en pista disponible\n");
    vTaskDelay(pdMS_TO_TICKS(3000));
    if (xSemaphoreTake(pista1, portMAX_DELAY) == pdTRUE){
      Serial.printf("Aqui torre de control pista1 esta libre para su aterrizaje\n");
      vTaskDelay(pdMS_TO_TICKS(3000));
      xQueueReceive(myQueue, &control, portMAX_DELAY);
    }
    else{
      Serial.printf("Aqui torre de control pista1 esta ocupada para su aterrizaje\n");
    }

    if (xSemaphoreTake(pista2, portMAX_DELAY) == pdTRUE){
      Serial.printf("Aqui torre de control pista2 esta libre para su aterrizaje\n");
      vTaskDelay(pdMS_TO_TICKS(3000));
      xQueueReceive(myQueue, &control, portMAX_DELAY);
    }    
    else{
      Serial.printf("Aqui torre de control pista2 esta ocupada para su aterrizaje\n");
    }
    if (xSemaphoreTake(pista3, portMAX_DELAY) == pdTRUE){
      Serial.printf("Aqui torre de control pista3 esta libre para su aterrizaje\n");
      vTaskDelay(pdMS_TO_TICKS(3000));
      xQueueReceive(myQueue, &control, portMAX_DELAY);
    }
    else{
      Serial.printf("Aqui torre de control pista3 esta ocupada para su aterrizaje\n");
    }
    xSemaphoreGive(pista1);
    xSemaphoreGive(pista2);
    xSemaphoreGive(pista3);

    Serial.printf("Avion en pista:\n");
    Serial.println(nombresAviones[control]);  
    vTaskDelay(pdMS_TO_TICKS(3000));
    Serial.printf("Avion despeja la pista\n");
    vTaskDelay(pdMS_TO_TICKS(5000));

    
  }
}  
void loop() {
}