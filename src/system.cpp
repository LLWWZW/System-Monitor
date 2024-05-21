#include <cstddef>
#include <set>
#include <string>
#include <unistd.h>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
// LW : Done
Processor &System::Cpu()
{
    return cpu_;
}

// TODO: Return a container composed of the system's processes
// LW: Done
vector<Process> &System::Processes()
{
    vector<int> pids = LinuxParser::Pids();
    processes_ = {};
    for (int pid : pids)
    {
        Process p{pid};
        processes_.push_back(p);
    }
    std::sort(processes_.begin(), processes_.end());
    return processes_;
}

// TODO: Return the system's kernel identifier (string)
// LW: Done
std::string System::Kernel()
{
    // return string();
    return LinuxParser::Kernel();
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization()
// LW: Done
{
    return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
// LW : Done
std::string System::OperatingSystem()
{
    return LinuxParser::OperatingSystem();
}

// TODO: Return the number of processes actively running on the system
// LW : Done
int System::RunningProcesses()
{
    return LinuxParser::RunningProcesses();
}

// TODO: Return the total number of processes on the system
// LW : Done
int System::TotalProcesses()
{
    return LinuxParser::TotalProcesses();
}

// TODO: Return the number of seconds since the system started running
// LW : Done
long int System::UpTime()
{
    return LinuxParser::UpTime();
}
