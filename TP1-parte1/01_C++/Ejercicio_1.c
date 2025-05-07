#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void named_process(const char *name);
void create_children(void (*func)());
void wait_all();
void process_B();
void process_C();
void process_D();
void process_E();
void process_F();
void process_G();
void process_H();
void process_I();

int main()
{
    named_process("A");
    create_children(process_B);
    wait(NULL);
    return 0;
}

void named_process(const char *name)
{
    prctl(PR_SET_NAME, name);
    printf("Proceso %s: PID=%d, PPID=%d\n", name, getpid(), getppid());
}

void create_children(void (*func)())
{
    pid_t pid = fork();
    if (pid == 0)
    {
        func();
        exit(0);
    }
}

void wait_all()
{
    while (wait(NULL) > 0)
        ;
}

void process_B()
{
    named_process("B");
    create_children(process_C);
    create_children(process_D);
    wait_all();
}

void process_C()
{
    named_process("C");
    create_children(process_E);
    wait_all();
}

void process_D()
{
    named_process("D");
    create_children(process_F);
    create_children(process_G);
    wait_all();
}

void process_E()
{
    named_process("E");
    create_children(process_H);
    create_children(process_I);
    wait_all();
}

void process_F()
{
    named_process("F");
    sleep(20);
}
void process_G()
{
    named_process("G");
    sleep(20);
}
void process_H()
{
    named_process("H");
    sleep(20);
}
void process_I()
{
    named_process("I");
    sleep(20);
}