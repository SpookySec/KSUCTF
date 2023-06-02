#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char username[16];
    char password[16];

    bool is_admin;
    bool logged_in;
} account_t;

char hostname[64];

int menu(account_t* active_account) {

    puts("");
    puts("[1] Login");
    puts("[2] Change username");
    puts("[3] Read flag");
    puts("[4] Logout");

    int input = 0;

    printf("(%s@%s) [%c]> ", active_account->logged_in ? active_account->username : "guest", hostname, active_account->is_admin ? 'A' : 'U');
    scanf("%d", &input);

    fflush(stdin);
    return input;
}

void read_flag() {
    char c;
    FILE* fp = fopen("./flag.txt", "r");
    
    if (!fp) {
        puts("[E] Flag not found.");
        return;
    }

    while ( (c = getc(fp)) != EOF)
        putchar(c);

    fclose(fp);
}

void setup() {
    gethostname(hostname, sizeof(hostname));
    setvbuf(stderr, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
}

int main(void) {
    setup();
    account_t active_user;
    active_user.is_admin = false;
    active_user.logged_in = false;

    int input;

    do {
        input = menu(&active_user);

        switch (input) {
            case 1:
                // Login

                printf("username> ");
                scanf("%16s", active_user.username);

                printf("password> ");
                scanf("%16s", active_user.password);

                active_user.logged_in = true;

                break;

            case 2:
                // Change username

                if (!active_user.logged_in) {
                    puts("[!] Please login first.");
                    break;
                }

                char new_username[70];
                
                printf("username> ");
                fflush(stdout);
                /*fgets(active_user.username, 70, stdin);*/
                read(STDIN_FILENO, new_username, 70);
                strtok(new_username, "\n"); // Strip newline
                strcpy(active_user.username, new_username);

                break;

            case 3:
                // Read the flag

                if (!active_user.logged_in) {
                    puts("[!] Please login first.");
                    break;
                }

                if (!active_user.is_admin) {
                    puts("[E] Only administrators can access the flag.");
                    break;
                }

                read_flag();
                break;

            default:
                break;
        }

    } while (input != 4);

    return 0;
}

