#include <iostream>
#include <fstream>
#include<sstream>

using namespace std;

//Kisi.txt dosyas�ndaki verilerin tutulacagi kisi class'�
class kisi {
private:
	int id;
	string ad;
	char cins;
	int mah;
	int yas;
	bool c19;
	bool kronik;
	bool disari;

public:
	//parametresiz kurucu metod
	kisi() {
	}
	//parametreli kurucu metod
	/*kisi(int _id,string _ad,char _cins,int _mah,int _yas,bool _c19,bool _kronik, bool _disari){
		id=_id;
		ad=_ad;
		cins=_cins;
		mah=_mah;
		yas=_yas;
		c19=_c19;
		kronik=_kronik;
		disari=_disari;

	}*/
	~kisi() {
	}
	//kullanacak oldu�um getter metodlar�
	int getYas() {
		return yas;
	}
	bool getKronik() {
		return kronik;
	}
	int getId() {
		return id;
	}
	string getAd() {
		return ad;
	}
	int getmah() {
		return mah;
	}
	bool getC19() {
		return c19;
	}
	bool getDisari() {
		return disari;
	}

	//elemanAta fonkiyonunda kullan�lacak olan metod
	void	ayarla(int _id, string _ad, char _cins, int _mah, int _yas, bool _c19, bool _kronik, bool _disari) {
		id = _id;
		ad = _ad;
		cins = _cins;
		mah = _mah;
		yas = _yas;
		c19 = _c19;
		kronik = _kronik;
		disari = _disari;

	}
	//nesneyi ekrana ��kt� almaya yarayan metod	
	void	print() {
		cout << id << " " << ad << " " << cins << " " << mah << " " << yas << " " << c19 << " " << kronik << " " << disari << endl;
	}
};

//Heryerden eri�im sa�lamak amac�yla olu�turulmu� global nesne
kisi kisiler[50];

//dinamik bellek kullanma amac�yla ve heryerden eri�im sa�lama amac�yla olu�turulmu� global pointer dizileri ve de�i�kenler
int** imatris, *** ematris, ** maske;
int satir, sutun, maskeSutun;
float* riskPuani, ** riskPuani2, * yasKatsayisi, * kronikKatsayisi, ** toplamEtkilesim, * mahalleRisk, ** mahalleRisk2;

int stoi(const string);
int virgul_sil(string&);
void satirSutunOku(const char*);
void matrisOkuma(int***, const char*, int, bool);
void matrisPrint(int**, int);
void matrisPrint(float**, int);

//void maskeOkuma(int matris[50][4],const char *arr)
void elemanAta();
void dosyaOku();
void iliskiDerecesiGoster(int, int);
void iliskiDerecesiGoster();
void bellekAta();
void etkilesimPuaniHesapla();
float etkilesimPuaniHesapla(int, int);
void etkilesimGrafOlustur();
int etkilesimKatsayi(int, int, int);
float iliskiKatsayi(int, int);
int maskeKatsayi(int, int);
void riskPuaniHesapla();
void yasKatsayiHesapla();
void kronikRahatsizlikKatsayisi();
void riskPuaniHesapla(int);
void mahalleRiskPuanHesapla();
void mahalleRiskPrint();
int mahalleSayisi();
void genelSiralama();
void genelSiralamaPrint();
void mahalleBulasmaRiskiSiralama();
void quicksort(float**, int, int);
float partition(float**, int, int);
void temasliKisileriBul();
void ilkVakaTespit();
int main() {

	setlocale(LC_ALL, "Turkish");
	elemanAta();
	bellekAta();
	dosyaOku();

	etkilesimGrafOlustur();

	riskPuaniHesapla();
	mahalleRiskPuanHesapla();

	genelSiralama();
	genelSiralamaPrint();
	mahalleBulasmaRiskiSiralama();
	temasliKisileriBul();
	ilkVakaTespit();



	return 0;
}

