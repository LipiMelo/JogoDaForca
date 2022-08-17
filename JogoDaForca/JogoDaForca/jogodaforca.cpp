#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

string palavra_secreta;
map<char, bool> chutou;
vector<char> chutes_errados;


bool letra_existe(char chute) {
	
	for (char letra : palavra_secreta){
		if (chute == letra) {
			return true;
		}
	}
	return false;
}

bool nao_acertou(){
	for (char letra : palavra_secreta) {
		if (!chutou[letra]) {
			return true;
		}
	}
	return false;
}

bool nao_enforcou() {
	return chutes_errados.size() < 5;
}
void imprime_cabecalho() {

	cout << "*******************" << endl;
	cout << "** Jogo da Forca **" << endl;
	cout << "*******************" << endl << endl;

}

void imprime_chutes_errados() {

	cout << "Chutes errados: ";
	for (char letra : chutes_errados) {
		cout << letra << " ";
	}
	cout << endl; 

}

void imprime_palavra_secreta() {

	for (char letra : palavra_secreta) {
		if (chutou[letra]) {
			cout << letra << " ";
		}
		else {
			cout << "_ ";
		}
	}
	cout << endl;
}


void imprime_tentativas() {

	char chute;
	cin >> chute;

	chutou[chute] = true;

	if (letra_existe(chute)) {
		cout << "Voce Acertou! Meus parabens." << endl;
	}
	else {
		cout << "Voce Errou. boa sorte na proxima." << endl;
		chutes_errados.push_back(chute);
	}
	cout << endl;
}


void fim_de_jogo() {
	cout << "Fim de Jogo!" << endl << endl;
	cout << "A palavra secreta era: " << palavra_secreta << endl;
	if (nao_acertou()) {
		cout << "Voce perdeu! Boa sorte na proxima." << endl;
	}
	else {
		cout << "Parabens! Voce acertou a palavra secreta!" << endl;
	}
}

vector<string> le_arquivo() {
	ifstream arquivo;
	arquivo.open("palavras.txt");

	if (arquivo.is_open()) {
		int quantidade_palavras;
		arquivo >> quantidade_palavras;


		vector<string> palavras_do_arquivo;

		for (int i = 0; i < quantidade_palavras; i++) {
			string palavra_lida;
			arquivo >> palavra_lida;
			palavras_do_arquivo.push_back(palavra_lida);
		}

		arquivo.close();
		return palavras_do_arquivo;
	}
	else {
		cout << "Nao foi possível acessar o banco de palavras." << endl;
		exit(0)
	}
}

void sorteia_palavra() {
	vector<string> palavras = le_arquivo();

	srand(time(NULL));
	int indice_sorteado = rand() % palavras.size();

	palavra_secreta = palavras[indice_sorteado];
}

int main() {

	imprime_cabecalho();

	le_arquivo();
	sorteia_palavra();

	while (nao_acertou() && nao_enforcou()) {

		imprime_chutes_errados();

		imprime_palavra_secreta();

		imprime_tentativas();
	}

	fim_de_jogo();
	
}