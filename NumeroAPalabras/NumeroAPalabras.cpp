// NumeroAPalabras.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

string centenas[10] = { "cien","ciento","doscientos","trescientos","cuatrocientos","quinientos","seiscientos","setecientos","ochocientos","novecientos" },
diez[10] = { "diez", "once", "doce", "trece", "catorce", "quince","dieciséis","diecisiete","dieciocho","diecinueve" },
veinte[10] = { "veintiun","veintiuno","veintidos","veintitres","veinticuatro","veinticinco","veintiseis","veintisiete","veintiocho","veintinueve" },
decenasRestantes[8] = { "veinte","treinta","cuarenta","cincuenta","sesenta","setenta","ochenta","noventa" },
unidades[10] = { "un","uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve" };

string NumeroAPalabra(string num, string group) {
	string numeroTexto;

	if (num.length() == 0) return " ";
	while (num.length() < 3) {
		num = '0' + num;
	}

	for (int i = 0; i < num.length(); i++) {
		int pos = int(num[i]) - 48;

		if (num[i] == '0' && i != 2) continue;

		if (i == 0) {
			if (num[i] == '1' && num[i + 1] == '0' && num[i + 2] == '0') {
				numeroTexto += centenas[0];
			}
			else{
				numeroTexto += centenas[pos] + " ";
			}
		}

		if (i == 1) {

			if (num[i] == '1' && num[i + 1] == '0') {
				return numeroTexto += diez[0];
			} else if(num[i] == '1' && num[i+1] != '0'){

			}

			if (num[i] == '2' && num[i+1] == '1' && group == "centena") {
				return numeroTexto += veinte[1];
			}
			else if (num[i] == '2' && num[i+1] == '1' && group != "centena") {
				return numeroTexto += veinte[0];
			}
			else if (num[i] == '2' && num[i+1] != '0') {
				return numeroTexto += veinte[int(num[i+1] - 48)];
			}
			else if (num[i] == '2' && num[i + 1] == '0') {
				return numeroTexto += decenasRestantes[0];
			}
			
			
			if (num[i + 1] != '0' && num[i] != '2') {
				numeroTexto += decenasRestantes[pos - 2] + " y ";
			}
			else {
				return numeroTexto += decenasRestantes[pos-2] + " ";
			}
			
		}

		if (i == 2) {
			if (group == "centena" && num[i] == '1') {
				numeroTexto += unidades[pos] + " ";
			}
			else if (num[i] == '1' && group != "centena") {
				numeroTexto += unidades[pos - 1] + " ";
			}
			else {
				numeroTexto += unidades[pos] + " ";
			}
			
		}
	}
	return numeroTexto;

}

int main()
{
	string num, numNoCentavos, subNum, endText;

	while (true) {
		cout << "Inserte el numero que desea convertir a texto: ";
		cin >> num;

		if (num.find('.') != string::npos) {
			numNoCentavos = num.substr(num.find('.') + 1);
		}
		else {
			numNoCentavos = num;
		}

		while (numNoCentavos.length() % 3 != 0) {
			numNoCentavos = '0' + numNoCentavos;
		}

		int strLength = numNoCentavos.length();

		if (strLength > 9) {
			cout << "Numero fuera de rango, intente de nuevo" << endl;
			continue;
		}

		int counter = 0;
		for (int i = 0; i < strLength + 1; i++) {
			int pos = strLength - i + 3;

			if (subNum.length() == 3 || i == strLength || counter == 3) {
				if (pos == 3 || pos == 2 || pos == 1) {
					endText += NumeroAPalabra(subNum, "centena") + " ";
					subNum = "";
				}

				if (pos == 6 || pos == 5 || pos == 4) {
					endText += NumeroAPalabra(subNum, "mil") + "mil ";
					subNum = "";
				}

				if (pos == 9 || pos == 8 || pos == 7) {
					endText += NumeroAPalabra(subNum, "millon") + " ";
					subNum = "";
				}

			}
			subNum += numNoCentavos[i];
			counter++;
		}

		cout << endText;

		//for (int i = num.length(); i > -1; i--) {
		//	if ((i == strLength - 12 || i == strLength - 9 || i == strLength - 6) && num[i] != '0') {
		//		if (num[i] == '1'&& num[i + 1] == '0' && num[i + 2] == '0') {
		//			cout << centenas[0];
		//		}
		//		int pos = int(num[i]) - 48;
		//		cout << centenas[pos] << endl;
		//	}

		//	if ((i == strLength - 11 || i == strLength - 8 || i == strLength - 5) && num[i] != '0') {
		//		if (num[i] == '2') { // 20.00, 20000.00, 20000000.00
		//			if (num[i + 1] != 0) {
		//				if (num[i + 2] != '.') {
		//					int pos = int(num[i + 1]) - 48;
		//					cout << veinte[pos] << endl;
		//				}
		//				else {
		//				}
		//			}
		//			
		//		}
		//		
		//	}

		//	if ((i == strLength - 10 || i == strLength - 7 || i == strLength - 4) && num[i] != '0') {
		//		int pos = int(num[i]) - 48;
		//		cout << unidades[pos] << endl;
		//	}
		//}

		break;
	}

}
