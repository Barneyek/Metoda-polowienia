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


//Funkcja Hornera do szybkiego obliczania warto�ci wielomianu
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

	int stopien, maks; //nazwa maks ze wzgl�du na komplikacje (w c++ max jest oddzielnie wbudowan� funkcj�)

	//wczytanie poszceg�lnych  wsp�czynnik�w
	cout << "Podaj zakres poszukiwan pierwiastka:\n\n";
	cout << "Podaj poczatek rzedzialu = "; cin >> poczatekPrzedzialu;
	cout << "Podaj koniec przedzialu = "; cin >> koniecPrzedzialu;
	cout << "Podaj stopien wielomianu: "; cin>>stopien;
	cout << "Podaj maksymalna liczba iteracji obliczen: "; cin>>maks;	  
	
	//Deklaracja tablicy niezb�dnej do wczytania kazdego wspolczynnika potegi   
  	//Jako �e tablica zaczyna si� od 0 dodajemy do zmiennej stopie� +1, aby by�a r�wna    
  	double* wspolczynniki = new double [stopien+1];
  	
	//P�tla niebzedna do wczytania kazdego wspolczynnika potegi
	//Wykona si� tyle razy, a� b�dzie r�wna stopniowi	
	//Zapyta o ka�dy wsp�czynnik wielomianu np. jaki wsp�lczynnik stoi przed x^3
	for(int i=0;i<=stopien;i++){
	    cout<<"Podaj wspolczynnik stojacy przy potedze "<<stopien-i<<": ";
	    cin>>wspolczynniki[i];
	}
	
  	cout << "Podaj dokladnosc obliczanej wartosci pierwiastka funkcji: "; cin>>eps;
  	cout << "\n---------------------------------\n\n"
          "WYNIK:\n\n";


	//wywo�anie funckji hornera:
	//Dla zmiennej wartoscFunkcjipoczatkowej przeka�e tablice wsp�czynnik�w, stopie� oraz pocz�tek przedzia�u
	//Analogicznie dla ko�ca tak samo
 	wartoscFunkcjiPrzedzialuPoczatkowego = horner(wspolczynniki, stopien, poczatekPrzedzialu);
  	wartoscFunkcjiPrzedzialuKoncowego = horner(wspolczynniki, stopien, koniecPrzedzialu);

	//Sprawdzenie warunku r�nych znak�w warto�ci funkcji na kra�cach zakresu poszukiwa� pierwiastka
  	if(wartoscFunkcjiPrzedzialuPoczatkowego * wartoscFunkcjiPrzedzialuKoncowego > 0) {
    	cout << "Funkcja nie spelnia zalozen\n";
  	} else {
  		//zmienna dodatkowa do por�wnywania z liczb� iteracji
      	int licznik = 0;
    
    	//P�tla wyliczania kolejnych przybli�e� pierwiastka funkcji. P�tla trwa, a� przedzia� poszukiwa� pierwiastka osi�gnie d�ugo�� Epslion.
   		while(fabs(poczatekPrzedzialu - koniecPrzedzialu) > eps) {
	       		if(licznik > maks){
	            	cout << "Przekroczono maksymalna liczbe iteracji obliczen\n";
	           		return 0;
	       		}
	       		
				//Wewn�trz p�tli wyznaczamy punkt (pierwiastekFunkcji) le��cy w �rodku przedzia�u oraz obliczamy warto�� funkcji  
		        pierwiastekFunkcji = (poczatekPrzedzialu + koniecPrzedzialu) / 2;
		        
		        // Obliczamy f. Hornera warto�c pierwiastka funkcji oraz przypisujemy j� do zmiennej wartoscFunkcjiMiejscaZerowego
		        wartoscFunkcjiMiejscaZerowego = horner(wspolczynniki, stopien, pierwiastekFunkcji);
				
				//Je�li warto�� wartoscFunkcjiMiejscaZerowego jest dostatecznie bliska zeru przerywamy p�tle, ko�czymy algorytm i wypisujemy pierwiastekFunkcji
		        if(fabs(wartoscFunkcjiMiejscaZerowego) < eps){
		           break;
		        }
				
				//W przeciwnym razie za nowy przedzia� przyjmujemy po��wk� wyznaczon� przez wartoscFunkcjiMiejscaZerowego w kt�rej funkcja zmienia znak
		        if(wartoscFunkcjiPrzedzialuPoczatkowego * wartoscFunkcjiMiejscaZerowego < 0){
		        	
		        	//Je�li iloczyn jest ujemny, to r�ne znaki funkcja przyjmuje w po��wce <poczatekPrzedzialu, pierwiastekFunkcji>
		            koniecPrzedzialu = pierwiastekFunkcji;
		            
		        } else {
		        	
		        	//W przeciwnym wypadku funkcja przyjmuje <pierwiastekFunkcji, koniecPrzedzialu>
		            poczatekPrzedzialu = pierwiastekFunkcji;
		            
		            //Za nowy pocz�tek wartoscFunkcjiPrzedzialuPoczatkowego  przyjmujemy wartoscFunkcjiMiejscaZerowego
		            wartoscFunkcjiPrzedzialuPoczatkowego = wartoscFunkcjiMiejscaZerowego;
		            
		        }
		        
				//Po tych czynno�ciach kontynuujemy p�tl� wyznaczania kolejnych przybli�e� pierwiastka 
		        licznik++;
    	}
    cout << "Pierwiastek  funkcji nieliniowej = " << pierwiastekFunkcji << endl;
  }
  	cout << "\n---------------------------------\n\n";

  system("pause");
  return 0;
}
