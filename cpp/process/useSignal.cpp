#include <unistd.h>

#include <csignal>
#include <iostream>
static void sig_handler(int signum) {
    switch (signum) {
        case SIGUSR1:
            std::cout << "SIGUSR1";
            stop();
            break;
        case SIGUSR2:
            std::cout << "SIGUSR2";
            stop();
            break;
        case SIGTERM:
            std::cout << "SIGTERM";
            stop();
            break;
    }
    exit(0);
}

int main() {
    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);
    signal(SIGTERM, sig_handler);
    return 0;
}