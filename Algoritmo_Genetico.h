#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime> 
using namespace std;

struct funcion_evaluada {
	float decimal = 0.0f; 
	float decimal_evaluado = 0.0f; 
	float probabilidad = 0.0f; 
	float probabilidad_acumulada = 0.0f; 
};

class Algoritmo_Genetico {
public: 
	Algoritmo_Genetico(); 
	~Algoritmo_Genetico();
	float Genetico(); 
private:
	void transformar_cadena_a_binario(string& numero, unsigned int num_bits);
	void generar_hijos(string& h1, string& h2, string mascara, string padre1, string padre2);
	void transformar_cadena_a_decimal(string numero_binario, float& decimal);
	void evaluar_funcion(vector<string> &padre1, vector<string> &padre2, vector<string> &h1, vector<string> &h2);
	vector<string>poblacion1;
	vector<string>poblacion2; 

};