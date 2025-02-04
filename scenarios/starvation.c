#define work()                            \
    for (u64 i = 0; i < (1UL << 23); i++) \
    {                                     \
    }
typedef unsigned long u64;
#define NULL ((void*)0)

int strcmp(const char *str1, const char *str2)
{
    while (1)
    {
        int diff = *str1 - *str2;
        if (diff != 0 || *str1 == 0 || *str2 == 0)
            return diff;
        str1++;
        str2++;
    }
}

int parse_number(const char *buf, u64 *ret, int base)
{
    u64 val = 0;
    int read = 0;

    for (; buf[read] != 0; read++)
    {
        char c = buf[read];
        int digit_val = 100;

        if (c >= '0' && c <= '9')
            digit_val = c - '0';
        else if (c >= 'a' && c <= 'f')
            digit_val = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            digit_val = c - 'A' + 10;

        if (digit_val >= base)
            break;

        val = val * base + digit_val;
    }

    *ret = val;
    return read;
}

/* === system calls === */

u64 systemcall(u64 number, u64 arg1, u64 arg2, u64 arg3)
{
    u64 ret;
    asm("int $0x80\n"
        : "=a"(ret)
        : "a"(number), "b"(arg1), "c"(arg2), "d"(arg3));
    return ret;
}

/* output a message to the screen */
u64 write(char *msg)
{
    return systemcall(1, (u64)msg, 0, 0);
}

/* terminate the current process */
void exit()
{
    systemcall(2, 0, 0, 0);
}

/* spawn a new processes running the given binary with the given argument
    if prog is NULL the current binary is used.
    
    the pid of the new process is returned and can be wait()-ed on.
    */
u64 spawn(char *prog, char *arg)
{
    return systemcall(3, (u64)prog, (u64)arg, 0);
}

/* stop execution for a given number of microseconds */
void sleep(u64 micros)
{
    systemcall(4, micros, 0, 0);
}

/* stop execution until the process with the given pid terminates */
u64 wait(u64 pid)
{
    return systemcall(5, pid, 0, 0);
}

u64 spawn_with_prio(char *prog, char *arg, u64 prio)
{
    return systemcall(3, (u64)prog, (u64)arg, prio);
}

/* === */

#define MSEC 1000UL

void _start(char *argument)
{
    if (strcmp(argument, "init") == 0)
    {
        write("I am init\n"); 
    
        
        spawn_with_prio(NULL, "batch_task", 3);
        spawn_with_prio(NULL, "interactive_task_1", 1);
        spawn_with_prio(NULL, "interactive_task_2", 1);
        spawn_with_prio(NULL, "interactive_task_3", 1);
        spawn_with_prio(NULL, "interactive_task_4", 1);
    
        spawn_with_prio(NULL, "interactive_task_5", 1);
        
    }
    if (strcmp(argument, "interactive_task_1") == 0 || 
            strcmp(argument, "interactive_task_2") == 0 || 
            strcmp(argument, "interactive_task_3") == 0 ||
            strcmp(argument, "interactive_task_4") == 0 ||
            strcmp(argument, "interactive_task_5") == 0)

    {
        // Simulate quick interactive/user tasks
        for (int i = 0; i < 10; i++) {
            sleep(100 * MSEC);
            write("HI\n");
        }

    }
    if (strcmp(argument, "batch_task") == 0)
    {
        // Simulate a longer batch task that needs CPU time
        for (int i = 0; i < 100; i++) {
            work();
            
        }
    }

    exit();
}