//dosyadan okunan string de�eri integer de�ere �eviren fonksiyon
int stoi(const string s) {
	stringstream ss(s);

	int x;

	ss >> x;

	return x;
}
//dosyadaki virgulleri silerek bo�lu�a �eviren ve virgul say�s�n� d�nd�ren fonksiyon
int virgul_sil(string& s) {
	int virgulSayisi = 0;
	int	l = s.length();
	for (int i = 0; i < l; i++)
	{
		if (s[i] == ',') {
			virgulSayisi++;
			s[i] = ' ';
		}
	}
	return virgulSayisi;
}
//dosyan�n sat�r say�s� ve sutun say�s�n� hesaplayan fonksiyon 
void satirSutunOku(const char* arr, int& stn) {
	satir = 0;
	fstream dosya(arr, ios::in);
	string temp;
	while (getline(dosya, temp)) {
		satir++;
	}
	stn = virgul_sil(temp) + 1;

}
//parametre olarak karakter dizisindeki txt dosyas�n� okuyan ve de�erlerini matrise atayan fonksiyon
//mod parametresimaske txt dosyas�ndaki ba�ta verilmi� olan idleri kullanmamak i�in olu�turulmu�tur	
void matrisOkuma(int** matris, const char* arr, int sutun, bool mod = 0) {

	fstream dosya(arr, ios::in);
	string temp;
	int sayac = 0;
	while (getline(dosya, temp)) {
		virgul_sil(temp);
		stringstream ss(temp);
		if (mod == true) {
			int tmp;
			//cout<<temp<<endl;
			ss >> tmp;

		}
		for (int i = 0; i < sutun; i++) {
			char c;

			ss >> c;

			if (c != '-') {

				matris[sayac][i] = c - 48;//c karaktesine at�lan de�erin 48 eksi�ini alarak asci tablosuna g�re i�lem yap�lmaktad�r

			}
			else
				matris[sayac][i] = 999;//okunan matristeki '-' ile belirtilen yerlere bo� de�er olarak 999 atanm��t�r

		}


		sayac++;
	}
}

//parametre olarak verilen integer matrisi ekrana bast�ran fonksiyon 
void matrisPrint(int** matris, int sutun) {

	for (int i = 0; i < satir; i++) {
		for (int j = 0; j < sutun; j++) {
			cout << matris[i][j] << " ";
		}
		cout << endl;
	}



}
//parametre olarak verilen float matrisi ekrana bast�ran overload edilmi� fonksiyon 
void matrisPrint(float** matris, int sutun) {

	for (int i = 0; i < satir; i++) {
		for (int j = 0; j < sutun; j++) {
			cout << matris[i][j] << " ";
		}
		cout << endl;
	}



}
//kisiler.txt dosyas� okunarak olu�turdu�umuz nesnelere de�er atamalar� yap�l�r
void elemanAta() {
	fstream dosya("kisiler.txt", ios::in);
	string temp;

	int oSayac = 0;
	while (getline(dosya, temp)) {
		int i = 1;
		virgul_sil(temp);

		stringstream ss(temp);
		int dizi[6];//6 tane �zelli�imiz oldu�u i�in onlar� tutan dizi
		string a;
		char arr;
		ss >> dizi[0] >> a >> arr;
		while (ss >> dizi[i++]);

		kisiler[oSayac].ayarla(dizi[0], a, arr, dizi[1], dizi[2], dizi[3], dizi[4], dizi[5]);
		oSayac++;
	}

}
//bize verilmi� olan dosyalar� okuyarak matrislere atayarak graf olu�turan fonksiyon 
void dosyaOku() {


	matrisOkuma(imatris, "iliski.txt", sutun);

	matrisOkuma(ematris[0], "etkilesim1.txt", sutun);
	matrisOkuma(ematris[1], "etkilesim2.txt", sutun);
	matrisOkuma(ematris[2], "etkilesim3.txt", sutun);
	matrisOkuma(ematris[3], "etkilesim4.txt", sutun);

	matrisOkuma(maske, "maske.txt", maskeSutun - 1, 1);


}
//d��ar�dan parametre alarak ili�ki derecesini g�steren fonksiyon 
void iliskiDerecesiGoster(int x, int y) {


	cout << imatris[x][y] << endl;


}
//parametreyi kullan�c�dan alarak ili�ki derecesini g�steren overload edilmi� fonksiyon 
void iliskiDerecesiGoster() {
	int x, y;
	cout << "Lutfen kaynak kisinin id giriniz" << endl;
	cin >> x;
	cout << "Lutfen hedef kisinin id giriniz" << endl;
	cin >> y;

	//dizi indisleri 101'den de�il 0'dan ba�lad��� i�in verilen de�erin 101 eksi�i ile i�lem yap�l�r 
	x -= 101;
	y -= 101;


	iliskiDerecesiGoster(x, y);



}

