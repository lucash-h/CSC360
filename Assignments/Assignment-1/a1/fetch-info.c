#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
This function outputs system information using /proc and system() in the following format: 
model name:   Intel(R) Xeon(R) Gold 6254 CPU @ 3.10GHz
cpu cores:    1
Linux version: 5.4.0-204-generic (buildd@lcy02-amd64-079) (gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.2)) #224-Ubuntu SMP Thu Dec 5 13:38:28 UTC 2024
MemTotal:   8136088 kB
Uptime: 32 days, 0 hours, 20 minutes, 36 seconds

PLEASE NOTE:

AI was used to generate the awk section for both the Linux version and the uptime. Its worth noting that I had no trouble retrieving it from the proc directory and I couldve opened it using a file, but I though this solution was cool, so I kept it in.


system("awk '{printf \"Uptime: %d days, %d hours, %d minutes, %d seconds\\n\", "
        "$1/86400, ($1%86400)/3600, ($1%3600)/60, $1%60}' /proc/uptime");

system("cat /proc/version | awk '{printf \"Linux version: \"; for(i=3;i<=NF;i++) printf \"%s \", $i; print \"\"}'");

*/

void print_computer_info() {

    //cpu name
    system("cat /proc/cpuinfo | grep 'model name' | head -n 1 | awk -F: '{print \"model name:   \"$2}'");

    //number of cores
    system("cat /proc/cpuinfo | grep 'cpu cores'| head -n 1 |awk -F: '{print \"cpu cores:   \"$2}'");

    //linux version
    //Prints Linux versions: then Starts at 3rd argument from proc(after Linux Version: and continues until finished)
    system("cat /proc/version | awk '{printf \"Linux version: \"; for(i=3;i<=NF;i++) printf \"%s \", $i; print \"\"}'");


    //memory 
    system("grep MemTotal /proc/meminfo | awk '{print \"MemTotal:   \"$2\" \"$3}'");

    //uptime/length system has been running for
    //takes total time the system has been on(second argument($2) from /proc/uptime and breaks it down into days, hours, minutes and seconds)
    system("awk '{printf \"Uptime: %d days, %d hours, %d minutes, %d seconds\\n\", "
        "$1/86400, ($1%86400)/3600, ($1%3600)/60, $1%60}' /proc/uptime");
}


/*
*************THIS IS CURRENTLY DISGUSTING I SHOULD CHANGE IT************************

Input params: char* pid, pulled from argv in command line

Returns: Nothing

Function: Prints process information
            - name of process
            - Console Command that started the process
            - The number of threads running in the process
            - The total number of context switches that have occured during the running of the process

Format: 
Process number:   1
Name:   systemd
Filename (if any):    /sbin/init
Threads:    1
Total context switches:   30419074

*/

void print_process_info(char* pid) {
  
    printf("Process number:   %s", pid);


    char buffer1[20]; //check for size of pid
    //does 
    snprintf(buffer1, sizeof(buffer1), "cat /proc/%s/comm", pid);

    system(buffer1);

    //cat /proc/[pid]/cmdline -> for console command
    char buffer2[80];
    snprintf(buffer2, sizeof(buffer2), "cat /proc/%s/cmdline", pid);
    system(buffer2);


    //cat /proc/[pid]/status | grep Threads -> for thread num
    char buffer3[40];
    snprintf(buffer3, sizeof(buffer3), "cat /proc/%s/status | grep Threads", pid);
    system(buffer3);

    //cat /proc/[pid]/status for status 
    char buffer4[80];
    snprintf(buffer4, sizeof(buffer4), "cat /proc/%s/status | grep voluntary_ctxt_switches:", pid);
    system(buffer4);


}

/*
Function checks if pid exists by seeing if the directory /proc/<pid> exists
Input: pid as a char*
Output: boolean value, 1 if it exists and 0 if not
*/

int is_pid_alive(char* pid) {

char test[256];
    // Use test command to check if /proc/PID directory exists
    snprintf(test, sizeof(test), "test -d /proc/%s", pid);
    
    //since test returns 0 if true 
    //if test == 0 is_pid_alive returns 1

    return system(test) == 0;
}

/*
Function clears an array in c by replacing non null terminators with null terminators
Input: char *
Output: cleared array (char*)

NOTE: This stops at the null terminator because I know there will be no null terminator other than the final one in this situation
which is honestly not great
*/
char *clear_array(char *array, size_t size) {
    /*
    for(int i = 0; array[i] !='\0'; i++) {
        array[i] = '\0';
    }
    */
    memset(array, '\0', size);
    return array;
}



int main(int argc, char *argv[]) {

    if(argv[1] == NULL) {
        print_computer_info();
        return 0;
    }

    if(!is_pid_alive(argv[1])) {
        printf("Process number %s not found.", argv[1]);
        exit(1);
    }

    char *pid = argv[1];
    printf("Process number:   %s\n", pid);

    char buffer[256]; //check for size of pid
    snprintf(buffer, sizeof(buffer), 
        "printf \"Name:    \" && cat /proc/%s/comm", pid);
    system(buffer);

    clear_array(buffer, sizeof(buffer));

    snprintf(buffer, sizeof(buffer), 
    "printf \"Filename (if any):    \" && cat /proc/%s/cmdline && echo", pid);
    system(buffer);

    clear_array(buffer, sizeof(buffer));

    snprintf(buffer, sizeof(buffer), "cat /proc/%s/status | grep Threads | awk -F: '{print \"Threads:    \"$2}'", pid);
    system(buffer);

    clear_array(buffer, sizeof(buffer));



    // Citation: https://ioflood.com/blog/awk-sum/#:~:text=TL%3BDR%3A%20How%20Do%20I,first%20column%20of%20the%20file.

    // https://www.cyberciti.biz/faq/awk-add-two-numbers/
    //ps -aylC php-cgi  | grep php-cgi | awk '{total += $8}END{size=  total / 1024; printf "php-cgi total size %.2f MB\n", size}'
    
    //CITATION: https://www.codingunit.com/c-tutorial-searching-for-strings-in-a-text-file#:~:text=With%20fgets()%20we%20get,we%20increase%20find_result%20with%20one.
   
    //although i didnt go with awk for this one, I did use some ressources that may have helped me
    char filepath[256];

    int vcs = 0;
    int nvcs = 0;

    snprintf(filepath, sizeof(filepath), "/proc/%s/status",pid);
    
    FILE * f_ptr = fopen(filepath, "r");

    if(f_ptr == NULL) {
        printf("THATS BAD");
    }

    char line[256];

    while (fgets(line, sizeof(line), f_ptr)) {
        if (strstr(line, "voluntary_ctxt_switches:")) {
            sscanf(line, "voluntary_ctxt_switches: %d", &vcs);
        }
        else if (strstr(line, "nonvoluntary_ctxt_switches:")) {
            sscanf(line, "nonvoluntary_ctxt_switches: %d", &nvcs);
        }
    }
    printf("Total context switches:   %d\n",vcs+nvcs);

}
