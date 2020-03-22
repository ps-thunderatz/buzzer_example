# Buzzer Example

Esse repositório contém um exemplo de como controlar um buzzer usando timers.

## Descrição do cube e hardware

| Pino | Configuração | Função |
|:---  |:---          |:---    |
| PA8  | TIM1_CH1     | Controlar um buzzer |

**Observações:**

* PA8 corresponde ao pino D7 na Nucleo F303RE.
* A polaridade do canal foi invertida para ser usado com um transistor PNP no acionamento.