//pointer olarak olu�turdu�umuz dizilere bellek atamas�n�n yap�ld��� fonksiyon 
//dosyalardan satir ve sutun say�lari okunarak bulunan de�erlere g�re diziler olu�turulur
void bellekAta() {

	satirSutunOku("iliski.txt", sutun);
	imatris = new int* [satir];
	for (int i = 0; i < satir; i++) {
		imatris[i] = new int[sutun];
	}

	satirSutunOku("maske.txt", maskeSutun);
	maske = new int* [satir];
	for (int i = 0; i < satir; i++) {
		maske[i] = new int[maskeSutun - 1];
	}


	ematris = new int** [4];
	satirSutunOku("etkilesim1.txt", sutun);
	for (int i = 0; i < 4; i++) {
		ematris[i] = new int* [satir];
		for (int j = 0; j < satir; j++) {
			ematris[i][j] = new int[sutun];
		}
	}

	toplamEtkilesim = new float* [satir];
	for (int i = 0; i < satir; i++) {
		toplamEtkilesim[i] = new float[sutun];
	}

	riskPuani2 = new float* [satir];
	for (int i = 0; i < satir; i++) {
		riskPuani2[i] = new float[2];
	}

	mahalleRisk2 = new float* [mahalleSayisi()];
	for (int i = 0; i < mahalleSayisi(); i++) {
		mahalleRisk2[i] = new float[2];
	}


	riskPuani = new float[satir];

	yasKatsayisi = new float[50];
	kronikKatsayisi = new float[50];

	mahalleRisk = new float[mahalleSayisi()];
}

//parametreler kullan�c� taraf�ndan al�narak etkile�im puan�n� hesaplayan fonksiyon 
void etkilesimPuaniHesapla() {
	int x, y;
	cout << "Etkilesimini hesaplamak istediginiz kisinin ID'sini giriniz" << endl;
	cin >> x;
	cout << x << " Kisisinin kim ile olan etkilesimini hesaplamak istiyorsunuz" << endl;
	cin >> y;
	float toplam = 0;
	cout << x << " ile " << y << " kisisinin etkilesim puani=";

	cout << etkilesimPuaniHesapla(x, y) << endl;


}
//parametre olarak ald��� idlerin etkile�imlerini hesaplayan fonksiyon
float etkilesimPuaniHesapla(int x, int y) {
	if (x > 100 && y > 100) {
		x -= 101;
		y -= 101;
	}

	float toplam = 0;
	for (int i = 0; i < 4; i++) {

		toplam += etkilesimKatsayi(x, y, i) * iliskiKatsayi(x, y) * maskeKatsayi(x, i);


	}

	return toplam;
}
//etkile�im katsay�lar�n� return eden fonksiyon	
int etkilesimKatsayi(int x, int y, int k) {

	if (ematris[k][x][y] == 1) {

		return 1;

	}
	else
		return 0;

}
//ili�ki katsay�lar�n� return eden fonksiyon
float iliskiKatsayi(int x, int y) {

	if (imatris[x][y] == 0)
		return 1;
	else if (imatris[x][y] == 1)
		return 1.2;
	else if (imatris[x][y] == 2)
		return 1.5;
	else if (imatris[x][y] == 3)
		return 1.9;
}
//maske katsay�s�n� return eden fonksiyon
int maskeKatsayi(int x, int k) {
	if (maske[x][k] == 0)
		return 3;
	else
		return 1;
}
//Hesaplanan etkile�im puanini matrise �evirerek graf olu�turan fonksiyon
void etkilesimGrafOlustur() {

	for (int i = 0; i < satir; i++) {
		for (int j = 0; j < sutun; j++) {
			toplamEtkilesim[i][j] = etkilesimPuaniHesapla(i, j);

		}
	}



}
//risk puanini hesaplayan fonksiyon
void riskPuaniHesapla() {
	//yas ve kronik rahats�zl�k katsay�lar�n� diziye atamak i�in �a��r�d��m�z fonksiyonlar
	yasKatsayiHesapla();
	kronikRahatsizlikKatsayisi();


	for (int i = 0; i < satir; i++) {
		for (int j = 0; j < sutun; j++) {

			riskPuani[i] += yasKatsayisi[i] * kronikKatsayisi[i] * toplamEtkilesim[i][j];


		}
	}



}
//id numaras� verilen ki�inin risk puan�n� hesaplanan matristen �eken ve ard�ndan bast�ran overload edilmi� fonksiyon 
void riskPuaniHesapla(int x) {
	riskPuaniHesapla();
	x -= 101;
	cout << x + 101 << "ID'li 'kisinin risk puani: " << riskPuani[x];


}

