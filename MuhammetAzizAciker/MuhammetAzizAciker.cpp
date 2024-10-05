#include <iostream>
#include <fstream>
#include<sstream>

using namespace std;


class kisi {
private:
	int id;
	string ad;

	float mKapasite;
	float vBeyani;

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
	//kullanacak olduðum getter metodlarý

	int getId() {
		return id;
	}
	string getAd() {
		return ad;
	}
	float getmKapasite() {
		return mKapasite;
	}
	float getvBeyani() {
		return vBeyani;
	}


	//elemanAta fonkiyonunda kullanýlacak olan metod
	void	ayarla(int _id, string _ad, float _mKapasite, float _vBeyani) {
		id = _id;
		ad = _ad;
		mKapasite = _mKapasite;
		vBeyani = _vBeyani;


	}
	//nesneyi ekrana çýktý almaya yarayan metod	
	void	print() {
		cout << id << " " << ad << " " << mKapasite << " " << vBeyani << endl;
	}
};
kisi kisiler[50];
int gonderilen[50] = { 0 };
int gelen[50] = { 0 };
int satir, sutun, maskeSutun;
int** imatris;


#pragma region functions

int virgul_sil(string& s) {
	int virgulSayisi = 0;
	int	l = s.length();
	for (int i = 0; i < l; i++)
	{
		if (s[i] == '\t') {
			virgulSayisi++;

		}
		 
	}
	return virgulSayisi;
}
void satirSutunOku(const char* arr, int& stn) {
	satir = 0;
	fstream dosya(arr, ios::in);
	string temp;
	while (getline(dosya, temp)) {
		satir++;
		stn = virgul_sil(temp) + 1;
	}


}
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
			int c;

			ss >> c;


			if (c != '-') {

				matris[sayac][i] = c;//c karaktesine atýlan deðerin 48 eksiðini alarak asci tablosuna göre iþlem yapýlmaktadýr

			}
			else
				matris[sayac][i] = 999;//okunan matristeki '-' ile belirtilen yerlere boþ deðer olarak 999 atanmýþtýr

		}


		sayac++;
	}
}
void matrisPrint(int** matris, int sutun) {

	for (int i = 1; i < satir; i++) {
		for (int j = 1; j < sutun; j++) {
			cout << matris[i][j] << " ";
		}
		cout << endl;
	}



}
void elemanAta() {
	fstream dosya("kisilervefirmalar.txt", ios::in);
	string temp;

	int oSayac = 0;
	int i = 0;
	while (getline(dosya, temp)) {

		if (i > 0) {
			virgul_sil(temp);

			stringstream ss(temp);
			int dizi[4];//6 tane özelliðimiz olduðu için onlarý tutan dizi
			string a;
			char arr;
			int id;
			string ad, ad2;
			float maksKapasite, vergiBeyani;
			
			ss >> id;


			if (id > 1030) {
				ss >> ad >> ad2 >> maksKapasite >> vergiBeyani;
				ad = ad + " " + ad2;
			}
			else {
				ss >> ad >> maksKapasite >> vergiBeyani;

			}

			kisiler[oSayac].ayarla(id, ad, maksKapasite*1000, vergiBeyani*1000);
			oSayac++;
		}
		i++;

	}

}
void bellekAta() {

	satirSutunOku("transfer.txt", sutun);
	imatris = new int* [satir];
	for (int i = 0; i < satir; i++) {
		imatris[i] = new int[sutun];
	}

}
int stoi(const string s) {
	stringstream ss(s);

	int x;

	ss >> x;

	return x;
}

