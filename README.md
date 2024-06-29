# Projeto Arduino: Controle de Portão Automático

Este repositório contém um projeto de controle de portão automático utilizando um Arduino, um servo motor, sensores ultrassônicos e um fotoresistor. O portão é controlado automaticamente com base na distância do veículo e na intensidade da luz ambiente.

## Componentes Necessários

- Arduino (Uno, Mega, Nano, etc.)
- Servo Motor
- Sensor Ultrassônico (HC-SR04)
- Fotoresistor
- Jumpers
- Protoboard (opcional)
- Resistor de 10kΩ (para o fotoresistor)

## Diagrama de Conexões

1. **Servo Motor:**
   - Fio de Sinal  -> Pino 7 do Arduino
   - Fio de Alimentação  -> Pino 5V do Arduino
   - Fio de Terra  -> Pino GND do Arduino

2. **Sensor Ultrassônico:**
   - VCC -> Pino 5V do Arduino
   - GND -> Pino GND do Arduino
   - Trig -> Pino 3 do Arduino
   - Echo -> Pino 2 do Arduino

3. **Fotoresistor:**
   - Um terminal do fotoresistor conectado ao pino A5 do Arduino
   - O outro terminal do fotoresistor conectado ao pino 5V do Arduino
   - Um resistor de 10kΩ conectado entre o pino A5 e o GND do Arduino

Como Carregar o Código no Arduino:

Conecte seu Arduino ao computador via USB.
Abra a IDE Arduino e copie o código acima.
Cole o código na IDE Arduino.
Selecione a placa e a porta correta em Ferramentas > Placa e Ferramentas > Porta.
Clique no botão Verificar (ícone de check) para compilar o código.
Clique no botão Carregar (ícone de seta para a direita) para enviar o código compilado para o Arduino.

Funcionamento:

O projeto utiliza um sensor ultrassônico para detectar a presença de um veículo.
Quando um veículo é detectado a menos de 20 cm e o sinal simulado do ESP CAM é recebido, o portão é aberto.
O portão permanece aberto por 5 segundos. Durante este tempo, a leitura do fotoresistor é monitorada.
Se a leitura do fotoresistor for maior que 900 após 5 segundos, o portão é fechado.
O sistema imprime as leituras dos sensores no monitor serial para monitoramento.

Contribuições:

Sinta-se à vontade para contribuir com melhorias ou novas funcionalidades para este projeto. Basta abrir uma issue ou enviar um pull request.

Contato:

Para dúvidas ou sugestões, entre em contato via email: joaovitrmendes@gmail.com
