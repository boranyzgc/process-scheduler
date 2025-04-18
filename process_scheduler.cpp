#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

struct Process {
    string name;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime = 0;
    int turnaroundTime = 0;
    int finishTime = 0;
};


void calculateFCFS(vector<Process>& processes) {
    int currentTime = 0;
    for (auto& p : processes) {
        if (currentTime < p.arrivalTime)
            currentTime = p.arrivalTime;

        p.waitingTime = currentTime - p.arrivalTime;
        currentTime += p.burstTime;
        p.turnaroundTime = p.waitingTime + p.burstTime;
    }
}


void calculateRR(vector<Process>& processes, int quantum) {
    int currentTime = 0;
    queue<int> q;
    int n = processes.size();
    vector<bool> visited(n, false);
    int completed = 0;

    // ilk gelen prosesleri sıraya ekle
    for (int i = 0; i < n; ++i) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int idx = q.front();
        q.pop();

        Process& p = processes[idx];

        if (currentTime < p.arrivalTime)
            currentTime = p.arrivalTime;

        int execTime = min(quantum, p.remainingTime);
        p.remainingTime -= execTime;
        currentTime += execTime;

        // yeni gelen prosesleri sıraya ekle
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && processes[i].arrivalTime <= currentTime) {
                q.push(i);
                visited[i] = true;
            }
        }

        // eğer proses bitmediyse tekrar kuyruğa ekle
        if (p.remainingTime > 0) {
            q.push(idx);
        } else {
            p.finishTime = currentTime;
            p.turnaroundTime = p.finishTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
            completed++;
        }
    }
}

void printResults(const vector<Process>& processes, const string& method) {
    float totalWaiting = 0, totalTurnaround = 0;

    cout << "\n--- " << method << " Scheduling Results ---\n";
    cout << left << setw(10) << "Process" << setw(15) << "Arrival Time"
         << setw(12) << "Burst Time" << setw(14) << "Waiting Time"
         << "Turnaround Time\n";

    for (const auto& p : processes) {
        cout << left << setw(10) << p.name << setw(15) << p.arrivalTime
             << setw(12) << p.burstTime << setw(14) << p.waitingTime
             << p.turnaroundTime << "\n";
        totalWaiting += p.waitingTime;
        totalTurnaround += p.turnaroundTime;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << totalWaiting / processes.size();
    cout << "\nAverage Turnaround Time: " << totalTurnaround / processes.size() << "\n";
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "\nProcess " << i + 1 << " name: ";
        cin >> processes[i].name;
        cout << "Arrival time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst time: ";
        cin >> processes[i].burstTime;
    }

    int choice;
    cout << "\nChoose scheduling algorithm:\n";
    cout << "1. First-Come-First-Served (FCFS)\n";
    cout << "2. Round Robin (RR)\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        calculateFCFS(processes);
        printResults(processes, "FCFS");
    } else if (choice == 2) {
        int quantum;
        cout << "Enter time quantum: ";
        cin >> quantum;
        calculateRR(processes, quantum);
        printResults(processes, "Round Robin");
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
