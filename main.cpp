#include <string>
#include <iostream>
#include <getopt.h>

#include "videoParser.cpp"

struct Args
{
    std::string inlog       = "";
    std::string outlog      = "";
    std::string param       = "";
    bool list               = false;
    bool debug              = false;

    bool parse( int argc, char *argv[] )
    {
        // set some defaults
        const char *optstring = "i:o:p:ldh";
        struct option long_opts[] = {
                { "input",       required_argument, 0, 'i' },
                { "output",      required_argument, 0, 'o' },
                { "param",       required_argument, 0, 'p' },
                { "list",        no_argument,       0, 'l' },
                { "debug",       no_argument,       0, 'd' },
                { "help",        no_argument,       0, 'h' },
                { 0,             0,                 0,  0  }
        };

        int c;
        while ( ( c = getopt_long ( argc, argv, optstring, long_opts, 0 ) ) >= 0 ) {
            switch (c) {
                case 'i': inlog       = std::string(optarg);    break;
                case 'o': outlog      = std::string(optarg);    break;
                case 'p': param       = std::string(optarg);    break;
                case 'l': list        = true;                   break;
                case 'd': debug       = true;                   break;
                case 'h': default: usage(); return false;
            };
        }

        if ( inlog == "" ) {
            std::cerr << "Please specify logfile input" << std::endl;
            return false;
        
        }
        if ( ( outlog  == "" ) && ( !list ) ) {
            std::cerr << "Please specify video file output" << std::endl;
            return false;
        }
        if ( ( param  == "" ) && ( !list ) ) {
            std::cerr << "Please specify parameters" << std::endl;
            return false;
        }
        
        return true;
    }

    void usage()
    {
        std::cout << "Usage: ./zcm2video [options]" << std::endl
                  << "" << std::endl
                  << "    Convert zcm log file to video file" << std::endl
                  << "    and get list zcm event parametrs" << std::endl
                  << "" << std::endl
                  << "Example:" << std::endl
                  << "    ./zcm2video -i zcm.log -o vid.avi -p <name_param>" << std::endl
                  << "" << std::endl
                  << "And view list parametrs: " << std::endl
                  << "    ./zcm2video -i zcm.log -l " << std::endl
                  << "" << std::endl
                << "Options:" << std::endl
                << "" << std::endl
                << "  -h, --help                 Shows this help text and exits" << std::endl
                << "  -i, --input = logfile      Input log to convert" << std::endl
                << "  -o, --output = videofile   Output video file" << std::endl
                << "  -p, --param = parameters   Input parameters" << std::endl
                << "  -l, --list = list          Output list parametrs" << std::endl
                << "  -d, --debug                Run a dry run to ensure proper converter setup" << std::endl
                << std::endl << std::endl;
    }
};

int main(int argc, char *argv[])
{
    Args args;
    if (!args.parse(argc, argv)) return 1;
    if (args.debug) return 0;
    
    
    VideoParser parser( args.inlog, args.outlog, args.param, args.list );
    parser.Run();
    
    return 0;
}
