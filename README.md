# Controle de LEDs com Raspberry Pi Pico

Este projeto implementa um controle de LEDs utilizando um Raspberry Pi Pico. Os LEDs acendem  ao pressionar o botão, desligando gradualmente a cada 3 segundos.

## Requisitos
- Raspberry Pi Pico
- LEDs conectados aos GPIOs 11, 12 e 13
- Botão conectado ao GPIO 5
- SDK do Raspberry Pi Pico W
- Ambiente de desenvolvimento VS Code
- Simulador Wokwi online.
- Simulador Wokwi integrado ao VS Code
- Repositório GitHub para versionamento

## Funcionalidades
1. **Acionamento do Botão:**
   - Quando o botão (GPIO 5) é pressionado, todos os LEDs acendem simultaneamente.
   - Após um atraso de 3 segundos, o primeiro LED é desligado.
   - Em seguida, a cada 3 segundos, os LEDs desligam um por um até que todos estejam apagados.

2. **Gerenciamento por Callbacks:**
   - A função `turn_off_callback()` é utilizada para gerenciar o desligamento sequencial dos LEDs.
   - Um temporizador (`add_alarm_in_ms()`) é usado para definir os atrasos entre cada transição.

3. **Bloqueio de Novas Ações Durante a Execução:**
   - O botão só pode ser pressionado novamente após todos os LEDs estarem apagados.
   - A função `todos_leds_inativos()` impede o acionamento repetitivo antes da finalização do ciclo.

4. **Debounce por Software:**
   - Um pequeno atraso de 50ms é inserido para evitar leituras incorretas do botão.

## Estrutura do Código
- **`iniciar_leds()`**: Inicializa os LEDs e configura-os como saída.
- **`iniciar_botao()`**: Configura o botão como entrada e habilita um resistor pull-up interno.
- **`turn_off_callback()`**: Callback responsável por desligar os LEDs sequencialmente.
- **`leds_true()`**: Acende todos os LEDs ao mesmo tempo.
- **`todos_leds_inativos()`**: Retorna `true` se todos os LEDs estiverem apagados.
- **Loop principal (`main`)**:
  - Verifica se o botão foi pressionado e se os LEDs estão apagados.
  - Se as condições forem atendidas, inicia o ciclo de acionamento e desligamento dos LEDs.

## Simulação
- Utilize a ferramenta BitDogLab ou Wokwi para testar o comportamento dos LEDs.
- No Wokwi, mapeie os LEDs para os GPIOs 11, 12 e 13 e o botão para o GPIO 5.

## Como Executar
1. Clone o repositório do projeto:
   ```sh
   git clone [<URL_DO_REPOSITORIO>](https://github.com/hbCosta/Temporizador-de-um-Disparo.git)
   ```
2. Compile e carregue o código utilizando a extensão Raspberry Pi Pico no VsCode.
3. Pressione o botão para iniciar a sequência de LEDs.
4. Utilize um simulador como Wokwi para testar virtualmente o código.


## Licença
Este projeto está licenciado sob a licença MIT.

