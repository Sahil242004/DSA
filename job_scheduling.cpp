#include <iostream>
#include <vector>
#include <algorithm>

struct Job {
    char id;       // Job ID
    int deadline;  // Deadline of the job
    int profit;    // Profit if the job is completed within the deadline
};

// Comparator to sort jobs in descending order of profit
bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

void jobScheduling() {
    int n;
    std::cout << "Enter the number of jobs: ";
    std::cin >> n;

    std::vector<Job> jobs(n);
    std::cout << "Enter the Job ID, Deadline, and Profit for each job:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "Job " << i + 1 << " (ID, Deadline, Profit): ";
        std::cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }

    // Sort jobs by profit in descending order
    std::sort(jobs.begin(), jobs.end(), compare);

    // Find the maximum deadline
    int maxDeadline = 0;
    for (auto &job : jobs) {
        maxDeadline = std::max(maxDeadline, job.deadline);
    }

    // Initialize the schedule array to store job IDs
    std::vector<int> schedule(maxDeadline, -1);
    int totalProfit = 0;

    // Greedily schedule jobs
    for (auto &job : jobs) {
        for (int j = job.deadline - 1; j >= 0; j--) {
            if (schedule[j] == -1) {
                schedule[j] = job.id;
                totalProfit += job.profit;
                break;
            }
        }
    }

    // Display the result
    std::cout << "\nSelected jobs: ";
    for (int i = 0; i < maxDeadline; i++) {
        if (schedule[i] != -1) {
            std::cout << char(schedule[i]) << " ";
        }
    }
    std::cout << "\nTotal profit: " << totalProfit << "\n";
}

int main() {
    jobScheduling();
    return 0;
}
