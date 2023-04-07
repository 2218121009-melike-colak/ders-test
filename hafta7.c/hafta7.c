#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void diziSiralaKucuktenBuyuge(int *dizi, int elemanSayisi);
void medyanbul(int *dizi, int elemanSayisi, double *medyanptr);

void hafta7_fonk(int dizi[], int elemanSayisi, int yuzdelikDeger, double *Q1ptr, double *Q3ptr, double *IQRptr,
            double *OrtPtr, double *ptr_esikDegeri_Alt, double *ptr_esikDegeri_Ust,
            int *islemeAlinanDegerlerFlag, double *ptr_IADT, int *ptrArray[])
{

    //Fonksiyon cagirma
    diziSiralaKucuktenBuyuge(dizi,elemanSayisi);
    double medyan;
    medyanbul(dizi,elemanSayisi,&medyan);


    //Degiskenler
    double Q1,Q3,IQR;
    int altindis, ustindis;
    //Alt ve ust indis hesaplama
    altindis = (elemanSayisi-1)/4;
    ustindis= 3*(elemanSayisi-1)/4;
    //Q1, Q3,IQR hesaplama
    Q1=(dizi[altindis]+dizi[altindis+(elemanSayisi% 2)])/2;
    Q3=(dizi[ustindis]+dizi[ustindis+(elemanSayisi% 2)])/2+1;
    IQR=abs(Q3-Q1);                                               // IQR degerimizin pozitif cikmasi icin mutlak deger aliyoruz.

    *Q1ptr=Q1;  //Burada degiskenlerimizin bellek adreslerini isaretcilerin tutmasi icin atama islemi yapiyoruz.
    *Q3ptr=Q3;
    *IQRptr=IQR;

    int i;
    for(i=0; i<elemanSayisi; i++)
    {
        if(dizi[i]<Q1-(1.5*IQR) || dizi[i]>Q3+(1.5*IQR))   //ic ve dis sinirlari hesaplayarak uc degerleri diziden cikarma islemi
             islemeAlinanDegerlerFlag[i]=0;
        else
            islemeAlinanDegerlerFlag[i]=1;
    }
    *islemeAlinanDegerlerFlag=islemeAlinanDegerlerFlag;   //islemeAlinanDegerlerFlag degiskenimizi isaretciye atama

    double toplam1=0;
    double ortalama=0;
    int kisisayisi;
    for(i=0; i<elemanSayisi; i++)
    {
        if(islemeAlinanDegerlerFlag[i]==1)   //aykiri olmayan degerleri alarak dongu icinde toplam degeri hesaplama
        {
            toplam1+=dizi[i];
            kisisayisi++;  //aykiri olmayan deger sayisini bu sayacla tutuyoruz.
        }
    }
    ortalama=toplam1/kisisayisi;
    *OrtPtr=ortalama;    //aykiri olmayan degerlerin ortalama hesabi

    double yuzdelikAralik,altEsikdegeri,ustEsikdegeri;

    yuzdelikAralik=ortalama*yuzdelikDeger/100;
    altEsikdegeri=ortalama-yuzdelikAralik;
    ustEsikdegeri=ortalama+yuzdelikAralik;

    *ptr_esikDegeri_Alt=altEsikdegeri;     //ust satirlarda hesaplanan alt ve ust esik degerlerinin bellek adreslerini tutmak uzere atama
    *ptr_esikDegeri_Ust=ustEsikdegeri;

    double toplam2;
    int kisisayisi1=0;
    for(i=0; i<elemanSayisi; i++)
    {
        if(dizi[i]>=altEsikdegeri && dizi[i]<=ustEsikdegeri) //isleme alinan degerler dizisini esik degerleriyle sinirlayarak guncelliyoruz
        {
            islemeAlinanDegerlerFlag[i]=1;
            toplam2+=dizi[i];
            kisisayisi1++;
        }
    }
    *ptr_IADT=toplam2; //aykiri olmayan degerler toplamini isaretciye atama




    for(i=0; i<elemanSayisi; i++)  //ptrArray dizisinin elemanlarýný baslangic olarak NULL degerine atama
    {
        ptrArray[i]=NULL;
    }

    for(i=0; i<elemanSayisi; i++)
    {
        if(dizi[i]>=altEsikdegeri && dizi[i]<=ustEsikdegeri)  //esik degerler arasindaki dizi degerlerini kosul olarak aldik
        {
            if(dizi[i]!=dizi[i-1] || i==0)                    //daha sonraki kosulumuz ise ayni degere sahip olmayan ilk essiz degerleri bulmak
            {                                                   /*son olarak da bu iki kosulu saglayan dizi degerlerinin adreslerini ptArray
                                                            dizisinin ayni indisteki bölgesine atama islemi yapiyoruz.*/
                ptrArray[i]=&dizi[i];
            }
        }
    }


}

void diziSiralaKucuktenBuyuge(int *dizi, int elemanSayisi)
{
   int i,pass,temp;

   for(pass=1; pass<elemanSayisi; pass++)
   {
       for(i=0; i<elemanSayisi-1; i++)
       {
           if(dizi[i]>dizi[i+1])     //swap
           {
               temp=dizi[i];
               dizi[i]=dizi[i+1];
               dizi[i+1]=temp;
           }
       }
}
}

void medyanbul(int *dizi, int elemanSayisi, double *medyanptr)
{
   diziSiralaKucuktenBuyuge(dizi,elemanSayisi);
   double medyan;
   *medyanptr=medyan;

   if(elemanSayisi%2==0)
   {
       *medyanptr=(double)((dizi[elemanSayisi/2-1]+dizi[elemanSayisi/2]))/2;
   }
   else
   {
       *medyanptr=dizi[elemanSayisi/2];
   }


}


