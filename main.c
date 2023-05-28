#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ogrenci {
    long int studentID;
    char bolum[100];
    char name[100];
};

void dosya_yap();
void ogrenci_ekle();
void searchByName();
void listStudents();

int main() {
    int choice;

    do {
        printf("\n----- Menu -----\n");
        printf("1- Ogrenci kaydi ekle\n");
        printf("2- Dosya olustur\n");
        printf("3- Ogrencileri listele\n");
        printf("4- �simlere gore ogrenci ara ve bilgilerini ekrana yazdir\n");
        printf("5- Cikis\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &choice);
        getchar();


        switch (choice)
        {
            case 1:
                ogrenci_ekle();
                break;

            case 2:
                dosya_yap();
                break;

            case 3:
                listStudents();
                break;

            case 4:
                searchByName();
                break;

            case 5:
                printf("Programdan cikiliyor\n");
                break;

            default:
                printf("Yanlis secim, lutfen tekrar deneyin!\n");
        }
    }
    while (choice != 5);

    return 0;
}



void dosya_yap()
{
    FILE* file = fopen("students.dat", "wb");

    if (file == NULL)
        {
        printf("Dosya olusturulamadi:\n");
        return;
        }

    printf("Dosya olu�turuldu: students.dat\n");
    fclose(file);
}



void searchByName()
{
    char searchName[50];
    struct Ogrenci ogrenci;
    FILE* file = fopen("students.dat", "rb");

    if (file == NULL)
    {
        printf("Dosya a��lamad�.\n");
        return;
    }



    printf("Aramak istediginiz ��rencinin adini girin: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';



    while (fread(&ogrenci, sizeof(struct Ogrenci), 1, file))
    {
        if (strcmp(ogrenci.name, searchName) == 0)
        {
            printf("\nOgrenci bulundu:\n");
            printf("Ogrenci Kimligi: %ld\n", ogrenci.studentID);
            printf("Adi: %s\n", ogrenci.name);
            printf("Bolumu: %s\n", ogrenci.bolum);
            fclose(file);
            return;
        }
    }


    printf("Ogrenci bulunamadi.\n");
    fclose(file);
}



void ogrenci_ekle()
{
    struct Ogrenci ogrenci;
    FILE* file = fopen("students.dat", "ab");

    if (file == NULL)
        {
        printf("Dosya a��lamad�.\n");
        return;
        }


    printf("Ogrenci bilgilerini girin:\n");
    printf("Ogrenci Kimligi: ");
    scanf("%ld", &ogrenci.studentID);
    getchar();

    printf("Adi: ");
    fgets(ogrenci.name, sizeof(ogrenci.name), stdin);

    ogrenci.name[strcspn(ogrenci.name, "\n")] = '\0';
    printf("B�l�m�: ");
    fgets(ogrenci.bolum, sizeof(ogrenci.bolum), stdin);

    ogrenci.bolum[strcspn(ogrenci.bolum, "\n")] = '\0';

    fwrite(&ogrenci, sizeof(struct Ogrenci), 1, file);

    printf("Ogrenci kaydedildi:\n");
    fclose(file);
}



void listStudents()
{
    struct Ogrenci ogrenci;
    FILE* file = fopen("students.dat", "rb");

    if (file == NULL)
    {
        printf("Dosya acilamadi:\n");
        return;
    }

    printf("��renciler:\n");


    while (fread(&ogrenci, sizeof(struct Ogrenci), 1, file))
    {
        printf("Ogrenci Kimligi: %ld\n", ogrenci.studentID);
        printf("Adi: %s\n", ogrenci.name);
        printf("Bolumu: %s\n", ogrenci.bolum);
        printf("\n");
    }

    fclose(file);
}
