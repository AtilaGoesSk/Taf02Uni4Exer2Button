#include <stdio.h>  // Biblioteca padrão do C.
#include "pico/stdlib.h"  // Biblioteca para controle de GPIO, temporização e comunicação serial.
#include "pico/time.h"   // Biblioteca para temporizadores e alarmes.

const uint LED_PIN_GREEN = 11;   // Pino GPIO para LED verde.
const uint LED_PIN_BLUE = 12;    // Pino GPIO para LED azul.
const uint LED_PIN_RED = 13;     // Pino GPIO para LED vermelho.

const uint BUTTON_A = 5;         // Pino GPIO para o botão (pushbutton).

bool led_RED_on = false;         // Estado do LED vermelho.
bool led_BLUE_on = false;        // Estado do LED azul.
bool led_GREEN_on = false;       // Estado do LED verde.

bool led_active = false;         // Indica se o temporizador está ativo.
absolute_time_t turn_off_time;   // Armazena o tempo em que o LED deve ser desligado.

int led_count = 0;  // Contador para controlar a mudança de estados dos LEDs.

int64_t turn_off_callback_desligar_led_vermelho(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_RED, false);  // Desliga o LED vermelho
    led_RED_on = false;
    led_count--;
    return 0;
}

int64_t turn_off_callback_desligar_led_azul(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_BLUE, false);  // Desliga o LED azul
    led_BLUE_on = false;
    led_count--;
    return 0;
}

int64_t turn_off_callback_desligar_led_verde(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_GREEN, false); // Desliga o LED verde
    led_GREEN_on = false;
    led_active = false; // Finaliza a sequência
    return 0;
}

void debounce_button() {
    // Simples rotina de debounce para evitar múltiplas leituras erradas do botão.
    sleep_ms(50);
}

int main() {
    stdio_init_all();

    // Configura os pinos dos LEDs como saída.
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    // Configura o pino do botão como entrada com pull-up.
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    // Loop principal que verifica o estado do botão.
    while (true) {
        if (gpio_get(BUTTON_A) == 0 && !led_active) {
            debounce_button();

            // Verifica novamente o estado do botão após o debounce.
            if (gpio_get(BUTTON_A) == 0) {
                // Aciona os LEDs.
                gpio_put(LED_PIN_RED, true);
                gpio_put(LED_PIN_BLUE, true);
                gpio_put(LED_PIN_GREEN, true);
                led_RED_on = true;
                led_BLUE_on = true;
                led_GREEN_on = true;

                led_active = true;
                led_count = 3;

                // Agendando os alarmes para a mudança dos LEDs.
                add_alarm_in_ms(3000, turn_off_callback_desligar_led_azul, NULL, false);
                add_alarm_in_ms(6000, turn_off_callback_desligar_led_vermelho, NULL, false);
                add_alarm_in_ms(9000, turn_off_callback_desligar_led_verde, NULL, false);
            }
        }

        // Delay para reduzir o uso excessivo de CPU.
        sleep_ms(10);
    }

    return 0;
}
