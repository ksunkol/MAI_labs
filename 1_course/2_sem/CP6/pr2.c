#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passenger.h"

void usage() {
    printf("Usage:program [key] <p> filename\n");
}

int readpassenger(passenger *p) {
    return scanf("%s %[^\t]%d\t%d\t%s\t%s\t%s\t%d\n", p->surname, p->name, &p->Nbaggage, &p->Wbaggage,
                 p->destination, p->timedep, p->transfer, &p->children) == 8;
}

int str_to_int(char x[]) {     //строка в инт
    int ans = 0;
    int pos = 1;
    for (int i = strlen(x) - 1; i >= 0; i--) {
        if (x[i] < '0' || x[i] > '9') return -1;
        ans += pos * (x[i] - '0');
        pos *= 10;
    }
    return ans;
}

int main(int argc, char *argv[]) {
    //проверка на количество параметров
    if (argc < 2 || argc > 3) {
        usage();
        return 1;
    }
    //распечатка базы по ключу -f
    if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'f') {

        FILE *base = fopen(argv[2], "rb");
        if (base==NULL) {
            printf("Can't open file\n");
            return 2;
        }

        int j = 1;
        passenger p;
        printf("№  |%-14s|%2s |%3s  |%s |%-7s| %-5s| %s\n", "Name", "N", "W", "Destination", "TimeDep", "Tr", "Ch");
        printf("-------------------------------------------------------------\n");
        while (fread(&p, sizeof(passenger), 1, base) > 0) {
            printf("%-3d|%-10s%s |%2d | %3d | %-10s | %-6s| %s\t| %d\n",j, p.surname, p.name, p.Nbaggage, p.Wbaggage,
                   p.destination,
                   p.timedep, p.transfer, p.children);
            j++;
        }
        fclose(base);
        return 0;
    }
    //Добавление записи в базу по ключу -a
    if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'a') {
        passenger p;
        readpassenger(&p);
        FILE *out = fopen(argv[2], "a");
        if (out==NULL) {
            printf("Can't open file\n");
            return 2;
        }
        fwrite(&p, sizeof(p), 1, out);
        fclose(out);
        printf("Successfully added\n");
        return 0;
    }

    //работа с параметром <p>
    if(str_to_int(argv[1])==-1){
        usage();
        printf("<p> must be integer-valued\n");
        return 1;
    }
    passenger p1;
    passenger p2;

    FILE *in = fopen(argv[2], "r");
    if (in==NULL) {
        printf("Can't open file\n");
        return 2;
    }

    long int i = 1;

    while (fread(&p1, sizeof(passenger), 1, in) == 1) {

        if (fread(&p2, sizeof(passenger), 1, in) != 1) {
            printf("Нет пассажиров,багаж которых совпадает по числу вещей и различается по весу не более чем на %s кг\n",
                   argv[1]);
            fclose(in);
            return 0;
        }
        do {
            if (p1.Nbaggage == p2.Nbaggage && (abs(p1.Wbaggage - p2.Wbaggage)) <= str_to_int(argv[1])) {
                printf("Есть пассажиры,багаж которых совпадает по числу вещей и различается по весу не более чем на %s кг\n\n",
                       argv[1]);
                printf("|%-14s|%2s |%3s  |\n","Name","N","W");
                printf("|%-10s%s |%2d | %3d |\n",p1.surname,p1.name,p1.Nbaggage,p1.Wbaggage);
                printf("|%-10s%s |%2d | %3d |\n",p2.surname,p2.name,p2.Nbaggage,p2.Wbaggage);
                fclose(in);
                return 0;
            }
        } while (fread(&p2, sizeof(passenger), 1, in) == 1);
        fseek(in, sizeof(passenger) * i, SEEK_SET);
        i++;

    }
}