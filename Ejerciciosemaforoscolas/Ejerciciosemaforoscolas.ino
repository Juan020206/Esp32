#include "data.h"
#define rojo 27
#define amarillo 26
#define verde 25
QueueHandle_t myQueue;


void setup() {
  pinMode(rojo, OUTPUT);// Asignamos los pines digitales
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);
  myQueue = xQueueCreate(30, sizeof(LedCommand));
  Serial.begin(115200);
  delay(100);
  xTaskCreatePinnedToCore(
    productor,     // Referencia a la funcion que vamos a ejecutar
    "Task_Core1",  // Nombre para la funcion, sirve solamente para propositos de debugging
    4096,          // Tamaño del stack la tarea
    NULL,          // Parametro que recibe la funcion que le vamos a pasar
    1,             // Prioridad de la tarea
    NULL,          // no es importante
    1              // El core donde queremos que corra la task (0/1)
  );

  xTaskCreatePinnedToCore(
    consumidor,     // Referencia a la funcion que vamos a ejecutar
    "Task_Core2",  // Nombre para la funcion, sirve solamente para propositos de debugging
    4096,          // Tamaño del stack la tarea
    NULL,          // Parametro que recibe la funcion que le vamos a pasar
    1,             // Prioridad de la tarea
    NULL,          // no es importante
    0              // El core donde queremos que corra la task (0/1)
  );


}

void productor(void *parameter){
  for (;;) {
    LedCommand random= randomCommand();
    if(random == LED_BLINK){//Si el random es LED_BLINK lo manda al frente de la cola
      xQueueSendToFront(myQueue, &random, 0);
    }
    else{//Si no es LED_BLINK solo lo envia mientras haya espacio en la cola
      xQueueSend(myQueue, &random, portMAX_DELAY);
    }


  }
}
void consumidor(void *parameter){
  for (;;) {
    LedCommand colores;
    xQueueReceive(myQueue, &colores, portMAX_DELAY);
    Serial.printf("color:");
    Serial.println(colores);
    if(colores == LED_RED)
    { 
      digitalWrite(rojo, HIGH);
      delay(1000);
      digitalWrite(rojo, LOW);
    }
    if(colores == LED_GREEN)
    { 
      digitalWrite(verde, HIGH);
      delay(1000);
      digitalWrite(verde, LOW);
    }
    if(colores == LED_YELLOW)
    { 
      digitalWrite(amarillo, HIGH);
      delay(1000);
      digitalWrite(amarillo, LOW);
    }
   if(colores == LED_BLINK)//En esta condicion con LED_BLINK hace parpadear todos los leds durante un segundo
    { 
      digitalWrite(rojo, HIGH);
      digitalWrite(verde, HIGH);
      digitalWrite(amarillo, HIGH);
      delay(200);
      digitalWrite(rojo, LOW);
      digitalWrite(verde, LOW);
      digitalWrite(amarillo, LOW);
      delay(200);
      digitalWrite(rojo, HIGH);
      digitalWrite(verde, HIGH);
      digitalWrite(amarillo, HIGH);
      delay(200);
      digitalWrite(rojo, LOW);
      digitalWrite(verde, LOW);
      digitalWrite(amarillo, LOW);
      delay(200);
      digitalWrite(rojo, HIGH);
      digitalWrite(verde, HIGH);
      digitalWrite(amarillo, HIGH);
      delay(200);
      digitalWrite(rojo, LOW);
      digitalWrite(verde, LOW);
      digitalWrite(amarillo, LOW);
    }
  }
}  
void loop() {
}