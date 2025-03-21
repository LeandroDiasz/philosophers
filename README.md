# Philosophers

## 📌 Sobre o projeto
O projeto **Philosophers** é um exercício de concorrência, threads e mutexes. Inspirado no clássico problema dos "filósofos famintos", este projeto simula o comportamento de filósofos sentados em uma mesa, onde compartilham garfos e devem alternar entre os estados de **comer**, **dormir** e **pensar** sem criar um deadlock.

## 🛠️ Tecnologias e conceitos utilizados
- Linguagem C
- Threads (`pthread`)
- Mutexes (`pthread_mutex`)
- Programação concorrente
- Sincronização de threads

## 📋 Regras do projeto
- Cada filósofo precisa pegar **dois garfos** para comer.
- Eles alternam entre os estados de **pensar**, **comer** e **dormir**.
- Se um filósofo não comer dentro do tempo determinado (`time_to_die`), ele morre.
- O programa deve parar quando um filósofo morre ou quando um número específico de refeições for atingido (caso esse parâmetro seja passado).

## 📦 Compilação e execução
### 🔧 Como compilar
Para compilar o projeto, execute:
```sh
make
```
Isso gerará um executável chamado `philo`.

### ▶️ Como executar
O programa recebe os seguintes argumentos:
```sh
./philo <num_philos> <time_to_die> <time_to_eat> <time_to_sleep> [num_meals]
```
Onde:
- `<num_philos>`: Número de filósofos.
- `<time_to_die>`: Tempo (em milissegundos) até que um filósofo morra se não comer.
- `<time_to_eat>`: Tempo (em milissegundos) que um filósofo leva para comer.
- `<time_to_sleep>`: Tempo (em milissegundos) que um filósofo leva para dormir.
- `[num_meals]` (opcional): Número de refeições que cada filósofo deve fazer antes do programa encerrar.

#### Exemplo de execução:
```sh
./philo 5 800 200 200
```
Isso inicia uma simulação com 5 filósofos, onde eles morrem após 800ms sem comer, levam 200ms para comer e 200ms para dormir.

## 🧐 Problemas comuns e soluções
- **Um filósofo sozinho não finaliza o programa**: O monitor deve encerrar corretamente quando há apenas um filósofo, pois ele nunca conseguirá pegar dois garfos.
- **Pequenas variações nos tempos de impressão**: Isso pode ocorrer devido ao `usleep` e à natureza concorrente das threads.
- **Deadlock**: O código deve garantir que os filósofos sempre consigam pegar e liberar os garfos corretamente.

---
Criado por [Leandro Dias](https://github.com/seu-perfil) 🚀

