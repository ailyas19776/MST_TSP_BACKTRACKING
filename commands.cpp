#include "impl.h"
using namespace std;
void drone::getMode(int argc, char* argv[]) {
    bool modeSpecified = false;
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    option long_options[] = {
        {"mode", required_argument, nullptr, 'm'},// nullptr refers to getopt feature
        {"help", no_argument,       nullptr, 'h'},
        { nullptr, 0,             nullptr, '\0' }
    };

    while ((choice = getopt_long(argc, argv, "m:h", long_options, &option_index)) != -1) { // colon means required argument
        switch (choice) {
        case 'h':
            cout << " HELP COMMAND USED! " << "\n";
            exit(0);
        case 'm':
            mode = optarg;
            if (mode != "MST" && mode != "OPTTSP" && mode != "FASTTSP") {
                cerr << "Error: invalid mode" << endl;
                cerr << "  I don't know recognize: " << mode << endl;
                exit(1);
            } // if
            modeSpecified = true;
            break;

        default:
            cerr << "Error: invalid option" << endl;
            exit(1);
        } // switch
    } // while

    if (!modeSpecified) {
        cerr << "Error: no mode specified" << endl;
        exit(1);
    } // if

}
