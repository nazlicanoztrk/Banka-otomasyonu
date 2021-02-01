#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char hesapAdi[50];
    int hesapNo;
    int musteriNo;
    float bakiye;
}Hesap;

typedef struct{
    char Ad[50];
    char Soyad[50];
    int musteriNo;
    Hesap *hesap;
    int hesapSayisi;
    int tip;
}Musteri;

char* DosyaOku(char*);
int KayitSay(char*);
int KayitKontrol(Musteri);
void KayitEkle(char*,Musteri*,int);
void KayitGuncelle(char*,Musteri[],int);
int KayitBul(char*,int,int);
int KayitSil(char*,int);
int NumaraBul(char*, int);
int HesapKontrol();
void HesapGuncelle(char*,Hesap[],int);
void HesapEkle(char *,Hesap *,int);

int MAX = 100;
int main()
{
    setlocale(LC_ALL,"Turkish");
    Musteri *pArr;
    pArr = calloc(1, sizeof(Musteri));

    printf("  CMG BANK in C\n************************\n");

    /* Kayit Sayisi Kontrolü*/
    int restriction = 0, kayitSayisi;
    /* Menu */
    char sec;
    char isim[100];
    int countTry = 0, secim, duzenle = 0, sonuc;
    do{
        printf("\n1. Musteri Ekle\n2. Hesap Acma\n3. Para Cekme\n4. Para Yatirma\n5. Havale\n6. Banka Gelir-Gider Raporu\n7. Hesap Ozeti \n8. Hesap Kapatma\n0. Cikis\n");
        printf("Secim : "); scanf("%d",&secim);
        switch(secim){

            /* Cikis Bolumu */
            case 0:
                exit(1);
                break;

            /* Musteri Ekleme */
            case 1:
                system("CLS");
                char isim[100], soyad[100];
                int tip = 0;
                printf("Musteri Ekleme Bolumune Hosgeldiniz!\n");
                printf("Ad:"); scanf(" %s",isim);
                strcpy(pArr->Ad,isim);
                printf("Soyad:"); scanf(" %s",soyad);
                strcpy(pArr->Soyad,soyad);
                printf("Musteri Tipi (Bireysel için 1, Ticari için 2):"); scanf(" %d",&tip);

                duzenle = 0;
                pArr->hesapSayisi = 0;
                pArr->musteriNo = KayitKontrol(*pArr);

                if(tip == 1){
                    pArr->tip = tip;
                    KayitEkle("bireysel.txt",pArr,duzenle);
                }else{
                    pArr->tip = tip;
                    KayitEkle("ticari.txt",pArr,duzenle);
                }
                printf("Musteri Numaraniz: %d",pArr->musteriNo);
                break;

                /* Tum Kayitlari Listeleme */
            case 2:
                system("CLS");
                Hesap *hesap;
                hesap = calloc(1, sizeof(Hesap));
                int musteriNo;
                char hesapAdi[100];
                printf("Hesap Acmak istediginiz Musteri NO: "); scanf("%d",&musteriNo);
                //printf("%d",NumaraBul("bireysel.txt",musteriNo));
                if(NumaraBul("bireysel.txt",musteriNo) == 1 || NumaraBul("ticari.txt",musteriNo) == 1){
                    printf("Hesap Adi: "); getchar(); gets(hesap->hesapAdi);
                    hesap->bakiye = 0;
                    hesap->musteriNo = musteriNo;
                    hesap->hesapNo = HesapKontrol();
                    printf("124");
                    duzenle = 0;
                    if(hesap->hesapNo != 0){
                        HesapEkle("hesap.txt", hesap, duzenle);
                    }
                }
                else
                    printf("hata.........\n");
                printf("Isleminiz basarili bir sekilde gerceklestirilmistir... Hesap bilgileri asagida yer almaktadir.\n");
                printf("\nHesap Adi: %s\nHesap No: %d\nHesap Bakiyesi: %.2f\n",hesap->hesapAdi,hesap->hesapNo,hesap->bakiye);
                countTry = 0;
                break;

                /* Kayit Duzenleme */
            case 3:
                system("CLS");
                duzenle = 1;
                do{
                    printf("Para Cekme Hosgeldiniz!\n");
                    int musteriNo,hesapNo,miktar,tip;
                    printf("Musteri Tipi: "); scanf("%d",&tip);
                    printf("Para Cekecek Musteri: "); scanf("%d",&musteriNo);
                    if(tip == 1){
                        sonuc = KayitBul("bireysel.txt",musteriNo, duzenle);

                    }
                    else{
                        sonuc = KayitBul("ticari.txt",musteriNo, duzenle);

                    }
                    if(!sonuc)
                    {
                        printf("Tekrar Arama Yapmak ister misiniz? (E / H)\n");
                        scanf(" %c",&sec);
                    }else{

                        printf("Para Cekilecek Hesap: "); scanf("%d",&hesapNo);
                        printf("Miktar: "); scanf("%d",&miktar);
                        HesapBul("hesap.txt",musteriNo,duzenle,miktar,hesapNo);
                    }
                }while(sec == 'E');
                break;

                /* Para Yatirma islemi */
            case 4:
                system("CLS");
                int bakiye=0;


                    printf("Cekiceginiz Tutar :"); scanf("%lld",&bakiye);

                   //Musteri.hesap-bakiye=Musteri.hesap;
                   printf("isleminiz basariyla gerceklestirildi.");

                break;

                /* Isim ile Kayit Bulma */
            case 5:
                system("CLS");
                int sonuc;
                duzenle = 0;
                do{
                    printf("Isim ile Kayit Bulma Bolumune Hosgeldiniz!\n");
                    printf("Isim: "); scanf("%s",isim);
                    sonuc = KayitBul("hesap.txt",isim,duzenle);
                    if(!sonuc)
                    {
                        printf("Tekrar Arama Yapmak ister misiniz? (E / H)\n");
                        scanf(" %c",&sec);
                    }
                }while(sec == 'E');
                break;

                /* Para cekme */
            case 6:
                system("CLS");
                long int kod;
                do{
                    printf("Kayit Silme Bolumune Hosgeldiniz!\n");
                    printf("Musteri adi:"); scanf("%ld",&kod);
                    sonuc = KayitSil("hesap.txt",kod);
                if(!sonuc)
                {
                    printf("Tekrar Arama Yapmak Ister misiniz? (E / H)\n");
                    scanf(" %c",&sec);
                }
                }while(sec == 'E');
                break;
            default:
                printf("Gecersiz secim islemi lutfen tekrar deneyiniz!\n");
                countTry++;
                break;
        }
    }while(countTry != 3);
    return 0;
}

