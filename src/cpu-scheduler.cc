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

void CPUScheduler::RR()
{
    int quantum = 2, count = process.size(), timePast = 0, i = 0, counter = 0;
    int timeNow =  process.at(0).arrivalTime;
    bool notComplete = true;
    vector<int> elapsed(count, 0);

    while (notComplete)
    {
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

        for (int j = 0; j < count; j++)
        {
            cout << "TIME: " << timeNow << "\n";
            cout << "response(" << j <<"): " << process.at(j).responseTime << "\n";
        }
        cout << "\n\n";

        i = (i + 1) % count;
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
    }

    showResults("RR: ", process);
}