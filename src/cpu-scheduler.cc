#include "cpu-scheduler.hh"

bool CPUScheduler::sortByArriveTime(Process& a, Process& b){
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

    cout << fixed << setprecision(1) << algorithm << averageReturnTimeProcess << " " << averageResponseTimeProcess << " " << averageWaitTimeProcess;
}

void CPUScheduler::FCFS (){

    int count = process.size();

    process.at(0).waitTime = 0;
    process.at(0).responseTime = 0;
    process.at(0).returnTime = process.at(0).timeToLeave;

    for (int i = 1; i < count; i++)
    {
        process.at(i).waitTime = process.at(i - 1).returnTime;
        process.at(i).responseTime = process.at(i - 1).returnTime;
        process.at(i).waitTime = process.at(i - 1).returnTime + process.at(i).timeToLeave;
    }
    
    showResults("FCFS", process);
}