void toplamTransfer(int** matris) {
	for (int i = 1; i < satir; i++) {
		for (int j = 1; j < sutun; j++) {
			gonderilen[i-1] += matris[i][j];
			gelen[i-1] += matris[j][i];
		}
	}
	
}
void transferListele() {
	for (int i = 0; i < 50; i++) {
		cout <<i+1001<< ". kisi Giden " << gonderilen[i] << " gelen " << gelen[i] << endl;
	}
}
void supheliBul() {
	int state = 0;
	ofstream dosyaYaz("SupheliListesi.txt");
	if (dosyaYaz.is_open()) {
		
	for (int i = 0; i < 50; i++) {
		state = 0;
		if (kisiler[i].getvBeyani() <= kisiler[i].getmKapasite()&& kisiler[i].getvBeyani() == gelen[i]) {
			state = 1;
			//dosyaYaz << kisiler[i].getId() << " ID'li " << kisiler[i].getAd() <<" vb "<<kisiler[i].getvBeyani()<<" mik "<< kisiler[i].getmKapasite()<< " TPT " <<gelen[i]<< " Durum 1'den supheli degil" << endl;
		}
		if (kisiler[i].getvBeyani()>(2* kisiler[i].getmKapasite())) {
			state = 1;
			dosyaYaz << kisiler[i].getId() << " ID'li " << kisiler[i].getAd() << " vb " << kisiler[i].getvBeyani() << " mik " << kisiler[i].getmKapasite() << " TPT " << gelen[i] << " Durum 2'den supheli " << endl;
			cout << kisiler[i].getId() << " ID'li " << kisiler[i].getAd() << " vb " << kisiler[i].getvBeyani() << " mik " << kisiler[i].getmKapasite() << " TPT " << gelen[i] << " Durum 2'den supheli " << endl;
		}
		if (kisiler[i].getvBeyani() != gelen[i]) {
			state = 1;
			dosyaYaz << kisiler[i].getId() << " ID'li " << kisiler[i].getAd() << " vb " << kisiler[i].getvBeyani() << " mik " << kisiler[i].getmKapasite() << " TPT " << gelen[i] << " Durum 3'den supheli " << endl;
			cout << kisiler[i].getId() << " ID'li " << kisiler[i].getAd() << " vb " << kisiler[i].getvBeyani() << " mik " << kisiler[i].getmKapasite() << " TPT " << gelen[i] << " Durum 3'den supheli " << endl;
		}
		if (state == 0) {
			//dosyaYaz << kisiler[i].getId() << " ID'li " << kisiler[i].getAd() << " vb " << kisiler[i].getvBeyani() << " mik " << kisiler[i].getmKapasite() << " TPT " << gelen[i] << "  supheli degil" << endl;
		}
	}
	
	dosyaYaz.close();
	}
}
#pragma endregion

int main()
{

	elemanAta();

	/*for (int i = 0; i < 50; i++) {
		kisiler[i].print();
	}*/
	satirSutunOku("transfer.txt", sutun);
	bellekAta();
	matrisOkuma(imatris, "transfer.txt", sutun);
	//matrisPrint(imatris, sutun);
	toplamTransfer(imatris);
	transferListele();
	supheliBul();
	
}


// Programı çalıştır: Ctrl + F5 veya Hata Ayıkla > Hata Ayıklamadan Başlat menüsü
// Programda hata ayıkla: F5 veya Hata Ayıkla > Hata Ayıklamayı Başlat menüsü

// Kullanmaya Başlama İpuçları: 
//   1. Dosyaları eklemek/yönetmek için Çözüm Gezgini penceresini kullanın
//   2. Kaynak denetimine bağlanmak için Takım Gezgini penceresini kullanın
//   3. Derleme çıktısını ve diğer iletileri görmek için Çıktı penceresini kullanın
//   4. Hataları görüntülemek için Hata Listesi penceresini kullanın
//   5. Yeni kod dosyaları oluşturmak için Projeye Git > Yeni Öğe ekle veya varolan kod dosyalarını projeye eklemek için Proje > Var Olan Öğeyi Ekle adımlarını izleyin
//   6. Bu projeyi daha sonra yeniden açmak için Dosya > Aç > Proje'ye gidip .sln uzantılı dosyayı seçin