//nesneden al�nan yas bilgilerine g�re yas katsay�lar�n� diziye atayan fonksiyon 
void yasKatsayiHesapla() {
	for (int i = 0; i < 50; i++) {
		if (kisiler[i].getYas() > 0 && kisiler[i].getYas() <= 5)
			yasKatsayisi[i] = 0.2;
		else if (kisiler[i].getYas() > 5 && kisiler[i].getYas() <= 20)
			yasKatsayisi[i] = 0.5;
		else if (kisiler[i].getYas() > 20 && kisiler[i].getYas() <= 55)
			yasKatsayisi[i] = 1;
		else if (kisiler[i].getYas() > 55 && kisiler[i].getYas() <= 75)
			yasKatsayisi[i] = 1.7;
		else if (kisiler[i].getYas() > 75)
			yasKatsayisi[i] = 2;

	}

}
//nesneden al�nan kronik rahats�zl�k bilgilerine g�re katsay�y� diziye atayan fonksiyon
void kronikRahatsizlikKatsayisi() {
	for (int i = 0; i < 50; i++) {
		if (kisiler[i].getKronik() == true)
			kronikKatsayisi[i] = 1.7;
		else
			kronikKatsayisi[i] = 1;

	}
}


//mahallede bulunan ki�ilerin risk puanlar�n� toplayarak mahallelere ait risk puan�n� bulan fonksiyon 
void mahalleRiskPuanHesapla() {
	int sayi = mahalleSayisi();
	for (int i = 0; i < sayi; i++) {
		for (int j = 0; j < satir; j++) {
			if (kisiler[j].getmah() == i + 1)
				mahalleRisk[i] += riskPuani[j];
		}
	}
}
//mahalle risk puanlar�n� bast�ran fonksiyon 
void mahalleRiskPrint() {

	for (int i = 0; i < mahalleSayisi(); i++) {
		cout << i + 1 << ". Mahallenin risk puani: " << mahalleRisk[i] << endl;
	}


}
//mahalle risk puan� hesaplan�rken kullanm�� oldu�umuz mahalle say�s�n� hesaplayarak return eden fonksiyon
int mahalleSayisi() {
	int mahalleSayi = 0;
	for (int i = 0; i < satir; i++) {
		if (kisiler[i].getmah() > mahalleSayi)
			mahalleSayi = kisiler[i].getmah();
	}

	return mahalleSayi;
}
//quicksort kullanarak id numaras� ve risk puan�n� tutan diziyi s�ralayan fonksiyon 
void genelSiralama() {

	for (int i = 0; i < satir; i++) {

		riskPuani2[i][0] = i + 101;
		riskPuani2[i][1] = riskPuani[i];

	}

	quicksort(riskPuani2, 0, 49);

}
void genelSiralamaPrint() {
	cout << "KisiId\tRiskPuani" << endl;
	for (int i = 0; i < satir; i++) {

		cout << riskPuani2[i][0] << "\t" << riskPuani2[i][1] << endl;


	}



}
//quickSort kullanarak risk puan� y�ksek olan mahalleleri s�ralayan fonksiyon
void mahalleBulasmaRiskiSiralama() {
	int sayi = mahalleSayisi();
	for (int i = 0; i < sayi; i++) {
		mahalleRisk2[i][0] = i + 1;
		mahalleRisk2[i][1] = mahalleRisk[i];

	}
	quicksort(mahalleRisk2, 0, mahalleSayisi() - 1);
}
//gerekli quicksort fonksiyonu 
void quicksort(float** Arr, int sol, int sag) {
	int pivot;
	if (sol < sag) {
		pivot = partition(Arr, sol, sag);
		quicksort(Arr, sol, pivot - 1);
		quicksort(Arr, pivot + 1, sag);
	}

}
//quicksort'ta kullan�lan partition(b�lme) fonksiyonu
float partition(float** Arr, int sol, int sag) {
	float temp[2];
	int x = Arr[sag][1];
	int i = sol - 1;

	for (int j = sol; j <= sag - 1; j++) {
		if (Arr[j][1] >= x) {
			i++;
			temp[0] = Arr[i][0];
			temp[1] = Arr[i][1];

			Arr[i][0] = Arr[j][0];
			Arr[i][1] = Arr[j][1];

			Arr[j][0] = temp[0];
			Arr[j][1] = temp[1];
		}
	}

	temp[0] = Arr[i + 1][0];
	temp[1] = Arr[i + 1][1];

	Arr[i + 1][0] = Arr[sag][0];
	Arr[i + 1][1] = Arr[sag][1];

	Arr[sag][0] = temp[0];
	Arr[sag][1] = temp[1];
	return i + 1;
}

