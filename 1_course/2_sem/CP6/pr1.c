
#include <stdio.h>
#include <string.h>
#include "passenger.h"

    int readpassenger(passenger *p) {
        return scanf("%s %[^\t]%d\t%d\t%s\t%s\t%s\t%d\n", p->surname, p->name, &p->Nbaggage, &p->Wbaggage,
                     p->destination, p->timedep, p->transfer, &p->children) == 8;
    }

    void usage() {
        printf("Usage:program filename\n");
    }

    int main(int argc, char *argv[]) {
        //проверка на количество аргументов
        if (argc != 2) {
            usage();
            return 1;
        }

        //создание файла базы
        passenger p;
        FILE *out = fopen(argv[1], "w");
        if (out==NULL) {
            printf("Can't open file\n");
            return 2;
        }

        //считывание строк и запись в файл
        while (readpassenger(&p)) {
            fwrite(&p, sizeof(p), 1, out);
        }
        fclose(out);
        printf("Successfully generated\n");
        return 0;
    }