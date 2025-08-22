#include "cpu-scheduler.hh"

void CPUScheduler::addProcess(int arrive, int burst) {
    process.push_back(Process(process.size(), arrive, burst));
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
