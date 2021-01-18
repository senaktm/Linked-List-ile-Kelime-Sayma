#include <stdio.h>
#include <string.h>

struct dugum *ilk=NULL, *son=NULL;
int VarMi(char kelime[]);
void BasaEkle(int adetsayisi,char kelime[]);
void SonaEkle(int adetsayisi,char* kelime);
void ArayaEkle(int adetsayisi,char* kelime,struct dugum *yer,struct dugum *onceki);
void SiraliEkle(int adetsayisi,char* kelime);
void listele();

int main()
{
    char dosya_icerigi[1000],kelime[50],kelime2[50];
    int i=0,dosyaUzunlugu,indis,say=0,in;
    FILE *dosya = fopen("dosya.txt","r");

    if(dosya == NULL)
    {
        printf("Dosya acilamadi!");
        return 0;
    }

    //Dosyayý okur
    while(!feof(dosya))
    {
        dosya_icerigi[i]=tolower(getc(dosya));
        i++;
    }

    dosya_icerigi[i]='\0';
    dosyaUzunlugu=strlen(dosya_icerigi)-1;

    for(int j=0; j<dosyaUzunlugu; j++)
    {
        say=0;
        indis=0;
        //Sýradaki kelimeyi alýr
        while(dosya_icerigi[j]!=' ' && dosya_icerigi[j]!='\0' && dosya_icerigi[j]!=10)
        {
            kelime[indis]=dosya_icerigi[j];
            j++;
            indis++;

        }
        if(j==i)
        {
            kelime[indis-1]=NULL;
            indis--;
        }
        if(!VarMi(kelime))
        {
            for(int b=0; b<dosyaUzunlugu; b++)
            {
                in=0;
                //Sýradaki kelimeyi alýr.
                while(dosya_icerigi[b]!=' ' && dosya_icerigi[b]!='\0' && dosya_icerigi[b]!=10)
                {
                    kelime2[in]=dosya_icerigi[b];
                    b++;
                    in++;

                }
                if(b==i)
                {
                    kelime2[in-1]=NULL;
                    indis--;
                }
                //Alýnan iki kelimeyi karþýlaþtýrýr.
                if(strcmp(kelime,kelime2)==0)
                    say++;
                memset(kelime2,NULL,50);
            }
            SiraliEkle(say,kelime);
        }
        memset(kelime,NULL,50);
    }
    listele();
}

struct dugum
{
    char kelimeler[50];
    int adet;
    struct dugum *sonraki;
};


void SonaEkle(int adetsayisi,char* kelime)
{
    struct dugum *yeni = (struct dugum*) malloc(sizeof(struct dugum));
    yeni->adet=adetsayisi;
    for(int j=0; j<50; j++)
        yeni->kelimeler[j]=kelime[j];

    if(ilk==NULL)
    {
        ilk=yeni;
        son=yeni;
        son->sonraki=NULL;
    }
    else
    {
        son->sonraki=yeni;
        son=yeni;
        son->sonraki=NULL;
    }
}

void BasaEkle(int adetsayisi,char kelime[])
{

    struct dugum *yeni = (struct dugum*) malloc(sizeof(struct dugum));
    yeni->adet=adetsayisi;

    strcpy(yeni->kelimeler,kelime);

    if(ilk==NULL)
    {
        ilk=yeni;
        son=yeni;
        son->sonraki=NULL;
    }
    else
    {
        yeni->sonraki=ilk;
        ilk=yeni;
    }
}
void ArayaEkle(int adetsayisi,char* kelime,struct dugum *yer,struct dugum *onceki)
{
    struct dugum *yeni=(struct dugum*) malloc(sizeof(struct dugum));
    yeni->adet=adetsayisi;
    strcpy(yeni->kelimeler,kelime);
    yeni->sonraki=onceki->sonraki;
    onceki->sonraki=yeni;

}

void SiraliEkle(int adetsayisi,char* kelime)
{
    if(ilk==NULL)
    {
        BasaEkle(adetsayisi,kelime);
    }
    else
    {
        struct dugum *yer=ilk;
        struct dugum *onceki=(struct dugum*) malloc(sizeof(struct dugum));
        while(yer!=NULL && yer->adet>adetsayisi)
        {
            onceki=yer;
            yer=yer->sonraki;
        }


        if(yer==NULL){
            SonaEkle(adetsayisi,kelime);
        }

        else if(yer==ilk){
            BasaEkle(adetsayisi,kelime);
        }

        else{
            ArayaEkle(adetsayisi,kelime,yer,onceki);
        }

    }

}

int VarMi(char kelime[])
{
    struct dugum *ara=ilk;
    char kelime2[50];
    while(ara!=NULL)
    {
        strcpy(kelime2,ara->kelimeler);
        if(strcmp(kelime2,kelime)==0)
            return 1;
        ara=ara->sonraki;
    }
    return 0;
}

void listele()
{
    int say=1;
    struct dugum *liste=ilk;
    while(liste!=NULL)
    {
        printf("%d. %s:%d\n",say,liste->kelimeler,liste->adet);
        liste=liste->sonraki;
        say++;
    }
}
