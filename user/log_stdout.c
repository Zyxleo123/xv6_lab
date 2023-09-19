#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include <stdarg.h>
char buf[1024];
int read_stdin(char *buf)
{
    /*
    Description: Read stdin into buf
    Example:
    - read_stdin(); // Read the stdin into buf
    Parameters:
    - buf (char*): A buffer to store all characters
    Return:
    - 0 (int)
    */
    // Your code here
    if (read(0, buf, sizeof buf) < 0)
    {
        return -1;
    }
    return 0;
    // End
}

int log_stdout(uint i)
{
    /*
    Description: Redirect stdout to a log file named i.logExample:
    - log_stdout(1); // Redirect the stdout to 1.log and return 0
    Parameters:
    - i (uint): A number
    Return:
    - 0 (int)
    */
    char log_name[15] = "0.log";
    // Your code here
    if (i != 0)
    {
        // get length of the number
        int length = 0;
        for (int tmp = i; tmp; length++, tmp /= 10);
        for (int j = length - 1; j >= 0; j--)
        {
            log_name[j] = i % 10 + '0';
            i /= 10;
        }
        char postfix[5] = ".log";
        for (int k = 0, j = length; k < sizeof postfix; k++, j++)
        {
            log_name[j] = postfix[k];
        }
    }
    close(1);
    if (open(log_name, O_CREATE | O_WRONLY | O_TRUNC) != 1)
    {
        fprintf(2, "log_stdout: open failed\n");
        return -1;
    }
    // End
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(2, "Usage: log_stdout number\n");
        exit(1);
    }
    if (log_stdout(atoi(argv[1])) != 0)
    {
        fprintf(2, "log_stdout: log_stdout failed here\n");
        exit(1);
    }
    if (read_stdin(buf) != 0)
    {
        fprintf(2, "log_stdout: read_stdin failed\n");
        exit(1);
    }
    fprintf(1, "%s", buf);
    exit(0);
}