#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void setup() {
    setvbuf(stderr, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
}

unsigned int money = 1337;
int tries = 2;
char* passwords[32] = { 
    "souq", "bazaar",
    "tijara", "mabadee",
    "qimat", "alwan",
    "hawaleat", "tawasul",
    "farsh", "shira",
    "spooky", "nathfa",
    "tabadul", "khidmat",
    "qiyada", "mufid",
    "fatora", "shahama",
    "ayyam", "murabaha",
    "ikhtiyar", "sahm",
    "sahara", "marhalah",
    "tawassut", "muhim",
    "thaman", "dawabit",
    "muhawala", "hukm",
    "amal", "shohra"
};

void banner(void) {
    char* banner = "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠂⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⡞⠁⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⣿⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⡾⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠹⡄⠀⠀⠀⠛⠀⠀⠀⠀⠀⠀⠸⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠙⡆⠀⢀⣀⣀⠀⠀⠀⠀⠀⠈⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⡴⠛⠁⠀⠀⣀⡇⠀⠀⠀⠀⠀⢻⡄⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⡀⠀⠀⠀⢀⡤⠤⠤⢤⡀\n⠤⠤⠤⠤⠤⠤⡾⠤⠖⠒⠒⠊⠉⠀⠀⠀⠀⠀⠘⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⣏⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠿⠴⠶⠤⠤⠤⠤⠴⠚⠹⠶⠶⠶⠶⠶⠵⠶⠶⠶\n";
    puts("\t\tsouk\t\t");
    puts(banner);
}

int main_opt(int balance) {
    int opt;
    puts("");
    puts("[1] Login");
    puts("[2] Buy flag");
    puts("[3] Edit money (admins only)");
    puts("[4] Leave feedback");
    printf("[*] Balance: %u\n", balance);

    printf("> ");
    scanf("%d", &opt);

    fflush(stdin);

    return opt;
}

void login(char* name) {
    printf("username> ");
    fflush(stdin);
    scanf("%30s", name);
}

void edit_money(int is_admin, unsigned int* money) {

    if (!is_admin) {
        printf("This feature is only for admins.\n");
        return;
    }

    long money_buf;

    printf("money amount> ");
    fflush(stdin);
    scanf("%ld", &money_buf);

    if (money_buf > 1936747384) {
        printf("Maximum amount is 1936747384!\n");
        return;
    }

    *money = money_buf;
}

void feedback() {
    char comment[32];
    puts("Thank you for choosing to leave us some feedback!");
    printf("Please leave any comments here> ");
    scanf("%31s", comment);
    printf("Feedback submitted: ");
    printf(comment);
    puts("");
}

void read_flag(const char* secret_word) {
    char password[33];
    if (money != 'spky') {
        puts("Incorrect funds!");
        return;
    }

    puts("What is the secret phrase?");
    printf("Tries left: %d\n", tries);
    printf("password> ");
    scanf("%32s", password);

    if (strcmp(password, secret_word)) {
        puts("Incorrect password!");
        puts("Tries decreased by 1!!");
        tries--;

        if (tries <= 0) {
            puts("Too many tries detected!");
            puts("Terminating...");
            exit(0);
        }

        return;
    }

    money -= 'spky';

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


int main(void) {
    setup();
    volatile int is_admin = 0;
    volatile char name[16];
    banner();

    volatile char* secret_word;
    srand(time(0));
    volatile char* password = passwords[rand() % 32];

    secret_word = password;

    while ('spky' != 1337) {
        int opt = main_opt(money);

        switch (opt) {
            case 1:
                login(name);
                break;

            case 2:
                read_flag(secret_word);
                break;

            case 3:
                edit_money(is_admin, &money);
                break;

            case 4:
                feedback();
                break;

            default:
                break;
        }
    }
}

void 👾() {
    return;
}
