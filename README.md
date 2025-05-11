**Código Semáforo**

El programa empieza con varios define definiendo a una variable con un valor especifico en este caso hacemos referencia a los colores propios del semáforo para mayor entendimiento y rápida reasignación de patas digitales ante un inconveniente.
A partir de la siguiente linea: "SemaphoreHandle_t mySemaphore;" declaramos una variable para utilizar de semáforo mas adelante.
En el void setup() asignaremos pines digitales como salidas para el semáforo.En la siguiente linea igualamos la variable "mySemaphore" a un "xSemaphoreCreateMutex()" para permitir que solo una tarea a la vez pueda acceder a ciertos recursos.El "xTaskCreatePinnedToCore" nos permites asignar diferentes tareas en diferentes núcleos.

Fuera del Void Setup() creamos dos "void semaforo1(void *parameter)", que dentro de estos crearemos un loop con un for y dentro de este a través de un if haremos el patron de los leds de colores del semáforo.El if lo que hace es con el "xSemaphoreTake" obtiene el semaforo anterior creado que es el "MySemaphore", esta variable junto con "portMAX_DELAY" que es un tiempo de bloque para bloquear indefinidamente el otro semáforo, son igualados a pdTrue que hace referencia a que si se obtuvo el semaforo, haciendo que la condicion sea si se obtuvo el semaforo se cumpla el patron de colores dentro del if, quedando bloqueado el otro semaforo hasta que termine la tarea.
