#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
// Creamos un cliente de MQTT con la conexión a internet via wifi
PubSubClient client(espClient);

// Callback (una función con una firma particular) que responderá ante un nuevo mensaje recibido
void callback(char* topic, byte* payload, unsigned int length) {
  // Iteramos el payload
  char letra;
  for (int i = 0; i < length; i++) {
  letra=(char)payload[i];
  Serial.print(letra);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);

  // Conectarse a una red por nombre + contraseña
  WiFi.begin("Wifi", "Contraseña");


  while (WiFi.status() != WL_CONNECTED){
    Serial.println("No se pudo conectar");
    Serial.println("Reintentando...");
    delay(4000);
  }
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Conectado");

  }


  // Realizamos la conexión con el servidor
  client.setServer("broker.hivemq.com", 1883);

  client.connect("ESP32_SENSOR_01"); // devuelve un booleano indicando si se conectó correctamente

  client.connected(); // devuelve un booleano que nos permite chequear si la conexión fue exitosa
  while(!client.connected()){
    Serial.println("Error de conexion de broker");
    Serial.println("Reintentando");
    delay(3000);
  }
  if(client.connected()){
    Serial.println("conectado al broker");
  }
  client.subscribe("huergo/sistemas-embebidos/Tobares"); // seguir patrón del tópico a escuchar

  // Configuramos el cliente con el callback correcto
  client.setCallback(callback);
}

void loop() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    String msg_user= "Tobares:"+ msg;
    client.publish("huergo/sistemas-embebidos/Tobares", msg.c_str()); // convertir el mensaje mediante .c_str()
    client.loop();
  }
}

