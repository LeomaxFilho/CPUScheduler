#include <fstream>
#include "cpu-scheduler.hh"

int main(int argc, char const *argv[])
{
    ifstream readFile("inputs/procs_2.txt");
    CPUScheduler scheduler;
    int arrivalTime, burst;

    if(!readFile.is_open()){
        cout << "Error\n\n";
        return 0;
    }

    while(!readFile.eof()){
        readFile >> arrivalTime >> burst;
        scheduler.addProcess(arrivalTime, burst);        
    }   

    scheduler.SJF();

    readFile.close(); 
    return 0;
}
