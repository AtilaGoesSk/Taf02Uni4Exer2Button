Programa de Controle de LEDs com Botão e Temporizador
Este é um programa em C para o Raspberry Pi Pico que controla três LEDs (vermelho, azul e verde) com um botão. Quando o botão é pressionado, os LEDs acendem e, após um intervalo de tempo específico, cada LED é desligado em uma ordem predefinida, utilizando alarmes temporizados.

Funcionalidades
Controle de LEDs: Aciona os LEDs vermelho, azul e verde simultaneamente ao pressionar o botão.
Temporização: Cada LED será desligado após um tempo específico (azul após 3 segundos, vermelho após 6 segundos e verde após 9 segundos).
Debounce de Botão: A entrada do botão é debounced para evitar múltiplos acionamentos.
Materiais Necessários
Raspberry Pi Pico ou placa compatível.
3 LEDs (vermelho, azul e verde).
3 resistores (para os LEDs).
1 botão push-button.
Fios para conexão.
Esquema de Conexão
LEDs:
O LED vermelho está conectado ao pino GPIO 13.
O LED azul está conectado ao pino GPIO 12.
O LED verde está conectado ao pino GPIO 11.
Botão:
O botão está conectado ao pino GPIO 5. Utilize um resistor pull-up interno para garantir o estado correto.
Como Utilizar
Compilar o Código:

Certifique-se de ter o toolchain do Raspberry Pi Pico configurado.
Compile o código com o seguinte comando:
bash
Copiar
Editar
make
Carregar no Raspberry Pi Pico:

Conecte o Raspberry Pi Pico ao seu computador enquanto mantém pressionado o botão BOOTSEL.
O dispositivo aparecerá como uma unidade de armazenamento.
Copie o arquivo .uf2 gerado para o Raspberry Pi Pico.
Execução:

Após carregar o programa, o Raspberry Pi Pico será reiniciado automaticamente.
Pressione o botão para acionar os LEDs. Eles acenderão simultaneamente e, após o tempo de temporização configurado, cada LED será desligado na ordem definida.
Explicação do Código
GPIOs: O código usa os pinos GPIO 11, 12 e 13 para controlar os LEDs, e o pino GPIO 5 para ler o estado do botão.
Temporizadores: Utiliza a função add_alarm_in_ms() do SDK do Raspberry Pi Pico para agendar o desligamento de cada LED em tempos diferentes.
Debounce de Botão: O código inclui uma rotina simples de debounce para evitar leituras erradas do botão.
