#include "process.h"
#include "linux_parser.h"
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <unistd.h>

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
// LW: Done
int Process::Pid()
{
    return this->pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
    // return 0;
    // std::vector<std::string> stat = LinuxParser::CpuUtilization(this->pid_);
    // int total_time = stoi(stat[13]) + stoi(stat[14]) + stoi(stat[15]) + stoi(stat[16]);
    // float seconds = LinuxParser::UpTime() - stoi(stat[21]) / float(sysconf(_SC_CLK_TCK));
    // float cpu_usage = 100 * ((total_time / sysconf(_SC_CLK_TCK)) / seconds);
    // return cpu_usage;
    long t = LinuxParser::UpTime();
    vector<string> s = LinuxParser::CpuUtilization(pid_);
    int total_time = std::stoi(s[0]) + std::stoi(s[1]);
    long sec = t - (std::stoi(s[4]) / sysconf(_SC_CLK_TCK));
    float cpu_usage = (((total_time * 1.0) / sysconf(_SC_CLK_TCK)) / sec);
    return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command()
{
    return LinuxParser::Command(this->pid_);
}

// TODO: Return this process's memory utilization
// LW: Done
string Process::Ram()
{
    return LinuxParser::Ram(this->pid_);
}

// TODO: Return the user (name) that generated this process
// LW: Done
string Process::User()
{
    return LinuxParser::User(this->pid_);
    // return string();
}

// TODO: Return the age of this process (in seconds)
// LW : Done
long int Process::UpTime()
{
    return LinuxParser::UpTime(this->pid_);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &a) const
{
    return cpu_time_ > a.cpu_time_;
}