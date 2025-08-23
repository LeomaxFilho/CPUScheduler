#include "cpu-scheduler.hh"

bool sortByArriveTime(Process& a, Process& b){
    return a.arrivalTime < b.arrivalTime;
}

void CPUScheduler::addProcess(int arrive, int burst) {
    process.push_back(Process(process.size(), arrive, burst));
    std::sort(process.begin(), process.end(), sortByArriveTime);
}

void CPUScheduler::showResults(const string algorithm, const vector<Process> procs) {
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
}

void CPUScheduler::FCFS (){

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

void CPUScheduler::SJF(){
   
    // Copia do vetor de processos para nao realizar nenhuma operacao com ele
    vector<Process> procs = this->process;

    int currentTime = 0; 

    int n = procs.size();
    if(n==0) return;

    int completedProcesses = 0;
    vector<bool> isCompleted(n, false);

    while(completedProcesses < n){
        int shortestJobIndex = -1;
        int minBurstTime = INT_MAX;
        
        // Encontra dentro dos processos aquele como menor tempo de execucao
        for(int i=0; i<n; i++){
            if(procs[i].arrivalTime <= currentTime && !isCompleted[i]){
                if(procs[i].timeToLeave < minBurstTime){
                    minBurstTime = procs[i].timeToLeave;
                    shortestJobIndex = i;
                }
            }
        }

        if (shortestJobIndex != -1){
            
            // Calcula o tempo de resposta do processo
            procs[shortestJobIndex].responseTime = currentTime - procs[shortestJobIndex].arrivalTime;

            // Adiciona ao tempo atual da CPU o tempo de execucao do processo
            currentTime += procs[shortestJobIndex].timeToLeave;

            // Calcula o tempo de retorno
            procs[shortestJobIndex].returnTime = currentTime - procs[shortestJobIndex].   arrivalTime;

            // Tempo de espera
            procs[shortestJobIndex].waitTime = procs[shortestJobIndex].returnTime - procs[shortestJobIndex].timeToLeave;

            isCompleted[shortestJobIndex] = true;
            completedProcesses++;
        }
        else{
            currentTime++;
        }
    }
     showResults("SJF: ", procs);
}
