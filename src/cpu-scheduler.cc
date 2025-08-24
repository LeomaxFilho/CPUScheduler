#include "cpu-scheduler.hh"

bool sortByArriveTime(Process& a, Process& b)
{
    return a.arrivalTime < b.arrivalTime;
}

void CPUScheduler:: flush()
{
    for (int i = 0; i < process.size(); i++)
    {
        process.at(i).responseTime =0;
        process.at(i).waitTime = 0;
        process.at(i).returnTime = 0;
    }
}

void CPUScheduler::addProcess(int arrive, int burst)
{
    process.push_back(Process(process.size(), arrive, burst));
    std::sort(process.begin(), process.end(), sortByArriveTime);
}

void CPUScheduler::showResults(const string algorithm, const vector<Process> procs)
{
    double averageResponseTimeProcess = 0;
    double averageWaitTimeProcess = 0;
    double averageReturnTimeProcess = 0;

    const int vectorSize = procs.size();

    for(auto var : procs)
    {
        averageResponseTimeProcess += var.responseTime;
        averageWaitTimeProcess += var.waitTime;
        averageReturnTimeProcess += var.returnTime;
    }

    averageResponseTimeProcess /= vectorSize;
    averageWaitTimeProcess /= vectorSize;
    averageReturnTimeProcess /= vectorSize;

    cout << fixed << setprecision(1) << algorithm << averageReturnTimeProcess << " " << averageResponseTimeProcess << " " << averageWaitTimeProcess << endl;
    flush();
}

void CPUScheduler::FCFS ()
{
    int count = process.size();
    int timeNow =  process.at(0).arrivalTime;

    for (int i = 0; i < count; i++)
    {
        process.at(i).responseTime = timeNow - process.at(i).arrivalTime;
        process.at(i).waitTime = timeNow - process.at(i).arrivalTime;
        process.at(i).returnTime = timeNow + process.at(i).timeToLeave - process.at(i).arrivalTime;

        timeNow += process.at(i).timeToLeave;

        if (i + 1 < count)
            if (timeNow < process.at(i + 1).arrivalTime)
                timeNow = process.at(i + 1).arrivalTime;
    }
    showResults("FCFS: ", process);
}

void CPUScheduler::SJF()
{
    vector<Process> procs = this->process;
    int currentTime = 0, n = procs.size(), completedProcesses = 0;
    vector<bool> isCompleted(n, false);

    if(n==0) return;

    while(completedProcesses < n){
        int shortestJobIndex = -1;
        int minBurstTime = INT_MAX;
        
        for(int i=0; i<n; i++)
            if(procs[i].arrivalTime <= currentTime && !isCompleted[i])
                if(procs[i].timeToLeave < minBurstTime){
                    minBurstTime = procs[i].timeToLeave;
                    shortestJobIndex = i;
                }

        if (shortestJobIndex != -1){

            procs[shortestJobIndex].responseTime = currentTime - procs[shortestJobIndex].arrivalTime;

            currentTime += procs[shortestJobIndex].timeToLeave;

            procs[shortestJobIndex].returnTime = currentTime - procs[shortestJobIndex].   arrivalTime;

            procs[shortestJobIndex].waitTime = procs[shortestJobIndex].returnTime - procs[shortestJobIndex].timeToLeave;

            isCompleted[shortestJobIndex] = true;
            completedProcesses++;
        }
        else
            currentTime++;
    }
    showResults("SJF: ", procs);
}

