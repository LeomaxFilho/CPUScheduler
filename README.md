# CPU Scheduler

Este projeto, desenvolvido para a disciplina de Sistemas Operacionais I, consiste em uma aplicação em C++ que simula o comportamento de diferentes algoritmos de escalonamento de processos da CPU. A aplicação lê uma lista de processos de um arquivo de entrada, executa as simulações e calcula métricas de desempenho para cada algoritmo.

## 📜 Sumário

* [Sobre o Projeto](#-sobre-o-projeto)
* [Algoritmos Implementados](#-algoritmos-implementados)
* [Métricas de Desempenho](#-métricas-de-desempenho)
* [Estrutura do Projeto](#-estrutura-do-projeto)
* [Como Compilar e Executar](#-como-compilar-e-executar)

## 📖 Sobre o Projeto

O objetivo principal é comparar o desempenho de três algoritmos de escalonamento clássicos: FCFS, SJF e Round Robin. O programa analisa um conjunto de processos, cada um com seu tempo de chegada e duração, e calcula tempos médios de retorno, resposta e espera para avaliar a eficiência de cada algoritmo.

## ⚙️ Algoritmos Implementados

O simulador implementa os seguintes algoritmos:

1.  **FCFS (First-Come, First-Served)**: Um algoritmo não preemptivo onde os processos são executados na ordem exata em que chegam na fila de prontos.
2.  **SJF (Shortest Job First)**: Um algoritmo não preemptivo que seleciona o processo com a menor duração (burst time) entre todos que já chegaram.
3.  **Round Robin (RR)**: Um algoritmo preemptivo que aloca a CPU para cada processo por um curto período de tempo (`quantum`). Se o processo não terminar nesse intervalo, ele volta para o final da fila de prontos. Neste projeto, foi utilizado um **quantum de 2 unidades de tempo**.

## 📊 Métricas de Desempenho

Para cada algoritmo, o programa calcula as seguintes métricas médias:

* **Tempo de Retorno (Turnaround Time)**: O tempo total que um processo leva desde a sua chegada até a sua conclusão.
* **Tempo de Resposta (Response Time)**: O tempo desde a chegada do processo até o início de sua *primeira* execução.
* **Tempo de Espera (Waiting Time)**: O tempo total que um processo passa na fila de prontos, esperando para usar a CPU.

## 📂 Estrutura do Projeto

O código-fonte está organizado nos seguintes arquivos:

* **`main.cc`**: O ponto de entrada do programa. É responsável por ler o arquivo de entrada, popular o escalonador com os processos e invocar os algoritmos de escalonamento.
* **`cpu-scheduler.hh` / `cpu-scheduler.cc`**: Define e implementa a classe `CPUScheduler`. Esta classe encapsula a lista de processos e contém a lógica para os algoritmos FCFS, SJF e RR, além de funções auxiliares para exibir os resultados.
* **`process.hh` / `process.cc`**: Define a estrutura `Process`, que armazena todas as informações relevantes de um processo, como ID, tempo de chegada, duração e as métricas calculadas.
* **`inputs/`**: Diretório contendo os arquivos de texto (`.txt`) com as listas de processos a serem testadas.

## 🚀 Como Compilar e Executar

Siga os passos abaixo para compilar e rodar o projeto.

### Pré-requisitos

* Compilador C++ (g++ recomendado)

### Compilação

Para compilar o projeto, execute o seguinte comando no seu terminal, a partir do diretório raiz do projeto:
```sh
g++ -std=c++17 -o scheduler main.cc cpu-scheduler.cc process.cc
```

isso irá gerar um executável chamado scheduler.

### Execução
Para executar o programa, basta rodar o executável gerado. O arquivo de entrada já está definido no main.cc como inputs/procs_3.txt.

```sh
./scheduler
```

Para testar com um arquivo de entrada diferente, você pode alterar o caminho do arquivo no main.cc e recompilar o projeto.


