/*
*














If run without arguments, the program should print to the console the following information, in order (one item per line):

    The model name of the CPU
    The number of cores
    The version of Linux running in the environment
    The total memory available to the system, in kilobytes
    The 'uptime' (the amount of time the system has been running, expressed in terms of days, hours, minutes and seconds).

*If run with a numerical argument, the program should print to the console information about the corresponding process:

    The name of the process
    The console command that started the process (if any)
    The number of threads running in the process
    The total number of context switches that have occurred during the running of the process.

*/

#include <stdio.h>
#include <string.h>

void print_computer_info() {


    printf("\nCPU MODEL NAME ");
    printf("\nNumber of Cores\n");
    printf("\nLocal Linux version\n");
    printf("\nTotal Memory Available\n");
    printf("\nSystem Run Time\n");

}

void print_process(char* process) {
    //name of the process
    printf("%s", process);
    //console command that started process if applicable
    //number of threads running in the process
    //total number of context switches that have occured during the process running
}

int main(int argc, char *argv[]) {
    if(argv[1] == NULL) {
        print_computer_info();
    }


    FILE *proc_ptr = fopen("/proc/cpuinfo", "r");
    /*
    int count = 100;
    char buffer[100];
    int getc(proc_ptr,count,buffer);
    */
    
   char c;
    while((c = getc(proc_ptr)) != EOF) {
        printf("%c",c);
    }



    

}
