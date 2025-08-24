#include "cpu-scheduler.hh"

bool sortByArriveTime(Process& a, Process& b)
{
    return a.arrivalTime < b.arrivalTime;
}

string dotToComma(string number)
{
    for(int i=0; i< number.length(); i++)
        if(number[i] == '.')
        { 
            number[i] = ',';
            number.erase(number.begin()+i+2, number.end());
        }
    return number;
}

void CPUScheduler:: flush()
{
    for (std::vector<Process>::size_type i = 0; i < process.size(); i++)
    {
        process.at(i).responseTime =0;
        process.at(i).waitTime = 0;
        process.at(i).returnTime = 0;
    }
}

void CPUScheduler::addProcess(int arrive, int burst)
{
    process.push_back(Process(arrive, burst));
    std::sort(process.begin(), process.end(), sortByArriveTime);

    for (std::vector<Process>::size_type i = 0; i < process.size(); i++){
        process.at(i).id = i;
    }
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

    cout << fixed << setprecision(1) << algorithm << dotToComma(to_string(averageReturnTimeProcess)) << " " << dotToComma(to_string(averageResponseTimeProcess)) << " " << dotToComma(to_string(averageWaitTimeProcess)) << endl;
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

void CPUScheduler::RR()
{
    queue<Process*> processQueue;
    int quantum = 2, count = process.size(), timePast = 0;
    int i = 0;
    vector<int> remainingTime(count, 0);
    int queueJoined = 1;

    processQueue.push(&process.at(0));

    int timeNow =  processQueue.front()->arrivalTime;

    while (!processQueue.empty() || queueJoined < count)
    {
        i = processQueue.front()->id;

        if (remainingTime.at(i) == 0)
            processQueue.front()->responseTime = timeNow - processQueue.front()->arrivalTime;

        if(quantum >= (processQueue.front()->timeToLeave - remainingTime.at(i)) && ((processQueue.front()->timeToLeave - remainingTime.at(i)) != 0))
        {
            timePast = timeNow;
            timeNow += processQueue.front()->timeToLeave - remainingTime.at(i);
            remainingTime.at(i) += timeNow - timePast;
            processQueue.front()->returnTime = timeNow - processQueue.front()->arrivalTime;
        }
        else
        {
            timePast = timeNow;
            timeNow += quantum;
            remainingTime.at(i) += quantum;
        }

        processQueue.pop();

        if(queueJoined <= count)
        {
            for (int j = queueJoined; j < count; j++)
            {
                if (timeNow >= process.at(j).arrivalTime)
                {
                    processQueue.push(&process.at(j));
                    queueJoined++;
                }
            }
        }

        if (process.at(i).timeToLeave > remainingTime.at(i))
            processQueue.push(&process.at(i));

        if (processQueue.empty())
            for (int j = queueJoined; j < count; j++)
            {
                if (timeNow < process.at(j).arrivalTime)
                {
                    timeNow = process.at(j).arrivalTime;
                    j--;
                }

                if (timeNow >= process.at(j).arrivalTime && remainingTime.at(j) == 0)
                {
                    processQueue.push(&process.at(j));
                    queueJoined++;
                }
            }

        i = ++i % queueJoined;
    }

    for(auto& var : process)
        var.waitTime = var.returnTime - var.timeToLeave;

    showResults("RR: ", process);
}