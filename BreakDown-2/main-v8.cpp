#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>
#include <queue>
#include <tuple>

using namespace std;

struct UAV
{
    int id;
    double weightCapacity;
    double energyPerKm;
    double totalEnergy;
    double availableTime; // Time when UAV is available again
};

struct Outpost
{
    int id;
    int medicine, food, weapons;
    double x, y;
    int priority;
};

struct Task
{
    double time;
    int uavIndex;
    bool operator>(const Task &other) const
    {
        return time > other.time; // Min-heap based on time
    }
};

double calculateDistance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main()
{
    int numOutposts, numUAVs;
    cout << "Enter number of outposts: ";
    cin >> numOutposts;
    cout << "Enter number of UAVs: ";
    cin >> numUAVs;

    vector<UAV> uavs(numUAVs);
    cout << "Enter UAV details (ID, weight capacity, energy/km, total energy):\n";
    for (int i = 0; i < numUAVs; i++)
    {
        cin >> uavs[i].id >> uavs[i].weightCapacity >> uavs[i].energyPerKm >> uavs[i].totalEnergy;
        uavs[i].availableTime = 0; // Initially all UAVs are available
    }

    double baseX, baseY;
    cout << "Enter Base Station coordinates (x y): ";
    cin >> baseX >> baseY;

    vector<Outpost> outposts(numOutposts);
    cout << "Enter Outpost details (ID, medicine, food, weapons, x, y, priority level 1-5):\n";
    for (int i = 0; i < numOutposts; i++)
    {
        cin >> outposts[i].id >> outposts[i].medicine >> outposts[i].food >> outposts[i].weapons >> outposts[i].x >> outposts[i].y >> outposts[i].priority;
    }

    // Sort outposts by priority (descending)
    sort(outposts.begin(), outposts.end(), [](const Outpost &a, const Outpost &b)
         { return a.priority > b.priority; });

    // Min-heap to track UAV availability based on earliest available time
    priority_queue<Task, vector<Task>, greater<Task>> pq;
    for (int i = 0; i < numUAVs; i++)
    {
        pq.push({0, i}); // All UAVs start at time 0
    }

    cout << "\nBest UAV Allocation:\n";
    vector<bool> outpostAssigned(numOutposts, false);

    for (const auto &outpost : outposts)
    {
        bool assigned = false;
        double minEnergyCost = 1e9;
        int selectedUAV = -1;
        double selectedEnergyUsed = 0;
        double selectedTravelTime = 0;
        double distance = calculateDistance(baseX, baseY, outpost.x, outpost.y);

        vector<Task> tempUAVs; // Store popped elements to push them back later

        while (!pq.empty())
        {
            auto [availableTime, uavIndex] = pq.top();
            pq.pop();
            UAV &uav = uavs[uavIndex];

            double energyCost = distance * uav.energyPerKm * 2; // Round trip
            double travelTime = distance / 10.0;                // Assume 10 units speed

            if (energyCost <= uav.totalEnergy)
            {
                assigned = true;
                selectedUAV = uavIndex;
                selectedEnergyUsed = energyCost;
                selectedTravelTime = travelTime;

                // Update UAV availability
                uav.availableTime = availableTime + (2 * travelTime);
                pq.push({uav.availableTime, uavIndex});
                break;
            }
            else
            {
                tempUAVs.push_back({availableTime, uavIndex});
            }
        }

        // Push back UAVs that were not selected
        for (auto &task : tempUAVs)
        {
            pq.push(task);
        }

        if (assigned)
        {
            cout << "UAV " << uavs[selectedUAV].id << " assigned to Outpost " << outpost.id
                 << " | Distance: " << distance << " | Energy Cost: " << selectedEnergyUsed
                 << " | Travel Time: " << selectedTravelTime << " | Available Again At: " << uavs[selectedUAV].availableTime << endl;
            outpostAssigned[outpost.id - 1] = true;
        }
        else
        {
            cout << "⚠️ Warning: Outpost " << outpost.id << " could not be reached due to UAV constraints.\n";
        }
    }

    return 0;
}
