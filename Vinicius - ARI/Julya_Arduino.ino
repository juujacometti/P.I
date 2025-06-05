// Julya Jacometti 

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"

// Insira as credenciais da rede Wi-Fi:
const char* ssid = "iPhone";
const char* password = "123456789";

// Insira o ID de implantação do Google Apps Script:
const char* GScriptId = "AKfycbyBTZrzsn_l3_qY5RhXZUeb_1zRiWTZHsy5gWcSYNRUVRmpfP2lwRAzK1Pm3EwH7K2VRA";

// Comando (insert_row ou append_row) e nome da aba no Google Sheets (padrão: Sheet1):
String payload_base = "{\"command\": \"insert_row\", \"sheet_name\": \"Página1\", \"values\": ";
String payload = "";

// Configuração do Google Sheets (não editar)
const char* host = "script.google.com";
const int httpsPort = 443;
const char* fingerprint = "";
String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;

// Declaração de variáveis que serão enviadas para o Google Sheets
  // Alteração dos nomes das variáveis para esteira 1, 2 e 3
int esteira1 = 0;
int esteira2 = 0;
int esteira3 = 0;

void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println('\n');

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  // Cria um novo cliente TLS usando a biblioteca HTTPSRedirect
  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");

  Serial.print("Connecting to ");
  Serial.println(host);

  // Tenta conectar no máximo 5 vezes
  bool flag = false;
  for (int i = 0; i < 5; i++) {
    int retval = client->connect(host, httpsPort);
    if (retval == 1) {
      flag = true;
      Serial.println("Connected");
      break;
    } else {
      Serial.println("Connection failed. Retrying...");
    }
  }

  if (!flag) {
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    return;
  }

  delete client;  // deleta o objeto HTTPSRedirect
  client = nullptr;
}

void loop() {
  // Gera dados aleatórios simulados para enviar
      // Alteração do nome das variáveis e alteraçãpo no número da randomização
  esteira1 = random(1, 3);
  esteira2 = random(1, 3);
  esteira3 = random(1, 3);

  static bool flag = false;
  if (!flag) {
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");
  }

  if (client != nullptr) {
    if (!client->connected()) {
      client->connect(host, httpsPort);
    }
  } else {
    Serial.println("Error creating client object!");
    return;
  }

  // Cria a string JSON que será enviada ao Google Sheets
      // Alteração no nome das variáveis para esteira 1, 2 e 3
  payload = payload_base + "\"" + esteira1 + "," + esteira2 + "," + esteira3 + "\"}";

  // Envia os dados ao Google Sheets
  Serial.println("Publishing data...");
  Serial.println(payload);
  if (client->POST(url, host, payload)) {

    // Se o envio foi bem-sucedido, pode-se fazer algo aqui
  } else {
    Serial.println("Error while connecting");
  }

  // Aguarda alguns segundos antes de enviar novamente
  delay(5000);
}
