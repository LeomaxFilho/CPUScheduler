#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include <climits>
#include <queue>

using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int timeToLeave;
    int waitTime = 0;
    int returnTime;
    int responseTime;

    Process(int ArrivalTime, int TimeToLeave);
};
