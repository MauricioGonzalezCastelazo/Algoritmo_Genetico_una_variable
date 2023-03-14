#include "Algoritmo_Genetico.h"
Algoritmo_Genetico::Algoritmo_Genetico() {

 }

Algoritmo_Genetico::~Algoritmo_Genetico() {

}


void Algoritmo_Genetico::transformar_cadena_a_binario(string& numero, unsigned int num_bits) {
	int numero_a_convertir = stoi(numero);
	int residuo = 0, coeficiente = -1; 
	vector<int> temporal; 
	while (coeficiente != 0)
	{
		coeficiente = numero_a_convertir / 2; 
		residuo = numero_a_convertir % 2; 
		temporal.push_back(residuo);
		numero_a_convertir = coeficiente;
	}
	numero = "";
	int i = (int)temporal.size() - 1;
	while (i != -1) {
		numero += to_string(temporal.at(i));
		i--;
	}

	if (num_bits > temporal.size())
	{
		string temporal = "";
		for (unsigned int i = 0; i < (num_bits - numero.size()); i++)
			temporal += "0";
		for (unsigned int i = 0; i < numero.size(); i++)
			temporal += numero.at(i);
		numero = temporal; 
	}
	else if (temporal.size() > num_bits)
	{
		string temporal = "";
		while(numero.size() != num_bits)
			numero.erase(numero.begin());
	}
}

void Algoritmo_Genetico::generar_hijos(string& h1, string& h2, string mascara, string padre1, string padre2) {
	srand((unsigned int)time(0));
	int probabilidad_de_mutacion = 0; 
	for (unsigned int i = 0; i < padre1.size(); i++)
	{
		probabilidad_de_mutacion = (rand() % 10);
		const char comparar = mascara[i];
		if (probabilidad_de_mutacion == 1) {
			int eleccion_padre = rand() % 2;
			string ayuda_mutacion; 
			if (eleccion_padre == 0)
			{
				ayuda_mutacion = padre1; 
				unsigned int posicion = rand() % padre1.size();
				if (ayuda_mutacion[posicion] == '0')
					ayuda_mutacion[posicion] = '1';
				else
					ayuda_mutacion[posicion] = '0';
				h1.push_back(ayuda_mutacion.at(i));
				h2.push_back(padre2.at(i));


			}
			else if (eleccion_padre == 1)
			{
				ayuda_mutacion = padre2;
				unsigned int posicion = rand() % padre2.size();
				if (ayuda_mutacion[posicion] == '0')
					ayuda_mutacion[posicion] = '1';
				else
					ayuda_mutacion[posicion] = '0';
				h1.push_back(padre1.at(i));
				h2.push_back(ayuda_mutacion.at(i));
			}
		}
			
		else if (comparar == (char)('1'))
		{
			h1.push_back(padre1.at(i));
			h2.push_back(padre2.at(i));
		}
		else if (comparar == (char)('0'))
		{
			h1.push_back(padre2.at(i));
			h2.push_back(padre1.at(i));
		}
	}
}

