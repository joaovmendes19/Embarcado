#include <Servo.h>

// Definindo pinos ultrassônicos
#define trigPin 3
#define echoPin 2

// Definindo pino para o sensor de luz
#define photoresistorPin A5

// Definindo pino para motor
#define servoPin 7
Servo myServo;

bool gateOpen = false;
bool gateClosing = false;
unsigned long gateOpenTime = 0;

// Função para abrir o portão
void openGate() {
    myServo.write(0); // Abrir o portão
    gateOpen = true;
    gateClosing = false;
    gateOpenTime = millis(); // Registrar o tempo em que o portão foi aberto
    Serial.println("Portão aberto.");
}

// Função para fechar o portão
void closeGate() {
    myServo.write(90); // Fechar o portão
    gateOpen = false;
    gateClosing = false;
    Serial.println("Portão fechado.");
}

// Função para imprimir dados do sensor ultrassônico
void printUltrasonicData() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    float duration = pulseIn(echoPin, HIGH);
    float distance = duration * 0.034 / 2;
    Serial.print("Distância Ultrassônica: ");
    Serial.print(distance);
    Serial.println(" cm");
}

// Função para imprimir dados do sensor de luz
void printPhotoresistorData() {
    int lightValue = analogRead(photoresistorPin);
    Serial.print("Valor do Fotoresistor: ");
    Serial.println(lightValue);
}

// Função simulada para receber dados do ESP CAM
bool receiveDataFromEspCamSimulated() {
    // Simula recebimento de "true" em intervalos de tempo
    static unsigned long lastTime = 0;
    unsigned long currentTime = millis();
    
    // Simula recebimento de "true" a cada 10 segundos
    if (currentTime - lastTime >= 10000) {
        lastTime = currentTime;
        Serial.println("Simulated ESP CAM: true");
        return true;
    }
    
    Serial.println("Simulated ESP CAM: false");
    return false;
}

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(photoresistorPin, INPUT);
    myServo.attach(servoPin);
    myServo.write(90); // Portão fechado
    Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
    // Imprimir dados dos sensores no monitor serial
    printUltrasonicData();
    printPhotoresistorData();

    if (!gateOpen && !gateClosing) {
        // Verificar a distância do veículo
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        float duration = pulseIn(echoPin, HIGH);
        float distance = duration * 0.034 / 2;

        bool espCamSignal = receiveDataFromEspCamSimulated();

        if (espCamSignal && distance < 20) {
            openGate();
        }
    } else if (gateOpen) {
        // Verificar a leitura do fotoresistor após 5 segundos do portão estar aberto
        if (millis() - gateOpenTime > 5000) {
            int lightValue = analogRead(photoresistorPin);
            if (lightValue > 900) {
                Serial.println("Leitura do fotoresistor acima de 900. Fechando portão.");
                delay(3000); // Espera 3 segundos antes de fechar o portão
                closeGate();
            } else {
                Serial.println("Leitura do fotoresistor abaixo de 900. Mantendo portão aberto.");
            }
        }
    }

    // Pequeno delay para não sobrecarregar o monitor serial
    delay(500);
}
