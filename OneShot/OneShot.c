#include <stdio.h>
#include "pico/stdlib.h"


const uint led_azul = 11;
const uint led_vermelho = 12;
const uint led_verde = 13;

const uint button_pin = 5;

bool led_azul_active = false;
bool led_vermelho_active = false;
bool led_verde_active = false;
int estado = 0;

// Função para inicializar os leds e setar eles como saída
void iniciar_leds(){
  gpio_init(led_azul);
  gpio_init(led_vermelho);
  gpio_init(led_verde);

  gpio_set_dir(led_azul, GPIO_OUT);
  gpio_set_dir(led_vermelho, GPIO_OUT);
  gpio_set_dir(led_verde, GPIO_OUT);
}

// Função para inicializar o botão e setar ele como entrada
void iniciar_botao(){
  gpio_init(button_pin);
  gpio_set_dir(button_pin, GPIO_IN);
  // Habilita o resistor pull-up interno para o pino do botão.
  // Isso garante que o pino seja lido como alto (3,3 V) quando o botão não está pressionado.
  gpio_pull_up(button_pin);

}

int64_t turn_off_callback(alarm_id_t id, void *user_data) {
  if(estado == 0){
    // Desliga o LED configurando o pino LED_PIN para nível baixo.
    gpio_put(led_azul, false);
    // Atualiza o estado de 'led_active' para falso, indicando que o LED está desligado.
    led_azul_active = false;
    estado = 1;
    add_alarm_in_ms(3000, turn_off_callback, NULL, false);
  }else if(estado == 1){
    // Desliga o LED configurando o pino LED_PIN para nível baixo.
    gpio_put(led_vermelho, false);
    // Atualiza o estado de 'led_active' para falso, indicando que o LED está desligado.
    led_vermelho_active = false;
    estado = 2;
    add_alarm_in_ms(3000, turn_off_callback, NULL, false);
  }else{
    gpio_put(led_verde, false);
    led_verde_active = false;
    estado = 0;
  }


  // Retorna 0 para indicar que o alarme não deve se repetir.
  return 0;
}

void leds_true(){
  gpio_put(led_azul, true);
  led_azul_active = true;
  
  gpio_put(led_vermelho, true);
  led_vermelho_active = true;

  gpio_put(led_verde, true);
  led_verde_active = true;
}

bool todos_leds_inativos() {
  return !led_azul_active && !led_vermelho_active && !led_verde_active;
}

int main() {
  // Inicializa a comunicação serial para permitir o uso de printf.
  stdio_init_all();
  // Chamada das funções de inicializar leds e botão
  iniciar_leds();
  iniciar_botao();

  while (true) {
    // Verifica se o botão foi pressionado para nível logico baixo e se todos os leds estão inativos
    if(gpio_get(button_pin)== 0 && todos_leds_inativos()){
      // Adiciona um pequeno atraso para debounce, evitando leituras errôneas.
      sleep_ms(50);
      // Verifica novamente o estado do botão após o debounce.
      if(gpio_get(button_pin) == 0){
        // Chama a função de configurar os LEDs para nível alto.
        leds_true();
        // Chama a função para desligar os LEDs um por um após 3 segundos (3000 ms)
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
      }

    }

    sleep_ms(10);
  }

  return 0;
}