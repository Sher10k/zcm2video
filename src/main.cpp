//=======================================================================================

// zcm2video modules
#include "parser.cpp"

// utils
#include "utils/argparser.hpp"

// UNIX & Linux
#include <sys/types.h>
#include <unistd.h>

// STD
#include <string>
#include <iostream>
#include <getopt.h>

using namespace std;

//=======================================================================================

void help()
{
    std::cout << "Usage: ./zcm2video [options] \n"
              << "\n"
              << "    Convert zcm log file to video file \n"
              << "    and get list zcm event parametrs \n"
              << "\n"
              << "Example: \n"
              << "    ./zcm2video -i zcm.log -o <video_name> -f <fps> -c <channel_name> -idx <id_camera> -p <file.pid> \n"
              << "\n"
              << "And view list parametrs: \n"
              << "    ./zcm2video -i zcm.log -l \n"
              << "\n"
            << "Options: \n"
            << "\n"
            << "  -h    Shows this help text and exits \n"
            << "  -i    Input log to convert \n"
            << "  -o    Output name video file \n"
            << "  -f    FPS, default = 5 \n"
            << "  -c    Channel name \n"
            << "  -idx  Camera index, if (idx == -1) then save videos from all cameras \n"
            << "  -p    PID file \n"
            << "  -l    Output list channels \n"
            << "\n\n";
}

//=======================================================================================

int main( int argc, const char** argv )
{
    // --- Parse arguments
    auto arguments = Argparser::parse(
                argc, argv,
                {
                    { "-v",   Argparser::Sufficient },
                    { "-h",   Argparser::Sufficient },
                    { "-i",   Argparser::NotSufficient },
                    { "-o",   Argparser::NotSufficient },
                    { "-f",   Argparser::NotSufficient },
                    { "-c",   Argparser::NotSufficient },
                    { "-idx", Argparser::NotSufficient },
                    { "-p",   Argparser::NotSufficient },
                    { "-l",   Argparser::Sufficient }
                } );
    
    try {
        arguments.at("-v");
        cout << "Version: " << "v0.2.0" << "\n";
        return 0;
    }
    catch ( const out_of_range& ) {
    }
    
    try {
        arguments.at("-h");
        help();
        return 0;
    }
    catch ( const out_of_range& ) {
    }
    
    bool list {false};
    try {
        arguments.at("-l");
        list = true;
    }
    catch ( const out_of_range& ) {
    }
    
    string infile   {""};
    string outfile  {""};
    string channel {""};
    int id_camera  {-1};
    double fps     {5};
    if (list)
    {
        try {
            infile = arguments.at("-i");
        }
        catch ( const out_of_range& ) {
            std::cerr << "Example: \n" 
                      << "View list parametrs: \n"
                      << "    ./zcm2video -i zcm.log -l \n";
        }
    }
    else
    {
        try {
            infile = arguments.at("-i");
            outfile = arguments.at("-o");
            channel = arguments.at("-c");
            id_camera = atoi( arguments.at("-idx").data() );
            fps = atof( arguments.at("-f").data() );
            
            cout << "Input file:  " << infile << "\n"
                 << "Output file: " << outfile << "\n"
                 << "Channel:     " << channel << "\n"
                 << "Camera:      " << ((id_camera != -1) ? to_string(id_camera) : "all") << "\n"
                 << "FPS:         " << fps << "\n"
                 << "\n";
        }
        catch ( const out_of_range& ) {
            std::cerr << "Example: \n"
                      << "    ./zcm2video -i zcm.log -o <video_name> -f <fps> -c <channel_name> -idx <id_camera> -p <file.pid> \n"
                      << "\n" 
                      << "And view list parametrs: \n" 
                      << "    ./zcm2video -i zcm.log -l \n";
            return 22;
        }
    }
    
    // --- Create pid file
    cout << "Current PID: " << getpid() << "\n";
    if ( !arguments["-p"].empty() )
    {
        cout << "Pid path: " << arguments["-p"] << "\n";
        ofstream out( arguments["-p"] );
        out << getpid();
        out.close();
    }
    
    // --- Start parsing
    VideoParser parser( infile, outfile, channel,id_camera, fps, list );
    parser.Run();
    
    return 0;
}

//=======================================================================================