char* DosyaOku(char *DosyaAdi)
{
    char *text = NULL;
    int i, text_size;
    FILE *fp = fopen(DosyaAdi,"r");
    if(fp != NULL)
    {
        /* imleci en sona götür. */
        fseek(fp,0,SEEK_END);

        /* imlecin bulundugu byte degerini al */
        text_size = ftell(fp);
        /* imleci en basa geri gönder */
        rewind(fp);

        /* imlecin bulundugu noktaya kadar boyut yarat */
        text = (char *) malloc(sizeof(char) * (text_size + 1));

        // For döngüsüyle ayni islemi döngü kullanmadan stdio.h kutuphanesinin kendi fonksiyonu ile yapar.
        fread(text,sizeof(char),text_size,fp);
    /* En Sevdigimiz "Actigin dosyayi kapat!" */
    fclose(fp);
    }
    else{
        printf("Dosya isleminde bir sorun yasandi!");
        exit(1);
    }
    return text;
}
void KayitEkle(char *DosyaAdi,Musteri *musteri,int duzenle)
{
    FILE *fp;
    fp = fopen(DosyaAdi,"a");
    if(fp != NULL)
    {
        if(fwrite(musteri, sizeof(*musteri), 1, fp) != 1)
        {
            printf("Yazma islemi Basarisiz oldu!\n");
            exit(1);
        }
        fclose(fp);
        if(duzenle == 0)
        {
            printf("Kayit Eklendi!\n\n");
        }
    }
    else{
        printf("Yazma islemi Basarisiz oldu!\n");
        exit(1);
    }
    fclose(fp);
}
int KayitBul(char *DosyaAdi,int musteriNo,int duzenle)
{
    /*
        Duzenle Parametresi isim ile kayit bulma ve kayit duzenleme bolumunde ayni fonksiyon kullanildigi icin cagirildigi yere gore tepki vermesi icindir.
    */
    FILE *fp;
    Musteri *pArr,Kisi[MAX];
    pArr = &Kisi;
    char nameTag[20],kodTag[20],noTag[20],lengthTag[20], tipTag[20];
    fp = fopen(DosyaAdi,"r+");
    int kayitBulunan[MAX];
    int FlagOne = 0,i = 0,c = 0,kayitNo;
    bool isEqual;
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp," %s %s ",nameTag,&(pArr+i)->Ad);
            fscanf(fp," %s %s ",kodTag,&(pArr+i)->Soyad);
            fscanf(fp," %s %d ",noTag,&(pArr+i)->musteriNo);
            fscanf(fp," %s %d ",lengthTag,&(pArr+i)->hesapSayisi);
            fscanf(fp," %s %d ",tipTag,&(pArr+i)->tip);
            isEqual = ((pArr+i)->musteriNo == musteriNo);
            if(isEqual)
            {
                printf("\n%d. Kayit:\n%s %s\n%s %d\n%s %d\n%s %d\n%s %d\n",i+1,nameTag,(pArr+i)->Ad,kodTag,(pArr+i)->Soyad,noTag,(pArr+i)->musteriNo,lengthTag,(pArr+i)->hesapSayisi,tipTag,(pArr+i)->tip);
                kayitBulunan[c]=i;
                c++;
                FlagOne++;
            }
            i++;
        }
        if(FlagOne != 0)
        {
            fclose(fp);
            printf("\n%d Kayit bulundu.\n",FlagOne);
            if(duzenle == 1) // Eger Duzenleme Bolumunde Cagirilmissa fonksiyon duzenleme degeri 1 olarak gonderildigi icin bu blok calisir
            {
                return 1; // 1 dondurulurse Kayit Bulundugunda yapilacak islem sirasini takip etmesi icin Main fonksiyonuna yansitilir
            }
        }
        else{
            fclose(fp);
            printf("\nKayit Bulunamadi.\n");
            return 0; // 0 dondurulurse Kayit Bulundugunda yapilacak islem sirasini takip etmesi icin Main fonksiyonuna yansitilir
        }
    }
    else{
        printf("Okuma islemi basarisiz oldu!\n");
        exit(1);
    }
}
void KayitGuncelle(char *DosyaAdi,Musteri musteri[],int kayitNo) //  kayitNo parametresi KayitBul fonksiyonunda gonderilen degerdir
{
    Musteri *pArr, updated;
    pArr = &musteri[0];
    char ad[100], soyad[100];
    char nameTag[20],kodTag[20],noTag[20],lengthTag[20], tipTag[20];
    printf("Ad:"); scanf(" %s",ad);
    strcpy(updated.Ad,ad);
    printf("Soyad:"); scanf(" %s",soyad);
    strcpy(updated.Soyad,soyad);
    printf("Musteri No:"); scanf("%d",&updated.musteriNo);
    printf("Hesap Sayisi:"); scanf("%d",&updated.hesapSayisi);
    int i=0,guncelle = 1;
    if(KayitKontrol(*pArr))  // Girilen girdilerin uygunlugu KayitKontrol Fonksiyonu ile kontrol ediliyor
    {
        FILE *fp_new;
        FILE *fp_old;
        if((fp_old = fopen(DosyaAdi,"r+")) == NULL)
        {
            printf("Dosya Acilamadi ! \n");
            exit(1);
        }
        if((fp_new = fopen("Yeni_Dosya.txt","wt")) == NULL)
        {
            printf("Dosya Acilamadi ! \n");
            exit(1);
        }
        while(!feof(fp_old)) // Tum Kayitlar diziye aliniyor
        {
                fscanf(fp_old," %s %s ",nameTag,&(pArr+i)->Ad);
                fscanf(fp_old," %s %s ",kodTag,&(pArr+i)->Soyad);
                fscanf(fp_old," %s %d ",noTag,&(pArr+i)->musteriNo);
                fscanf(fp_old," %s %d ",lengthTag,&(pArr+i)->hesapSayisi);
                fscanf(fp_old," %s %d ",tipTag,&(pArr+i)->tip);
                i++;
        }
        int c;
        for(c=0;c<i;c++) // Tum kayitlar duzenlenecek kayit disinda yeni klasore aktariliyor
        {
            if(c==kayitNo)
                continue;
            else{
                fprintf(fp_new,"Ad: %s\n",(pArr+c)->Ad);
                fprintf(fp_new,"Soyad: %s\n",(pArr+c)->Soyad);
                fprintf(fp_new,"MusteriNo: %d\n",(pArr+c)->musteriNo);
                fprintf(fp_new,"HesapSayisi: %d\n",(pArr+c)->hesapSayisi);
                fprintf(fp_new,"Tip: %d\n",(pArr+c)->tip);
            }
        }
        fclose(fp_new);
        fclose(fp_old);
       // KayitEkle("Yeni_Dosya.txt",updated,guncelle); // guncellenecek deger yeni klasore yeni kayit gibi ekleniyor
        remove(DosyaAdi);
        rename("Yeni_Dosya.txt",DosyaAdi); // Yeni dosyamiza asil dosyamizin adini veriyoruz
        printf("Kayit Guncellendi!\n");
    }
    else{
        printf("Kayit Guncellenemedi!\n");
    }
}
int KayitKontrol(Musteri musteri) // Girdi kontrol fonksiyonu
{
        srand (time(NULL));
        int r = rand() % 10000;
        int musteriNo = 1;
        if(musteri.tip == 1){
            while(musteriNo == 1){
                musteriNo = NumaraBul("bireysel.txt",r);
            }
        }else{
            while(musteriNo == 1){
                musteriNo = NumaraBul("ticari.txt",r);
            }
        }
        return r;
}
int HesapKontrol() // Girdi kontrol fonksiyonu
{
        srand (time(0));
        int r = rand();
        int hesapNo = 1;
        while(hesapNo == 1)
            hesapNo = HesapNumaraBul("hesap.txt",r);
        return r;
}
int NumaraBul(char *DosyaAdi,int musteriNo) // Numara ile Kayit Bulma fonksiyonu
{
    FILE *fp;
    Musteri *pArr;
    pArr = calloc(1, sizeof(Hesap));
    fp = fopen(DosyaAdi,"r+");
    if(fp != NULL)
    {
        while(fread(pArr, sizeof(*pArr), 1, fp) == 1)
        {
            if(pArr->musteriNo == musteriNo)
                return 1;
        }
        return 0;
    }
    else{
        printf("Okuma islemi basarisiz oldu!\n");
        exit(1);
    }
}
int KayitSil(char *DosyaAdi,int musteriNo) //Kayit Sil Fonksiyonu
{
    FILE *fp_old;
    FILE *fp_new;
    Musteri *pArr,Kisi[MAX];
    pArr = &Kisi[0];
    char nameTag[20],kodTag[20],noTag[20],lengthTag[20], tipTag[20];
    int i=0, FlagOne = 0,kayitNo,c=0;
    int kayitBulunan[MAX];
    if((fp_old = fopen(DosyaAdi,"r")) == NULL)
    {
        printf("Dosya Acilamadi ! \n");
    }
    if((fp_new = fopen("Yeni_Dosya.txt","wt")) == NULL)
    {
        printf("Dosya Acilamadi ! \n");
    }
    while(!feof(fp_old)) //Eski dosyadaki tüm veriler Struct dizimize alýnýyora
    {
            fscanf(fp_old," %s %s ",nameTag,&(pArr+i)->Ad);
            fscanf(fp_old," %s %s ",kodTag,&(pArr+i)->Soyad);
            fscanf(fp_old," %s %d ",noTag,&(pArr+i)->musteriNo);
            fscanf(fp_old," %s %d ",lengthTag,&(pArr+i)->hesapSayisi);
            fscanf(fp_old," %s %d ",tipTag,&(pArr+i)->tip);
            if((pArr+i)->musteriNo == musteriNo)
            {
                printf("\n%d. Kayit:\n%s %s\n%s %d\n%s %d\n%s %d\n%s %d\n",i+1,nameTag,(pArr+i)->Ad,kodTag,(pArr+i)->Soyad,noTag,(pArr+i)->musteriNo,lengthTag,(pArr+i)->hesapSayisi,(pArr+i)->tip);
                kayitBulunan[c]=i;
                FlagOne++;
                c++;
            }
            i++;
   }
   if(FlagOne != 0)
   {    int c;
        printf("\n%d Kayit bulundu.\n",FlagOne);
        int FlagTwo = 0;
        do{
            printf("Silmek istediginiz kayit numarasi:");
            scanf("%d",&kayitNo);
            for(c=0;c<i;c++)
            {
                // kayitNo ile listelenen kayitlar uyusuyorsa Kayit Duzenleme Fonksiyonu Cagiriliyor
                if(kayitBulunan[c] == (kayitNo-1))
                {
                    FlagTwo = 1;
                    break;
                }
            }
            if(c==i)
            {
                printf("\nGecersiz Kayit Numarasi!\n");
            }
        }while(FlagTwo == 0);
        for(c=0;c<i;c++) //Silenecek Kayit haric diger tum kayitlar yeni dosyaya aktariliyor
        {
            if(c != (kayitNo-1))
            {
                fprintf(fp_new,"Ad: %s\n",(pArr+c)->Ad);
                fprintf(fp_new,"Soyad: %s\n",(pArr+c)->Soyad);
                fprintf(fp_new,"MusteriNo: %d\n",(pArr+c)->musteriNo);
                fprintf(fp_new,"HesapSayisi: %d\n",(pArr+c)->hesapSayisi);
                fprintf(fp_new,"Tip: %d\n",(pArr+c)->tip);
            }else{
                continue;
            }
        }
        printf("Kayit Silindi!\n");
        fclose(fp_new);
        fclose(fp_old);
        /* Dosya degisim islemleri */
        remove(DosyaAdi);
        rename("Yeni_Dosya.txt",DosyaAdi);
        return 1;
   }
   else{
        fclose(fp_new);
        fclose(fp_old);

        remove(DosyaAdi);
        rename("Yeni_Dosya.txt",DosyaAdi);
        printf("\nKayit Bulunamadi.\n");
        return 0;
   }
}
int KayitSay(char *DosyaAdi)// Dosyadaki Tum kayitlari sayan Fonksiyon ve sayisini donduren fonksiyon
{
    FILE *fp;
    fp = fopen(DosyaAdi,"r+");
    Musteri *pArr,Musteri;
    pArr = &Musteri;
    char nameTag[20],kodTag[20],noTag[20],lengthTag[20], tipTag[20];
    int i=0;
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp," %s %s ",nameTag,&(pArr+i)->Ad);
            fscanf(fp," %s %s ",kodTag,&(pArr+i)->Soyad);
            fscanf(fp," %s %d ",noTag,&pArr->musteriNo);
            fscanf(fp," %s %d ",lengthTag,&pArr->hesapSayisi);
            fscanf(fp," %s %d ",tipTag,&pArr->tip);
            i++;
        }
        fclose(fp);
        return i;
    }
    else{
        printf("Dosya Bulunamadi!\n");
        exit(1);
    }
}
int HesapNumaraBul(char *DosyaAdi,int hesapNo) // Numara ile Kayit Bulma fonksiyonu
{
    FILE *fp;
    Hesap *pArr;
    pArr = calloc(1, sizeof(Hesap));
    fp = fopen(DosyaAdi,"r+");
    if(fp != NULL)
    {
        while(fread(pArr, sizeof(*pArr), 1, fp) == 1)
        {
            if(pArr->hesapNo == hesapNo)
                return 1;
        }
        return 0;
    }
    else{
        printf("Okuma islemi basarisiz oldu!\n");
        exit(1);
    }
}
void HesapEkle(char *DosyaAdi,Hesap *hesap,int duzenle)
{
    FILE *fp;
    fp = fopen(DosyaAdi,"a");
    if(fp != NULL)
    {
        if(fwrite(hesap, sizeof(*hesap), 1, fp) != 1)
        {
            printf("Yazma islemi Basarisiz oldu!\n");
            exit(1);
        }
        if(duzenle == 0)
        {
            printf("Kayit Eklendi!\n\n");
        }
    }
    else{
        printf("Yazma islemi Basarisiz oldu!\n");
        exit(1);
    }
    fclose(fp);
}
void HesapGuncelle(char *DosyaAdi,Hesap *hesap,int kayitNo) //  kayitNo parametresi KayitBul fonksiyonunda gonderilen degerdir
{
    Hesap *pArr, updated;
    pArr = &hesap[0];
    char ad[100], soyad[100];
    char nameTag[20],kodTag[20],noTag[20],lengthTag[20];
    printf("Hesap Adi:"); scanf(" %s",ad);
    strcpy(updated.hesapAdi,ad);
    printf("Bakiye:"); scanf("%.2fd",&updated.bakiye);
    int i=0,guncelle = 1;
    FILE *fp_new;
    FILE *fp_old;
    if((fp_old = fopen(DosyaAdi,"r+")) == NULL)
    {
        printf("Dosya Acilamadi ! \n");
        exit(1);
    }
    if((fp_new = fopen("Yeni_Dosya.txt","wt")) == NULL)
    {
        printf("Dosya Acilamadi ! \n");
        exit(1);
    }
    while(!feof(fp_old)) // Tum Kayitlar diziye aliniyor
    {
            fscanf(fp_old," %s %s ",nameTag,&(pArr+i)->hesapAdi);
            fscanf(fp_old," %s %d ",kodTag,&(pArr+i)->hesapNo);
            fscanf(fp_old," %s %d ",noTag,&(pArr+i)->musteriNo);
            fscanf(fp_old," %s %.2fd ",lengthTag,&(pArr+i)->bakiye);
            i++;
    }
    int c;
    for(c=0;c<i;c++) // Tum kayitlar duzenlenecek kayit disinda yeni klasore aktariliyor
    {
        if(c==kayitNo)
            continue;
        else{
            fprintf(fp_new,"Ad: %s\n",(pArr+c)->hesapAdi);
            fprintf(fp_new,"HesapNo: %d\n",(pArr+c)->hesapNo);
            fprintf(fp_new,"MusteriNo: %d\n",(pArr+c)->musteriNo);
            fprintf(fp_new,"Bakiye: %.2fd\n",(pArr+c)->bakiye);
        }
    }
    fclose(fp_new);
    fclose(fp_old);
//    HesapEkle("Yeni_Dosya.txt",updated,guncelle); // guncellenecek deger yeni klasore yeni kayit gibi ekleniyor
    remove(DosyaAdi);
    rename("Yeni_Dosya.txt",DosyaAdi); // Yeni dosyamiza asil dosyamizin adini veriyoruz
    printf("Kayit Guncellendi!\n");
}
int HesapBul(char *DosyaAdi,int musteriNo,int duzenle,int miktar, int hesapNo)
{
    /*
        Duzenle Parametresi isim ile kayit bulma ve kayit duzenleme bolumunde ayni fonksiyon kullanildigi icin cagirildigi yere gore tepki vermesi icindir.
    */
    FILE *fp;
    Musteri *pArr,Kisi[MAX];
    pArr = &Kisi;
    char nameTag[20],kodTag[20],noTag[20],lengthTag[20], tipTag[20];
    fp = fopen(DosyaAdi,"r+");
    int kayitBulunan[MAX];
    int FlagOne = 0,i = 0,c = 0,kayitNo;
    bool isEqual;
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp," %s %s ",nameTag,&(pArr+i)->Ad);
            fscanf(fp," %s %s ",kodTag,&(pArr+i)->Soyad);
            fscanf(fp," %s %d ",noTag,&(pArr+i)->musteriNo);
            fscanf(fp," %s %d ",lengthTag,&(pArr+i)->hesapSayisi);
            fscanf(fp," %s %d ",tipTag,&(pArr+i)->tip);
            isEqual = ((pArr+i)->musteriNo == musteriNo);
            if(isEqual)
            {
                printf("\n%d. Kayit:\n%s %s\n%s %d\n%s %d\n%s %d\n%s %d\n",i+1,nameTag,(pArr+i)->Ad,kodTag,(pArr+i)->Soyad,noTag,(pArr+i)->musteriNo,lengthTag,(pArr+i)->hesapSayisi,(pArr+i)->tip);
                kayitBulunan[c]=i;
                c++;
                FlagOne++;
            }
            i++;
        }
        if(FlagOne != 0)
        {
            fclose(fp);
            printf("\n%d Kayit bulundu.\n",FlagOne);
            if(duzenle == 1) // Eger Duzenleme Bolumunde Cagirilmissa fonksiyon duzenleme degeri 1 olarak gonderildigi icin bu blok calisir
            {
                HesapGuncelle("hesap.txt", kayitBulunan,hesapNo);
                return 1; // 1 dondurulurse Kayit Bulundugunda yapilacak islem sirasini takip etmesi icin Main fonksiyonuna yansitilir
            }
        }
        else{
            fclose(fp);
            printf("\nKayit Bulunamadi.\n");
            return 0; // 0 dondurulurse Kayit Bulundugunda yapilacak islem sirasini takip etmesi icin Main fonksiyonuna yansitilir
        }
    }
    else{
        printf("Okuma islemi basarisiz oldu!\n");
        exit(1);
    }
}
