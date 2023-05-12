#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pid_t pid;

    /* Création du tube */
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    /* Création du premier processus */
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { /* Code exécuté par le fils */
        /* Fermeture de la sortie standard */
        close(STDOUT_FILENO);
        /* Duplication du descripteur de fichier de sortie sur le tube */
        dup(fd[1]);
        /* Fermeture des descripteurs inutiles */
        close(fd[0]);
        close(fd[1]);
        /* Exécution de la commande ls -al */
        execlp("ls", "ls", "-al", NULL);
        /* En cas d'échec de l'exécution de la commande */
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { /* Code exécuté par le père */
        /* Fermeture de l'entrée standard */
        close(STDIN_FILENO);
        /* Duplication du descripteur de fichier d'entrée sur le tube */
        dup(fd[0]);
        /* Fermeture des descripteurs inutiles */
        close(fd[0]);
        close(fd[1]);
        /* Exécution de la commande wc -l */
        execlp("wc", "wc", "-l", NULL);
        /* En cas d'échec de l'exécution de la commande */
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    /* Attente de la fin du processus fils */
    wait(NULL);

    return 0;
}