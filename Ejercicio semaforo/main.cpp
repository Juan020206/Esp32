#define rojo 26 // Definimos un valor especifico a una variable
#define amarillo 27
#define verde 33
#define rojo2 18
#define amarillo2 19
#define verde2 21

SemaphoreHandle_t mySemaphore;  // declaracion de la varaible que vamos a usar como semaforo

void setup() {
  pinMode(rojo, OUTPUT);// Asignamos los pines digitales
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(rojo2, OUTPUT);
  pinMode(amarillo2, OUTPUT);
  pinMode(verde2, OUTPUT);
  Serial.begin(115200);
    mySemaphore = xSemaphoreCreateMutex(); // permite que solo una tarea a la vez pueda acceder a ciertos recursos

  xTaskCreatePinnedToCore(
    semaforo1,     // Referencia a la funcion que vamos a ejecutar
    "Task_Core1",  // Nombre para la funcion, sirve solamente para propositos de debugging
    4096,          // Tamaño del stack la tarea
    NULL,          // Parametro que recibe la funcion que le vamos a pasar
    1,             // Prioridad de la tarea
    NULL,          // no es importante
    1              // El core donde queremos que corra la task (0/1)
  );

  xTaskCreatePinnedToCore(
    semaforo2,     // Referencia a la funcion que vamos a ejecutar
    "Task_Core2",  // Nombre para la funcion, sirve solamente para propositos de debugging
    4096,          // Tamaño del stack la tarea
    NULL,          // Parametro que recibe la funcion que le vamos a pasar
    1,             // Prioridad de la tarea
    NULL,          // no es importante
    0              // El core donde queremos que corra la task (0/1)
  );
 // En este caso queremos que sea un mutex.
}

void semaforo1(void *parameter) {
  for (;;) {
    if (xSemaphoreTake(mySemaphore, portMAX_DELAY) == pdTRUE) { // Se determina la condicion de que si se obtiene el semaforo se cumple el if


      //rojo
      digitalWrite(rojo, HIGH);
      digitalWrite(amarillo, LOW);
      digitalWrite(verde, LOW);
      delay(4000);

      //verde
      digitalWrite(rojo, LOW);
      digitalWrite(amarillo, LOW);
      digitalWrite(verde, HIGH);
      delay(3000);

      //amarillo
      digitalWrite(rojo, LOW);
      digitalWrite(amarillo, HIGH);
      digitalWrite(verde, LOW);
      delay(1000);
    }
    xSemaphoreGive(mySemaphore);//Libera el semaforo
  }
}

void semaforo2(void *parameter) {
  for (;;) {
    if (xSemaphoreTake(mySemaphore, portMAX_DELAY) == pdTRUE) {

      //Verde
      digitalWrite(rojo2, LOW);
      digitalWrite(amarillo2, LOW);
      digitalWrite(verde2, HIGH);
      delay(3000);

      //amarillo
      digitalWrite(rojo2, LOW);
      digitalWrite(amarillo2, HIGH);
      digitalWrite(verde2, LOW);
      delay(1000);

      //rojo
      digitalWrite(rojo2, HIGH);
      digitalWrite(amarillo2, LOW);
      digitalWrite(verde2, LOW);
      delay(4000);
    }
    xSemaphoreGive(mySemaphore);
  }
}


void loop() {
}
