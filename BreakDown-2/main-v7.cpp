#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct UAV
{
    int id;
    double capacity;
    double energyPerKm;
    double totalEnergy;
};

struct Outpost
{
    int id;
    int medicine, food, weapons;
    double x, y;
    int priority;
};

double calculateDistance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

struct Allocation
{
    int uavId;
    int outpostId;
    double energyCost;
};

bool compareByPriority(const Outpost &a, const Outpost &b)
{
    return a.priority > b.priority; // Sort in descending order of priority
}

vector<Allocation> allocateUAVs(vector<UAV> &uavs, vector<Outpost> &outposts, double baseX, double baseY)
{
    vector<Allocation> allocations;
    sort(outposts.begin(), outposts.end(), compareByPriority); // Sort outposts by priority

    vector<bool> assignedOutposts(outposts.size(), false);
    vector<bool> assignedUAVs(uavs.size(), false);

    for (size_t i = 0; i < outposts.size(); i++)
    {
        for (size_t j = 0; j < uavs.size(); j++)
        {
            if (!assignedUAVs[j] && !assignedOutposts[i])
            {
                double distance = calculateDistance(baseX, baseY, outposts[i].x, outposts[i].y);
                double energyCost = distance * uavs[j].energyPerKm;

                if (energyCost <= uavs[j].totalEnergy)
                { // Check if UAV has enough energy
                    allocations.push_back({uavs[j].id, outposts[i].id, energyCost});
                    assignedUAVs[j] = true;
                    assignedOutposts[i] = true;
                    break; // Assign one UAV per outpost
                }
            }
        }
    }
    return allocations;
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
        cin >> uavs[i].id >> uavs[i].capacity >> uavs[i].energyPerKm >> uavs[i].totalEnergy;
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

    vector<Allocation> allocations = allocateUAVs(uavs, outposts, baseX, baseY);

    cout << "\nBest UAV Allocation:\n";
    for (const auto &allocation : allocations)
    {
        cout << "UAV " << allocation.uavId << " assigned to Outpost " << allocation.outpostId
             << " with Energy Cost: " << allocation.energyCost << endl;
    }

    return 0;
}
