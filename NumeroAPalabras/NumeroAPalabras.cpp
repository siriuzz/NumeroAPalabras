// Enunciado:
// Realizar un programa C++ que lea un número real (correspondiente a un monto) y convertir este monto a palabra.
//
// Participantes:
// 1- John Luis Del Rosario Sánchez - ID 1106940
// 2- Ashly Marisell Paula Ynoa - ID 1108023
// 3- Elián Matos Díaz - ID 1106901
// 4- Juan Daniel Ubiera Méndez - ID 1107248
// 5- Kelvin Arístides García Espinal - ID 1107646

#include <iostream>
#include <string>

using namespace std;

string centenas[10] = { "cien","ciento","doscientos","trescientos","cuatrocientos","quinientos","seiscientos","setecientos","ochocientos","novecientos" },
diez[10] = { "diez", "once", "doce", "trece", "catorce", "quince","dieciséis","diecisiete","dieciocho","diecinueve" },
veinte[10] = { "veintiun","veintiuno","veintidos","veintitres","veinticuatro","veinticinco","veintiseis","veintisiete","veintiocho","veintinueve" },
decenasRestantes[8] = { "veinte","treinta","cuarenta","cincuenta","sesenta","setenta","ochenta","noventa" },
unidades[10] = { "un","uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve" };

bool ValidarNumero(string str)// metodo para comprobar si el dato introducido es entero
{
	int i = 0, dotCount = 0;
	while (str[i] != '\0') //'\0' es el character que marca el final del string
	{
		if (str[i] == '.')
		{
			dotCount++;
			i++;
			continue;
		}

		if (isdigit(str[i]) == false || dotCount > 1 || (str[i] == '.' && i == str.length() - 1)) // compara cada caracter de la cadena para saber si es numerico
		{
			return false;
		}
		i++;
	}
	return true; //devuelve un str igual si no se encontraron letras
}


string NumeroAPalabra(string num, string group) {
	string numeroTexto;

	if (num.length() == 0) return " ";

	for (int i = 0; i < num.length(); i++) {
		int pos = int(num[i]) - 48;

		if (num[i] == '0' && i != 2) continue;

		if (i == 0) { //caso para las centenas
			//caso para "cien"
			if (num[i] == '1' && num[i + 1] == '0' && num[i + 2] == '0') {
				return numeroTexto += centenas[0];
			}
			//caso para "ciento y centenas diferente de "cien"
			else {
				numeroTexto += centenas[pos] + " ";
			}
		}

		if (i == 1) { //caso para las decenas
			if (num[i] == '1') {
				//caso para "diez"
				if (num[i + 1] == '0') {
					return numeroTexto += diez[0];
				}
				//caso para "once", "doce", etc.
				else if (num[i + 1] != '0') {
					return numeroTexto += diez[int(num[i + 1]) - 48];
				}
			}


			if (num[i] == '2') {
				if (group == "centena" && num[i + 1] == '1') { //caso veintiuno
					return numeroTexto += veinte[1];
				}
				else if(num[i + 1] == '1') { // caso veintiun
					return numeroTexto += veinte[0];
				}
				else if (num[i + 1] != '0') { //veintiuno, veintidos...
					return numeroTexto += veinte[int(num[i + 1]) - 48];
				}
			}

			if (num[i + 1] != '0') { //decenas mayores que 2
				numeroTexto += decenasRestantes[pos - 2] + " y ";
			}
			else { //caso para veinte
				return numeroTexto += decenasRestantes[pos - 2];
			}

		}

		if (i == 2) { //caso para las unidades
			if (num[i] == '1') {
				if (group == "centena") {  //cuando esta en formato unidad y no en el grupo de miles ni millones
					numeroTexto += unidades[pos];
				}
				else { //para los casos de "un"
					numeroTexto += unidades[pos - 1];
				}
			}

			if (group == "mil" && num[i] == '1' && num[i - 1] == '0' && num[i - 2] == '0') { //del 1000 al 1999
				return "";
			}

			if (num[i] != '0') { //grupo de unidades sin ningun caso especial
				numeroTexto += unidades[pos];
			}
		}
	}
	return numeroTexto;

}

int main()
{
	string num, numEntero, centavos, subNum, endText;

	while (true) {
		cout << "Inserte el numero que desea convertir a texto: ";
		cin >> num;

		if (ValidarNumero(num) == false) { //Validar si solo se ingresaron numeros (no evalua el punto)
			cout << "Numero invalido, intente de nuevo" << endl;
			continue;
		}

		if (num.find('.') != string::npos) { //si existe el punto en el string
			numEntero = num.substr(0, num.find('.'));
			centavos = num.substr(num.find('.') + 1, num.length() - 1);
			if (centavos == "") {
				cout << "Parte decimal vacia" << endl;
				continue;
			}
		}
		else {
			numEntero = num;
		}

		if (centavos == "") {
			centavos = "00";
		}
		else if (centavos.length() > 2) { //si se agregaron mas de dos decimales
			cout << "Parte decimal fuera de rango, solo inserte dos numeros decimales" << endl;
			continue;
		}
		else if (centavos.length() == 1) { //si solo se agrego un decimal
			centavos = centavos + "0";
		}

		while (numEntero.length() % 3 != 0) { //agregar ceros hasta que la longitud sea 3, 6 o 9
			numEntero = '0' + numEntero;
		}

		int enteroLength = numEntero.length(); //longitud de la parte entera del numero

		if (enteroLength > 9) { //verificar que se encuentra dentro del rango
			cout << "Numero fuera de rango, intente de nuevo" << endl;
			continue;
		}

		for (int i = 0; i < enteroLength + 1; i++) {
			int pos = enteroLength - i; //sirve para saber la posicion del numero que se esta evaluando
			if (subNum.length() == 3 && subNum != "000") { //cuando se han seleccionado 3 digitos
				if (pos == 0) {//posiciones para las unidades, decenas y centenas
					endText += NumeroAPalabra(subNum, "centena") + " ";
				}

				if (pos == 3) { //posiciones para los miles 
					endText += NumeroAPalabra(subNum, "mil") + " mil ";
				}

				if (pos == 6) { //posiciones para los millones
					endText += NumeroAPalabra(subNum, "millon");
					if (subNum[2] == '1' && subNum[1] == '0' && subNum[0] == '0') { //caso para "un millon"
						endText += " millon ";
					}
					else {
						endText += " millones ";
					}
				}
				subNum = "";

			}
			subNum += numEntero[i]; //agregar el digito actual a subNum
		}

		endText = endText + "con " + centavos[0] + centavos[1] + " centavos"; // agregar la parte de los centavos al mensaje final
		if (endText[0] == ' ') {
			endText.erase(0, 1);
		}
		endText[0] = toupper(endText[0]); //primer caracter en mayuscula
		cout << endText;
		break;
	}
}
