#include <stdio.h>
#include <stdlib.h>
#include <locale.h>//turkce karakter kullanmak icin kullanilmistir...
#include <windows.h>//konsoldaki yazi renkleri icin kullanilmistir...
#include <conio.h>//konsol ekranini temizlemek icin gereken fonksiyonlar icin kullanilmistir...

typedef struct labirent{
    int veri;
    struct labirent *sonraki;
}matris;

typedef struct iz{
    int i;
    int j;
    struct iz* sonraki;
}yol;

matris* root=NULL;
matris* iter=NULL;
yol* kok=NULL;
int satir,sutun,x,y,g_satir,g_sutun,c_satir,c_sutun;

void labirent_yap(){
    int i;
    srand(time(NULL));
    for(i=0;i<(satir*sutun);i++){
        labirente_ekle((rand()%2));
    }
    labirent_yazdir();
}

void labirente_ekle(int veri){
    matris* yeni_dugum=(matris*)malloc(sizeof(matris*));
    yeni_dugum->veri=veri;
    yeni_dugum->sonraki=NULL;
    if(root==NULL){
        root=iter=yeni_dugum;
    }
    else{
       iter->sonraki=yeni_dugum;
       iter=iter->sonraki;
    }
}

void labirent_yazdir(){
    int i=0;
    iter=root;
    printf("\t\t");
    while(iter){
        printf("%-6d",iter->veri);
        iter=iter->sonraki;
        i++;
        if(i==sutun){i=0;printf("\n\t\t");}
    }
}

int veri_al(int i,int j){/** (istenilen Satir-1)*Sutun+istenilen Sutun **/
    int veri,k=1,kosul;
    kosul=(i-1)*sutun+j;
    iter=root;
    while(iter){
        veri=iter->veri;
        iter=iter->sonraki;
        if(k==kosul)break;
        k++;
    }
    return veri;
}

void veri_degis(int i,int j,int deger){
    int k=1,kosul;
    kosul=(i-1)*sutun+j;
    iter=root;
    while(iter){
        if(k==kosul)break;iter=iter->sonraki;
        k++;
    }
    iter->veri=deger;
}

void yola_ekle(int i,int j){
    yol* yeni_dugum=(yol*)malloc(sizeof(yol*));
    yeni_dugum->i=i;
    yeni_dugum->j=j;
    yeni_dugum->sonraki=kok;
    kok=yeni_dugum;
}

void yoldan_al(){
    if(kok==NULL)return;
    yol* alinacak=kok;
    kok=kok->sonraki;
    x=alinacak->i;
    y=alinacak->j;
    free(alinacak);
}

void labirenti_coz(){
    int kontrol=0;
    while(1){
        if( y!=c_sutun || x!=c_satir){

            if(veri_al(x,y)==1){/**ilk veri kontrolu**/
                yola_ekle(x,y);veri_degis(x,y,2);
            }
            else if(veri_al(x,y)==2){/**Diger olasiliklarin kontrolu**/

                if(asagi(x+1,y)){x++;yola_ekle(x,y);veri_degis(x,y,2);}
                else if(saga(x,y+1)){y++;yola_ekle(x,y);veri_degis(x,y,2);}
                else if(yukari(x-1,y)){x--;yola_ekle(x,y);veri_degis(x,y,2);}
                else if(sola(x,y-1)){y--;yola_ekle(x,y);veri_degis(x,y,2);}
                else {veri_degis(x,y,3);yoldan_al();}
            }
            else if(veri_al(x,y)==3){if(kok!=NULL)yoldan_al();else {kontrol=1;break;}}
            else {kontrol=1;break;}


        }else{
            printf("Tebrikler Labirentten Cikis Bulundu...\n");
            printf("\n\t\t  Labirentten Cikis Yolu\n");
            printf("\t\t-------------------------------\n");
            cozulmus_labirenti_yazdir();
            break;}
    }
    if(kontrol==1)printf("Labirentte Olasi Yol Bulunamamistir...\n");

}

void cozulmus_labirenti_yazdir(){
    HANDLE  renk;
    renk= GetStdHandle(STD_OUTPUT_HANDLE);
    WORD ilk_renk;
    CONSOLE_SCREEN_BUFFER_INFO console_bilgisi;
    GetConsoleScreenBufferInfo(renk, &console_bilgisi);
    ilk_renk = console_bilgisi.wAttributes;
     int i=0;
    iter=root;
    printf("\t\t");
    while(iter){
        if(iter->veri==2){iter->veri=1;SetConsoleTextAttribute(renk, FOREGROUND_BLUE);printf("%-6d",iter->veri);}
        else {iter->veri=0;SetConsoleTextAttribute ( renk,ilk_renk);printf("%-6d",iter->veri);}
        iter=iter->sonraki;
        i++;
        if(i==sutun){i=0;printf("\n\t\t");}
    }
    SetConsoleTextAttribute ( renk,ilk_renk);
    /**
    Fonksiyondaki yazý rengi kodlari
    "https://iamhunger.wordpress.com/2012/03/13/c-de-renkli-yazi-yazma/"
    sitesinden alinmis ve uyarlanmistir.
    **/
}

