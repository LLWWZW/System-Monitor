#include "processor.h"
#include "linux_parser.h"
#include <iostream>
#include <string>
#include <unistd.h>
// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
    int Total_prev{0}, Idle_prev{0}, NoIdel_prev{0};
    std::vector<std::string> cpu_sort = LinuxParser::CpuUtilization();
    int user_jiffies = std::stoi(cpu_sort[0]);
    int nice_jiffies = std::stoi(cpu_sort[1]);
    int system_jiffies = std::stoi(cpu_sort[2]);
    int idle_jiffies = std::stoi(cpu_sort[3]);
    int iowait_jiffies = std::stoi(cpu_sort[4]);
    int irq_jiffies = std::stoi(cpu_sort[5]);
    int softirq_jiffies = std::stoi(cpu_sort[6]);
    int steal_jiffies = std::stoi(cpu_sort[7]);
    Idle_prev = idle_jiffies + iowait_jiffies;
    NoIdel_prev = user_jiffies + nice_jiffies + system_jiffies + irq_jiffies + softirq_jiffies + steal_jiffies;
    Total_prev = Idle_prev + NoIdel_prev;

    unsigned int microsecond = 1000000;
    usleep(3 * microsecond); // sleeps for 3 second
    int Total{0}, Idle{0}, NoIdel{0};
    cpu_sort = LinuxParser::CpuUtilization();
    user_jiffies = std::stoi(cpu_sort[0]);
    nice_jiffies = std::stoi(cpu_sort[1]);
    system_jiffies = std::stoi(cpu_sort[2]);
    idle_jiffies = std::stoi(cpu_sort[3]);
    iowait_jiffies = std::stoi(cpu_sort[4]);
    irq_jiffies = std::stoi(cpu_sort[5]);
    softirq_jiffies = std::stoi(cpu_sort[6]);
    steal_jiffies = std::stoi(cpu_sort[7]);
    Idle = idle_jiffies + iowait_jiffies;
    NoIdel = user_jiffies + nice_jiffies + system_jiffies + irq_jiffies + softirq_jiffies + steal_jiffies;
    Total = Idle + NoIdel;

    float cpu_usage = ((Total - Total_prev) - (Idle - Idle_prev)) / float(Total - Total_prev);
    return cpu_usage;
}