//Covid!9 pozitif olan ki�ilerin g�nlere g�re temas etti�i ki�ileri bulup ekrana bast�ran fonksiyon 
void temasliKisileriBul() {

	for (int i = 0; i < 50; i++) {

		if (kisiler[i].getC19() == true) {
			cout << "\n\n";
			cout << "######################" << endl;
			cout << i + 101 << " kisisinin temas listesi" << endl;
			cout << "######################" << endl;
			for (int j = 0; j < 4; j++) {
				cout << "-------------------------" << endl;
				cout << j + 1 << ". gun temas ettigi kisiler" << endl;
				cout << "-------------------------" << endl;
				for (int k = 0; k < sutun; k++)
					if (ematris[j][i][k] == 1) {
						cout << kisiler[k].getId() << " " << kisiler[k].getAd() << endl;
					}

			}
		}
	}

}

//il d���ndan gelen ve covid19 olan ki�ilerin etkile�imde bulunduklar� ki�ilerle olan etkile�im puanlar� toplan�r
//ard�ndan da s�ralanarak ilk vaka olma durumu ekrana bast�r�l�r
void ilkVakaTespit() {

	//linkedlist yerine matris kullan�ld��� i�in matrisi heap'a �evirmek yerine quciksortla s�ralama yap�lm��t�r


	int elemanSayi = 0;
	float** toplam;//id numaras� ve id numaras�na g�re toplama yap�lams� i�in olu�turulmu� pointer dizi

	//dizinin eleman say�s�n� belirlemek i�in 
	for (int i = 0; i < 50; i++) {
		if (kisiler[i].getDisari() == true && kisiler[i].getC19() == true) {

			elemanSayi++;

		}
	}

	//bulunan eleman say�s�na g�re dizi olu�turulur 
	toplam = new float* [elemanSayi];
	for (int i = 0; i < elemanSayi; i++) {
		toplam[i] = new float[2];
	}
	int sayac = 0;
	for (int i = 0; i < 50; i++) {
		if (kisiler[i].getDisari() == true && kisiler[i].getC19() == true) {


			toplam[sayac][0] = i + 101;
			for (int j = 0; j < sutun; j++) {
				toplam[sayac][1] += toplamEtkilesim[i][j];
			}

			sayac++;

		}
	}


	quicksort(toplam, 0, elemanSayi - 1);
	cout << "KisiID\tIsim\tRiskPuani" << endl;
	for (int i = 0; i < elemanSayi; i++) {

		cout << toplam[i][0] << "\t" << kisiler[(int)toplam[i][0] - 101].getAd() << "\t" << toplam[i][1] << endl;



	}
}