int saga(int i,int j){
    if(j>=1 && j<=sutun && veri_al(i,j)==1)return 1;
    else return 0;
}

int asagi(int i,int j){
    if(i>=1 && i<=satir && veri_al(i,j)==1)return 1;
    else return 0;
}

int yukari(int i,int j){
    if(i>=1 && i<=satir && veri_al(i,j)==1)return 1;
    else return 0;
}

int sola(int i,int j){
    if(j>=1 && j<=satir && veri_al(i,j)==1)return 1;
    else return 0;
}

int main()
{
    char c;int s,e1,e2;
    setlocale(LC_ALL,"Turkish");
    do{
      system("cls");
    printf("\t\t   |Labirent Cozme Oyununa Hosgeldiniz|\n");
    printf("\t\t------------------------------------------\n");

    do{
    printf("Labirent Oyunu icin Labirent Boyutunu Giriniz;\n\tLabirentin Satir Sayisi:");
    scanf("%d",&satir);
    if(satir>25){printf("Ekran Boyutunu Asacagi icin Lutfen Satir Bilgisini Tekrar Giriniz!!!\n\n");e1=1;}  else e1=0;
    }while(e1);

    do{
    printf("\tLabirentin Sutun Sayisi:");
    scanf("%d",&sutun);
    if(satir>25){printf("Ekran Boyutunu Asacagi icin Lutfen Sutun Bilgisini Tekrar Giriniz!!!\n\n");e2=1;}  else e2=0;
    }while(e2);

    labirent_yap();
    printf("\n\nLabirent Oyunu icin Labirente Giris ve Cikis Kapilarini Giriniz;\n\tGiris:");
    scanf("%d %d",&g_satir,&g_sutun);
    while(1){
            if((g_satir>=1 && g_satir<=satir) && (g_sutun>=1 && g_sutun<=sutun))
                if((g_satir==1 && g_sutun<=sutun) || (g_sutun==1 && g_satir<=satir)|| (g_satir==satir && g_sutun<=sutun)|| (g_sutun==sutun && g_satir<=satir))break;
                else {printf("Giris Kapisi Labirentin Kenarlar Koselerinden Olmalidir!!! Lutfen Tekrar Giriniz...\n\tGiris:");
                    scanf("%d %d",&g_satir,&g_sutun);continue;}
            else {printf("Girilen Giris Degerleri Satir icin:[1-%d] / Sutun icin:[1-%d] Arasinda Olmalidir!!! Lutfen Tekrar Giriniz...\n\tGiris:",satir,sutun);
                  scanf("%d %d",&g_satir,&g_sutun);
                 }
            }
    printf("\tCikis:");
    scanf("%d %d",&c_satir,&c_sutun);
    while(1){
            if((c_satir>=1 && c_satir<=satir) && (c_sutun>=1 && c_sutun<=sutun)){
                if((c_satir==1 && c_sutun<=sutun) || (c_sutun==1 && c_satir<=satir)|| (c_satir==satir && c_sutun<=sutun)|| (c_sutun==sutun && c_satir<=satir))
                    if(g_satir!=c_satir || g_sutun!=c_sutun)break;
                    else {printf("Giris ve Cikis Kapilari Esit Olamaz!!! Lutfen Tekrar Giriniz...\n\tCikis:");
                          scanf("%d %d",&c_satir,&c_sutun);continue;}
                else {printf("Cikis Kapisi Labirentin Kenarlar Koselerinden Olmalidir!!! Lutfen Tekrar Giriniz...\n\tCikis:");
                      scanf("%d %d",&c_satir,&c_sutun);continue;}
            }
            else {printf("Girilen Cikis Degerleri Satir icin:[1-%d] / Sutun icin:[1-%d] Arasinda Olmalidir!!! Lutfen Tekrar Giriniz...\n\tCikis:",satir,sutun);
                  scanf("%d %d",&c_satir,&c_sutun);
                 }
            }

    x=g_satir;y=g_sutun;
    labirenti_coz();
     printf("\nLabirent Oyununu Tekrar Oynamak Ister misiniz? (e/h):");
     fflush(stdin);
     scanf("%c",&c);
     if(c=='e' || c=='E'){//Eger kullanici tekrar oyun oynamak isterse bagintili listeleremizdeki elemanlari sildirme islemi yapmaliyiz...
        while(kok!=NULL)yoldan_al();
        while(root!=NULL){
            matris* yeni=(matris*)malloc(sizeof(matris));
            yeni=root;
            root=root->sonraki;
            free(yeni);
        }
        s=1;
     }
     else s=0;

    }while(s);
    printf("Labirent Oyunu Sona Erdi...\n\nYapan Ogrenciler:Yakup KAMCI(160201135) / Cengiz ATILA(160201141)\n");
    return 0;
}


