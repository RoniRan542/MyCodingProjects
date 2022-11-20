#ifndef __SIMPLESHELL_H__
#define __SIMPLESHELL_H__

int SimpleShell(const char *fork_or_system);

#if 0
in C:
static int SimpleShellFork(void);
// returns success/fail according to fork() return value. //

static int SimpleShellSystem(void);

int main(int argc, char *argv[])
{
    // argv = fork/system //
    // SimpleShell(argv[1]); //
    return 0;
}
#endif

#endif /* __SIMPLESHELL_H__ */