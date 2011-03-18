#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <vector>
#include <string>


//class to log all program acitivity

class Log
{
    //data
    private:
        std::vector<std::string> logstr;
        //mode vars
        bool echo_msg; //'true' = show messages in console
        bool echo_err; //'true' = show errors in console
        //text-vars
        std::string name; //string to be put before every output symbol (which is before entry)
        std::string file_ending; //standard file ending
        std::string file_name; //standard file name
        std::string seperator; //string to seperate log entries in log-file
        std::string output_symbol; //string to be put before every log entry printed in the console
        std::string error_symbol; //string to be put before every error entry
        //messages
        std::string msg_log_info; //information about "SimpleLog" at construction of object
        std::string msg_begin_log; //information about starting to log
        //remote Log -- another object of class 'Log' which should log everything this log does
        Log* remote;

    //methods declaration
    public:
        //constructors
        Log(); //create empty log
        Log(const char path[]); //create log with 'logstr' from file 'path'

        void init(); //set standard values for messages / echo
        void reset_messages(); //sets message vars to standard messages
        void reset_configuration(); //sets configuration to default values
        void log_info(); //logs information about Log at beginning

        //methods
        bool load(const char path[]); //loads a saved log from file 'filename' -- return value: true=ok | errors: false=file not found or could not be opened
        bool load(); //calls 'load(const char path[])' with 'std_file_name' and 'std_file_ending'
        bool save(const char path[]); //saves 'logstr' to file 'path' or overwrites it (!) -- return value: true=ok | errors: false=file could not be opened
        bool save(); //calls 'save(const char path[])' with 'std_file_name' and 'std_file_ending'
        void add(std::string s); //add normal entry
        void err(std::string s); //add error entry

        //mode switches
        void echo_on();
        void echo_off();
        void echo_msg_on();
        void echo_msg_off();
        void echo_err_on();
        void echo_err_off();

        //set messages vars
        void set_name(std::string name);
        void set_file_ending(std::string file_ending);
        void set_file_name(std::string file_name);
        void set_seperator(std::string seperator);
        void set_output_symbol(std::string output_symbol);
        void set_error_symbol(std::string error_symbol);
        void set_msg_begin_log(std::string msg_begin_log);

        //set remote log (0 = no remote)
        void set_remote(Log* remote_log); //sets 'remote' to 'remote_log' (if 'remote_log' != 'this')

        //print methods
        void print(unsigned int entry); //displays 'logstr[entry]'
        void print(unsigned int start, unsigned int end); //displays 'logstr[start]' to 'logstr[end]' -- if end<start logstr[start] to logstr[entries] will be displayes
        void print(); //displays whole content of 'logstr'

    private:
        void send_console(); //sends last entry to standard output -- used to print new log entry
};


#endif // LOG_H_INCLUDED
