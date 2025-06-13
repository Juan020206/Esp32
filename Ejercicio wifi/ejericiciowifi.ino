#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
// Creamos un cliente de MQTT con la conexión a internet via wifi
PubSubClient client(espClient);

// Callback (una función con una firma particular) que responderá ante un nuevo mensaje recibido
void callback(char* topic, byte* payload, unsigned int length) {
  // Iteramos el payload
  for (int i = 0; i < length; i++) {
    
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);

  // Conectarse a una red por nombre + contraseña
  WiFi.begin("MovistarSoraya", "15430253656");

  if (WiFi.status() != WL_CONNECTED){
    // aun no esta conectado
  }
  // ok

  // Realizamos la conexión con el servidor
  client.setServer("broker.hivemq.com", 1883);

  client.connect("ESP32_SENSOR_01"); // devuelve un booleano indicando si se conectó correctamente

  client.connected(); // devuelve un booleano que nos permite chequear si la conexión fue exitosa

  client.subscribe("casa/sala/temperatura"); // seguir patrón del tópico a escuchar

  // Configuramos el cliente con el callback correcto
  client.setCallback(callback);
}

void loop() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
  }

  client.publish("casa/sala/temperatura", "13 °C"); // convertir el mensaje mediante .c_str()

  client.loop();
}
