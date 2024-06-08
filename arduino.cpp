#include <Servo.h>

// Definido pinos ultrassônico
#define trigPin 3
#define echoPin 2

// Definido pino para o sensor de luz
#define photoresistorPin A5

// Definindo pino para motor
#define servoPin 7
Servo myServo;

bool gateOpen = false;

// Função para abrir o portão
void openGate() {
    myServo.write(180); // Abrir o portão
    gateOpen = true;
}

// Função para fechar o portão
void closeGate() {
    myServo.write(0); // Fechar o portão
    gateOpen = false;
}

// Função para verificar se o carro passou
bool carPassed() {
    int lightValue = analogRead(photoresistorPin);
    return lightValue > 100; // Ajuste este valor conforme necessário
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

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(photoresistorPin, INPUT);
    myServo.attach(servoPin);
    myServo.write(0); // Portão fechado
    Serial.begin(9600);
}

void loop() {
    // Imprimir dados dos sensores no monitor serial
    printUltrasonicData();
    printPhotoresistorData();

    // Verificar a distância do veículo
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    float duration = pulseIn(echoPin, HIGH);
    float distance = duration * 0.034 / 2;

    if (distance < 20) {
        Serial.println("Imagens enviadas");
        delay(5000);
        Serial.println("Resposta recebida");
        openGate();

        while (!carPassed()) {
            delay(100);
            printPhotoresistorData();
        }

        if (carPassed()) {
            closeGate();
        }
    }

    // Pequeno delay para não sobrecarregar o monitor serial
    delay(500);
}
