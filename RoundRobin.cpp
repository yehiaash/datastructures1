#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

class process {
public:
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;

    process(int pid, int arrival, int burst) {
        id = pid;
        arrival_time = arrival;
        burst_time = burst;
        remaining_time = burst;
        completion_time = 0;
        turnaround_time = 0;
        waiting_time = 0;
    }
};

void printQueue(queue<int> q, vector<process>& procs) {
    if (q.empty()) { 
        cout << "[ Empty ]\n"; 
        return; 
    }
    cout << "[ ";
    while (!q.empty()) {
        cout << "P" << procs[q.front()].id;
        q.pop();
        if (!q.empty()) cout << ", ";
    }
    cout << " ]\n";
}


int main() {
    int Quantum, n ;
    cin >> Quantum >> n;

    vector <process> all_processes;
    for (int i = 0; i < n; i++) {
        int arrival, burst;
        cin >> arrival >> burst;

        all_processes.push_back(process(i + 1, arrival, burst));
    }

    sort(all_processes.begin(), all_processes.end(), [](process a, process b) {
        return a.arrival_time < b.arrival_time;
        });
    queue <int> q;
    int next = 0;
    int current_time = 0; 

    while (next < n && all_processes[next].arrival_time <= current_time) {
        q.push(next++);
    }

    printQueue(q, all_processes);

    while (!q.empty() || next < n) {

        if (q.empty() && next < n) {
            current_time = all_processes[next].arrival_time; 
            while (next < n && all_processes[next].arrival_time <= current_time) {
                q.push(next);
                next++;
            }
            printQueue(q, all_processes);
        }
        

        if (!q.empty()) {
            int indx = q.front();
            q.pop();

            int exec = min(Quantum, all_processes[indx].remaining_time);
            all_processes[indx].remaining_time -= exec;
            current_time += exec;

            while (next < n && all_processes[next].arrival_time <= current_time) {
                q.push(next);
                next++;
            }

            if (all_processes[indx].remaining_time > 0) {
                q.push(indx);
            }
            else {
                all_processes[indx].completion_time = current_time;
            }
            printQueue(q, all_processes);

        }      
    }
    int total_waiting_time = 0;
    cout << "\nProcess\tcompletion time\tturnaround time\twaiting time\n";
    for (int i = 0; i < n; i++) {
        all_processes[i].turnaround_time = all_processes[i].completion_time - all_processes[i].arrival_time;
        all_processes[i].waiting_time = all_processes[i].turnaround_time - all_processes[i].burst_time;
        total_waiting_time += all_processes[i].waiting_time;
        cout << "P" << all_processes[i].id << "\t"
            << all_processes[i].completion_time << "\t\t"
            << all_processes[i].turnaround_time << "\t"
            << all_processes[i].waiting_time << endl;  
    }
    cout << "\nAverage Waiting Time: " << (double)total_waiting_time / n;
     
    return 0;
}