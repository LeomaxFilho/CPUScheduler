#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int timeToLeave;
    int waitTime;
    int returnTime;
    int responseTime;

    Process(int Id, int ArrivalTime, int TimeToLeave);
};
