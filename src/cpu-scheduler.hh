#include "process.hh"

using namespace std;

class CPUScheduler {
private:
    vector<Process> process;
    
public:
    void addProcess(int arrive, int burst);
    void showResults(const string algoritmo, const vector<Process> procs);
    void FCFS ();
    void SJF();
};