void Algoritmo_Genetico::transformar_cadena_a_decimal(string numero_binario, float& decimal)
{
	decimal = 0; 
	int numero_temporal = numero_binario.size()-1;
	for (unsigned int i = 0; i < numero_binario.size(); i++)
	{
		if (numero_binario.at(i) == '1')
			decimal += (float)pow(2, numero_temporal-i);
	}
}
void Algoritmo_Genetico:: evaluar_funcion(vector<string> &padre1, vector<string> &padre2, vector<string> &h1, vector<string> &h2)
{
	vector<funcion_evaluada>padre1_funcion;
	vector<funcion_evaluada>padre2_funcion;
	vector<funcion_evaluada>h1_funcion;
	vector<funcion_evaluada>h2_funcion;
	funcion_evaluada ayuda; 
	float temporal = 0.0f; 
	float probabilidad = 0; 
	for (unsigned int i = 0; i < padre1.size(); i++)
	{
		transformar_cadena_a_decimal(padre1.at(i), temporal);
		ayuda.decimal = float(temporal); 
		padre1_funcion.push_back(ayuda);
		transformar_cadena_a_decimal(padre2.at(i), temporal);
		ayuda.decimal = float(temporal);
		padre2_funcion.push_back(ayuda);
		transformar_cadena_a_decimal(h1.at(i), temporal);
		ayuda.decimal = float(temporal);
		h1_funcion.push_back(ayuda);
		transformar_cadena_a_decimal(h2.at(i), temporal);
		ayuda.decimal = float(temporal);
		h2_funcion.push_back(ayuda);
	}
	for (unsigned int i = 0; i < padre1.size(); i++)
	{
		padre1_funcion.at(i).decimal_evaluado = (float)pow((padre1_funcion.at(i).decimal-30), 2);
		padre2_funcion.at(i).decimal_evaluado = (float)pow((padre2_funcion.at(i).decimal-30), 2);
		h1_funcion.at(i).decimal_evaluado = (float)pow((h1_funcion.at(i).decimal-30), 2);
		h2_funcion.at(i).decimal_evaluado = (float)pow((h2_funcion.at(i).decimal-30), 2);
	}
	for (unsigned int i = 0; i < padre1_funcion.size(); i++)
	{
		probabilidad += (padre1_funcion.at(i).decimal_evaluado + padre2_funcion.at(i).decimal_evaluado);
	}
	for (unsigned int i = 0; i < padre1_funcion.size(); i++)
	{
		padre1_funcion.at(i).probabilidad = padre1_funcion.at(i).decimal_evaluado / probabilidad; 
		padre2_funcion.at(i).probabilidad = padre2_funcion.at(i).decimal_evaluado / probabilidad;
		h1_funcion.at(i).probabilidad = h1_funcion.at(i).decimal_evaluado / probabilidad;
		h2_funcion.at(i).probabilidad = h2_funcion.at(i).decimal_evaluado / probabilidad;
	}
	for (unsigned int i = 0; i < padre1.size(); i++)
	{
		if(i == 0)
			padre1_funcion.at(i).probabilidad_acumulada += padre1_funcion.at(i).probabilidad;
		else {
			padre1_funcion.at(i).probabilidad_acumulada += (padre1_funcion.at(i).probabilidad+ padre1_funcion.at(i-1).probabilidad_acumulada);
		}
	}
	for (unsigned int i = 0; i < padre1_funcion.size(); i++)
	{
		if (i == 0)
			padre2_funcion.at(i).probabilidad_acumulada = padre1_funcion.at(padre1_funcion.size() - 1).probabilidad_acumulada + padre2_funcion.at(i).probabilidad;
		else {
			padre2_funcion.at(i).probabilidad_acumulada += (padre2_funcion.at(i).probabilidad+ padre2_funcion.at(i-1).probabilidad_acumulada);
		}
	}
	
	funcion_evaluada ayuda_bubble1;
	vector<funcion_evaluada> mejores_pobladores; 
	for (unsigned int i = 0; i < padre1_funcion.size(); i++)
	{
		mejores_pobladores.push_back(padre1_funcion.at(i));
	}
	for (unsigned int i = 0; i < padre1_funcion.size(); i++)
	{
		
		mejores_pobladores.push_back(padre2_funcion.at(i));
	}
	for (unsigned int i = 0; i < padre1_funcion.size(); i++)
	{
		mejores_pobladores.push_back(h1_funcion.at(i));
	}
	for (unsigned int i = 0; i < h1_funcion.size(); i++)
	{
		mejores_pobladores.push_back(h2_funcion.at(i));
	}

	for (unsigned int i = 0; i < mejores_pobladores.size(); i++)
	{
		for (unsigned int j = 0 ; j < mejores_pobladores.size(); j++)
		{
			if (mejores_pobladores.at(i).decimal_evaluado < mejores_pobladores.at(j).decimal_evaluado) {
				ayuda_bubble1 = mejores_pobladores.at(i);
				mejores_pobladores.at(i) = mejores_pobladores.at(j);
				mejores_pobladores.at(j) = ayuda_bubble1;
			}
		}
	}

	while (mejores_pobladores.size() != (padre1_funcion.size())*2)
	{
		mejores_pobladores.pop_back();
	}
	padre1.clear(); 
	padre2.clear();
	h1.clear();
	h2.clear();
	for (unsigned int i = 0; i<(unsigned int)(padre1_funcion.size()); i++)
	{
		string mejor = to_string(mejores_pobladores.at(i).decimal);
		transformar_cadena_a_binario(mejor, 8);
		padre1.push_back(mejor);
	}
	for (unsigned int i = padre1_funcion.size(); i<(unsigned int)(padre1_funcion.size()*2); i++)
	{
		string mejor = to_string(mejores_pobladores.at(i).decimal);
		transformar_cadena_a_binario(mejor, 8);
		padre2.push_back(mejor);
	}

}

float Algoritmo_Genetico::Genetico()
{
	int size_poblacion = 100;//poblacion
	int num_random = 0; 
	string numero_a_transformar = "";
	vector<string>h1; 
	vector<string>h2; 
	float valor_devuelto = 0; 
	srand((unsigned int)(time(0)));
	for (unsigned int i = 0; i < (unsigned int)size_poblacion; i++)
	{
		num_random = (rand() % (rand()));
		numero_a_transformar = to_string(num_random);
		transformar_cadena_a_binario(numero_a_transformar, 8);
		if (i < (unsigned int)size_poblacion/2)
			poblacion1.push_back(numero_a_transformar);
		else
			poblacion2.push_back(numero_a_transformar);
	}
	for (unsigned int i = 0; i < 50; i++) {//Generacion
		for (unsigned int i = 0; i < poblacion1.size(); i++)
		{
			string hijos1;
			string hijos2;
			generar_hijos(hijos1, hijos2, "10010101", poblacion1.at(i), poblacion2.at(i));
			h1.push_back(hijos1);
			h2.push_back(hijos2);
		}
		evaluar_funcion(poblacion1, poblacion2, h1, h2);
	}
	
	transformar_cadena_a_decimal(poblacion1.at(0), valor_devuelto);
	return valor_devuelto; 
}
//(x-30)^2
//x^2-60x+900
//2x-60=0
//=30






