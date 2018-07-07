#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

//-----------------------------------------
// Do testowania Funkcja:
// x * x * x - 3*x*x-2*x+5;
// Eps=0.1 przedzial <1,2> wynik: 1.1875
//-----------------------------------------


//Funkcja Hornera do szybkiego obliczania wartoœci wielomianu
double horner(double wsp[],int st, double x){
	if(st == 0){
		return wsp[0];
	}
	return x*horner(wsp,st-1,x)+wsp[st];
}

int main() {	
	//parametry zgodne z wymaganiami, zmiennoprzecinkowe
 	double poczatekPrzedzialu,
            koniecPrzedzialu,
            pierwiastekFunkcji,
            eps,
            wartoscFunkcjiPrzedzialuPoczatkowego,
            wartoscFunkcjiPrzedzialuKoncowego,
            wartoscFunkcjiMiejscaZerowego;

	int stopien, maks; //nazwa maks ze wzglêdu na komplikacje (w c++ max jest oddzielnie wbudowan¹ funkcj¹)

	//wczytanie poszcególnych  wspó³czynników
	cout << "Podaj zakres poszukiwan pierwiastka:\n\n";
	cout << "Podaj poczatek rzedzialu = "; cin >> poczatekPrzedzialu;
	cout << "Podaj koniec przedzialu = "; cin >> koniecPrzedzialu;
	cout << "Podaj stopien wielomianu: "; cin>>stopien;
	cout << "Podaj maksymalna liczba iteracji obliczen: "; cin>>maks;	  
	
	//Deklaracja tablicy niezbêdnej do wczytania kazdego wspolczynnika potegi   
  	//Jako ¿e tablica zaczyna siê od 0 dodajemy do zmiennej stopieñ +1, aby by³a równa    
  	double* wspolczynniki = new double [stopien+1];
  	
	//Pêtla niebzedna do wczytania kazdego wspolczynnika potegi
	//Wykona siê tyle razy, a¿ bêdzie równa stopniowi	
	//Zapyta o ka¿dy wspó³czynnik wielomianu np. jaki wspólczynnik stoi przed x^3
	for(int i=0;i<=stopien;i++){
	    cout<<"Podaj wspolczynnik stojacy przy potedze "<<stopien-i<<": ";
	    cin>>wspolczynniki[i];
	}
	
  	cout << "Podaj dokladnosc obliczanej wartosci pierwiastka funkcji: "; cin>>eps;
  	cout << "\n---------------------------------\n\n"
          "WYNIK:\n\n";


	//wywo³anie funckji hornera:
	//Dla zmiennej wartoscFunkcjipoczatkowej przeka¿e tablice wspó³czynników, stopieñ oraz pocz¹tek przedzia³u
	//Analogicznie dla koñca tak samo
 	wartoscFunkcjiPrzedzialuPoczatkowego = horner(wspolczynniki, stopien, poczatekPrzedzialu);
  	wartoscFunkcjiPrzedzialuKoncowego = horner(wspolczynniki, stopien, koniecPrzedzialu);

	//Sprawdzenie warunku ró¿nych znaków wartoœci funkcji na krañcach zakresu poszukiwañ pierwiastka
  	if(wartoscFunkcjiPrzedzialuPoczatkowego * wartoscFunkcjiPrzedzialuKoncowego > 0) {
    	cout << "Funkcja nie spelnia zalozen\n";
  	} else {
  		//zmienna dodatkowa do porównywania z liczb¹ iteracji
      	int licznik = 0;
    
    	//Pêtla wyliczania kolejnych przybli¿eñ pierwiastka funkcji. Pêtla trwa, a¿ przedzia³ poszukiwañ pierwiastka osi¹gnie d³ugoœæ Epslion.
   		while(fabs(poczatekPrzedzialu - koniecPrzedzialu) > eps) {
	       		if(licznik > maks){
	            	cout << "Przekroczono maksymalna liczbe iteracji obliczen\n";
	           		return 0;
	       		}
	       		
				//Wewn¹trz pêtli wyznaczamy punkt (pierwiastekFunkcji) le¿¹cy w œrodku przedzia³u oraz obliczamy wartoœæ funkcji  
		        pierwiastekFunkcji = (poczatekPrzedzialu + koniecPrzedzialu) / 2;
		        
		        // Obliczamy f. Hornera wartoœc pierwiastka funkcji oraz przypisujemy j¹ do zmiennej wartoscFunkcjiMiejscaZerowego
		        wartoscFunkcjiMiejscaZerowego = horner(wspolczynniki, stopien, pierwiastekFunkcji);
				
				//Jeœli wartoœæ wartoscFunkcjiMiejscaZerowego jest dostatecznie bliska zeru przerywamy pêtle, koñczymy algorytm i wypisujemy pierwiastekFunkcji
		        if(fabs(wartoscFunkcjiMiejscaZerowego) < eps){
		           break;
		        }
				
				//W przeciwnym razie za nowy przedzia³ przyjmujemy po³ówkê wyznaczon¹ przez wartoscFunkcjiMiejscaZerowego w której funkcja zmienia znak
		        if(wartoscFunkcjiPrzedzialuPoczatkowego * wartoscFunkcjiMiejscaZerowego < 0){
		        	
		        	//Jeœli iloczyn jest ujemny, to ró¿ne znaki funkcja przyjmuje w po³ówce <poczatekPrzedzialu, pierwiastekFunkcji>
		            koniecPrzedzialu = pierwiastekFunkcji;
		            
		        } else {
		        	
		        	//W przeciwnym wypadku funkcja przyjmuje <pierwiastekFunkcji, koniecPrzedzialu>
		            poczatekPrzedzialu = pierwiastekFunkcji;
		            
		            //Za nowy pocz¹tek wartoscFunkcjiPrzedzialuPoczatkowego  przyjmujemy wartoscFunkcjiMiejscaZerowego
		            wartoscFunkcjiPrzedzialuPoczatkowego = wartoscFunkcjiMiejscaZerowego;
		            
		        }
		        
				//Po tych czynnoœciach kontynuujemy pêtlê wyznaczania kolejnych przybli¿eñ pierwiastka 
		        licznik++;
    	}
    cout << "Pierwiastek  funkcji nieliniowej = " << pierwiastekFunkcji << endl;
  }
  	cout << "\n---------------------------------\n\n";

  system("pause");
  return 0;
}