/*
void CPUScheduler::RR()
{
    int quantum = 2, count = process.size(), timePast = 0, i = 0, counter = 0;
    int timeNow =  process.at(0).arrivalTime;
    bool notComplete = true;
    vector<int> elapsed(count, 0);
    queue<int> ready;
    vector<bool> estaNaFila(count, false);

    while (notComplete)
    {   
        // inicilizar a fila 
        for(int x = 0; x<count; x++)
            if((process.at(x).arrivalTime <= timeNow) && (elapsed.at(x) < process.at(x).timeToLeave) && !(estaNaFila.at(x))){ 
                ready.push(x);
                estaNaFila[x] = true;
                cout << x << " " << timeNow << endl;
            }

        if(ready.empty()){
            timeNow++;
            continue;
        }
          
        i = ready.front();

        if ((timeNow >= process.at(i).arrivalTime) && (elapsed.at(i) < process.at(i).timeToLeave))
        {
            counter = 0;
            if (elapsed.at(i) == 0)
                process.at(i).responseTime = timeNow - process.at(i).arrivalTime;

            if(quantum >= (process.at(i).timeToLeave - elapsed.at(i)) && ((process.at(i).timeToLeave - elapsed.at(i)) != 0))
            {
                timePast = timeNow;
                timeNow += process.at(i).timeToLeave - elapsed.at(i);
                elapsed.at(i) += timeNow - timePast;
                process.at(i).returnTime = timeNow - process.at(i).arrivalTime;
            }
            else
            {
                timePast = timeNow;
                timeNow += quantum;
                elapsed.at(i) += quantum;
            }

            for (int j = 0; j < count; j++)
            {
                if ((j != i) && (timeNow > process.at(j).arrivalTime) && (elapsed.at(j) < process.at(j).timeToLeave))
                    process.at(j).waitTime += timeNow - timePast;
            }
        }
    

        
        cout << "proc(" << i <<"): " << " TIME: "<< timeNow << endl;
        cout << "Tempo de resposta p(" << i <<"):" <<  process.at(i).responseTime << endl;
        std::queue<int> copia_fila = ready;
        std::cout << "Elementos da fila:" << std::endl;
        while (!copia_fila.empty()) {
            std::cout << copia_fila.front() << " "; // Acessa e exibe o elemento da frente
            copia_fila.pop(); // Remove o elemento da frente
        }
        std::cout << std::endl << endl;

        notComplete = false;

        for (int j = 0; j < count; j++){
            if(elapsed.at(j) < process.at(j).timeToLeave){
                notComplete = true;
                break;
            }
        }

        counter++;

        if (counter - 1 > count)
            for (int j = 0; j < count; j++)
                if(elapsed.at(j) < process.at(j).timeToLeave){
                    timeNow = process.at(j).arrivalTime;
                    timePast = timeNow;
                    break;
                }

        if(elapsed.at(i) < process.at(i).timeToLeave){
            ready.pop(); // remove da cabeca da fila
            ready.push(i); // joga para o final da fila
        }else
            ready.pop();
        
    }

    showResults("RR: ", process);
}*/

void CPUScheduler::RR()
{
    const int quantum = 2;
    vector<Process> procs = this->process;
    int n = procs.size();

    queue<int> readyQueue;
    vector<bool> inQueue(n, false); // Renomeado para maior clareza

    int currentTime = 0;
    int completedProcesses = 0;
    
    // Inicia o tempo no momento de chegada do primeiro processo
    int firstArrivalTime = INT_MAX;
    for(int i = 0; i < n; ++i) {
        if(procs[i].arrivalTime < firstArrivalTime) {
            firstArrivalTime = procs[i].arrivalTime;
        }
    }
    currentTime = firstArrivalTime;

    // Loop principal da simulação
    while (completedProcesses < n)
    {
        // ETAPA 1: Adicionar todos os processos que já chegaram e ainda não estão na fila
        for (int i = 0; i < n; ++i) {
            if (procs[i].remainingTime > 0 && procs[i].arrivalTime <= currentTime && !inQueue[i]) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        // ETAPA 2: Se a fila está vazia, a CPU está ociosa. Avance o tempo.
        if (readyQueue.empty()) {
            int nextArrivalTime = INT_MAX;
            for (int i = 0; i < n; ++i) {
                if (procs[i].remainingTime > 0) { // Procura o próximo processo AINDA NÃO CONCLUÍDO
                    nextArrivalTime = min(nextArrivalTime, procs[i].arrivalTime);
                }
            }
            // Avança o tempo para a chegada do próximo processo relevante
            currentTime = nextArrivalTime;
            continue; // Reinicia o loop para adicionar o novo processo à fila
        }

        // ETAPA 3: Executar o processo da frente da fila
        int currentProcIndex = readyQueue.front();
        readyQueue.pop();
        inQueue[currentProcIndex] = false; // O processo já não está na fila, está a executar


        // Calcular o tempo de resposta na primeira vez
        if (procs[currentProcIndex].responseTime == -1) {
            procs[currentProcIndex].responseTime = currentTime - procs[currentProcIndex].arrivalTime;
        }

        int timeSlice = min(quantum, procs[currentProcIndex].remainingTime);
        
        currentTime += timeSlice;
        procs[currentProcIndex].remainingTime -= timeSlice;

        // ETAPA 4: Verificar se o processo terminou ou volta para a fila
        if (procs[currentProcIndex].remainingTime > 0) {
            // Antes de o devolver à fila, adicionamos primeiro os que chegaram durante a sua execução
            for (int i = 0; i < n; ++i) {
                if (procs[i].remainingTime > 0 && procs[i].arrivalTime <= currentTime && !inQueue[i]) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }
            // Agora sim, o processo atual volta para o fim da fila
            readyQueue.push(currentProcIndex);
            inQueue[currentProcIndex] = true;
        } else {
            // O processo terminou
            procs[currentProcIndex].returnTime = currentTime - procs[currentProcIndex].arrivalTime;
            procs[currentProcIndex].waitTime = procs[currentProcIndex].returnTime - procs[currentProcIndex].timeToLeave;
            completedProcesses++;
        }
    }

    showResults("RR", procs);
}