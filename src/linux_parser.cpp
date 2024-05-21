#include <dirent.h>
#include <string>
#include <unistd.h>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem()
{
    string line;
    string key;
    string value;
    std::ifstream filestream(kOSPath);
    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::replace(line.begin(), line.end(), ' ', '_');
            std::replace(line.begin(), line.end(), '=', ' ');
            std::replace(line.begin(), line.end(), '"', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value)
            {
                if (key == "PRETTY_NAME")
                {
                    std::replace(value.begin(), value.end(), '_', ' ');
                    return value;
                }
            }
        }
    }
    return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel()
{
    string os, version, kernel;
    string line;
    std::ifstream stream(kProcDirectory + kVersionFilename);
    if (stream.is_open())
    {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os >> version >> kernel;
    }
    return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids()
{
    vector<int> pids;
    DIR *directory = opendir(kProcDirectory.c_str());
    struct dirent *file;
    while ((file = readdir(directory)) != nullptr)
    {
        // Is this a directory?
        if (file->d_type == DT_DIR)
        {
            // Is every character of the name a digit?
            string filename(file->d_name);
            if (std::all_of(filename.begin(), filename.end(), isdigit))
            {
                int pid = stoi(filename);
                pids.push_back(pid);
            }
        }
    }
    closedir(directory);
    return pids;
}

// TODO: Read and return the system memory utilization
// LW: Done
float LinuxParser::MemoryUtilization()
{
    std::string line;
    float memtotal = -1;
    float memfree = -1;
    std::string name;
    float size;
    std::string unit;
    std::ifstream filestream(kProcDirectory + kMeminfoFilename);
    if (filestream.is_open())
    {

        while (std::getline(filestream, line))
        {
            std::istringstream stringstream(line);
            stringstream >> name >> size >> unit;
            if (name == "MemTotal:")
            {
                memtotal = size;
            }
            if (name == "MemFree:")
            {
                memfree = size;
            }
            if (memtotal != -1 && memfree != -1)
            {
                return (memtotal - memfree) / memtotal;
            }
        }
    }
    // return (memtotal - memfree) / memtotal;
}

// TODO: Read and return the system uptime
// LW: Done
long LinuxParser::UpTime()
{
    std::string line;
    long uptime;
    std::ifstream filestream(kProcDirectory + kUptimeFilename);
    if (filestream.is_open())
    {
        std::getline(filestream, line);
        std::istringstream stringstream(line);
        stringstream >> uptime;
        return uptime;
    }
}
// long LinuxParser::UpTime()
// {
//     string line;
//     string key;
//     int value;
//     std::ifstream filestream(kProcDirectory + kUptimeFilename);
//     if (filestream.is_open())
//     {
//         while (std::getline(filestream, line))
//         {
//             std::istringstream linestream(line);
//             while (linestream >> value)
//             {
//                 return value;
//             }
//         }
//     }
//     return value;
// }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies()
{
    return 0;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]])
{
    return 0;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies()
{
    return 0;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies()
{
    return 0;
}

// TODO: Read and return CPU utilization
// LW: Done
vector<string> LinuxParser::CpuUtilization()
{
    string line;
    string key;
    vector<string> value;
    string value1, value2, value3, value4, value5, value6, value7, value8, value9, value10;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            while (linestream >> key >> value1 >> value2 >> value3 >> value4 >> value5 >> value6 >> value7 >> value8 >>
                   value9 >> value10)
            {
                if (key == "cpu")
                {
                    for (int i = 0; i < 10; i++)
                    {
                        value.push_back(value1);
                    }
                    value.push_back(value1);
                    value.push_back(value2);
                    value.push_back(value3);
                    value.push_back(value4);
                    value.push_back(value5);
                    value.push_back(value6);
                    value.push_back(value7);
                    value.push_back(value8);
                    value.push_back(value9);
                    value.push_back(value10);
                    break;
                }
            }
        }
    }
    return value;
}

// TODO: Read and return the total number of processes
// LW: Done
int LinuxParser::TotalProcesses()
{
    std::string line;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    std::string name;
    int number;
    if (filestream.is_open())
    {

        while (std::getline(filestream, line))
        {
            std::istringstream stringstream(line);
            stringstream >> name >> number;
            if (name == "processes")
            {
                return number;
            }
        }
    }
}

// TODO: Read and return the number of running processes
// LW: Done
int LinuxParser::RunningProcesses()
{
    std::string line;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    std::string name;
    int number;
    if (filestream.is_open())
    {

        while (std::getline(filestream, line))
        {
            std::istringstream stringstream(line);
            stringstream >> name >> number;
            if (name == "procs_running")
            {
                return number;
            }
        }
    }
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid)
{
    // return string();
    std::string line;
    std::string command;
    std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::istringstream stringstream(line);
            stringstream >> command;

            return command;
        }
    }
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
// LW: Done
string LinuxParser::Ram(int pid)
{
    // return string();
    std::string line;
    std::string name;
    float value;
    std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::istringstream stringstream(line);
            stringstream >> name >> value;
            if (name == "VmSize:")
            {
                return std::to_string(int(0.001 * value));
            }
        }
    }
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid)
{
    std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
    std::string line;
    std::string name, num;

    if (filestream.is_open())
    {

        while (std::getline(filestream, line))
        {
            std::istringstream stringstream(line);
            stringstream >> name >> num;
            if (name == "Uid:")
            {
                return num;
            }
        }
    }
    // return string();
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// LW : Done
string LinuxParser::User(int pid)
{
    std::string line;
    std::ifstream filestream(kPasswordPath);
    std::string user_name, value, pd;

    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream stringstream(line);
            stringstream >> user_name >> value >> pd;
            if (pd == Uid(pid))
            {
                return user_name;
            }
        }
    }
    // return string();
}
// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid)
{
    string line;
    string key;
    long value;
    vector<string> temp;
    std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);

    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            while (linestream >> key)
            {
                temp.push_back(key);
            }
        }
    }
    value = std::stol(temp[21]) / sysconf(_SC_CLK_TCK);
    return value;
}

// LW : TO DO
// Done
std::vector<std::string> LinuxParser::CpuUtilization(int pid)
{
    std::string line;
    std::string key;
    std::vector<std::string> res;
    int i = 0;
    std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::istringstream stringstream(line);
            while (stringstream >> key)
            {
                if ((i == 13) || (i == 14) || (i == 15) || (i == 16) || (i == 21))
                {
                    res.push_back(key);
                }
                i++;
            }
        }
    }
    return res;
}

/*-------------------------------------------------------------------------------------------------------------------------*/