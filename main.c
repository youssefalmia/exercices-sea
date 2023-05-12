#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork(); // cr�ation du processus fils

    if (pid < 0) {
        perror("Erreur lors de la cr�ation du processus fils");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // code du processus fils
        printf("Valeur de fork : %d\n", pid);
        printf("PID du fils : %d\n", getpid());
        printf("PID du p�re du fils : %d\n", getppid());
        exit(2);
    } else { // code du processus p�re
        printf("Valeur de fork : %d\n", pid);
        printf("PID du p�re : %d\n", getpid());
        printf("PID du p�re du p�re : %d\n", getppid());

        int status;
        waitpid(pid, &status, 0); // attente de la fin du processus fils
        printf("Code de retour du processus fils : %d\n", WEXITSTATUS(status));

        // ex�cution du programme qui liste tous les processus actifs
        execlp("ps", "ps", "-e", NULL);
    }

    return 0;
}
