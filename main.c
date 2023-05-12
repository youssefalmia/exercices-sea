#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork(); // création du processus fils

    if (pid < 0) {
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // code du processus fils
        printf("Valeur de fork : %d\n", pid);
        printf("PID du fils : %d\n", getpid());
        printf("PID du père du fils : %d\n", getppid());
        exit(2);
    } else { // code du processus père
        printf("Valeur de fork : %d\n", pid);
        printf("PID du père : %d\n", getpid());
        printf("PID du père du père : %d\n", getppid());

        int status;
        waitpid(pid, &status, 0); // attente de la fin du processus fils
        printf("Code de retour du processus fils : %d\n", WEXITSTATUS(status));

        // exécution du programme qui liste tous les processus actifs
        execlp("ps", "ps", "-e", NULL);
    }

    return 0;
}
