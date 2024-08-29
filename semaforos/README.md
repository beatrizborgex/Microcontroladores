# Projeto de Controlador de Semáforos

## Descrição

Este projeto controla dois semáforos em um cruzamento e inclui um semáforo de pedestre. O controlador foi desenvolvido utilizando o simulador Wokwi e está configurado para gerenciar diferentes estados dos semáforos, incluindo um estado especial acionado por comunicação Serial.

## Arquivos

- `src/sketch.ino`: Código fonte do microcontrolador.
- `diagrams/diagram.json`: Diagrama do circuito eletrônico.
- `docs/wokwi-project.txt`: Informações sobre o projeto no Wokwi.

## Funcionamento

1. **Estados dos Semáforos:**
   - **S0**: Primeiro semáforo vermelho, segundo semáforo verde.
   - **S1**: Primeiro semáforo vermelho, segundo semáforo amarelo.
   - **S2**: Primeiro semáforo verde, segundo semáforo vermelho.
   - **S3**: Primeiro semáforo amarelo, segundo semáforo vermelho.
   - **S4**: Ambos os semáforos com LED amarelo piscando (acionado via Serial com a palavra "amarelo").

2. **Comandos Serial:**
   - Enviar "amarelo": Ativa o estado S4.
   - Enviar "semáforo": Retorna ao ciclo normal de semáforos.

3. **Semáforo de Pedestre:**
   - Pressionar um botão: Todos os semáforos ficam vermelhos e o semáforo de pedestre acende em verde.
   - Após um tempo, o semáforo de pedestre apaga e os semáforos voltam ao funcionamento normal.

## Instruções

1. Importe o projeto para o Wokwi para simulação.
2. Faça upload do código para o microcontrolador utilizando o Arduino IDE.
3. Teste o funcionamento dos semáforos e do semáforo de pedestre conforme descrito acima.


