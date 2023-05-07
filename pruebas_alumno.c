#include "pa2m.h"
#include "./src/abb.h"
#include "./src/abb_estructura_privada.h"

int comparador_enteros(void *valor1, void *valor2)
{
	return *(int *)(valor1) - *(int *)(valor2);
}

bool comparador_mayor_booleano(void *valor1, void *valor2)
{
	if (*(int *)valor1 > *(int *)valor2)
		return true;
	return false;
}

void sumar_uno(void *valor1)
{
	int *auxiliar = (int *)valor1;
	(*auxiliar)++;
	valor1 = (void *)auxiliar;
}

void prueba_abb_cada_elemento()
{
	abb_t *arbol = abb_crear(comparador_enteros);
	if (!arbol)
		return;

	int valor1 = 544;
	int valor2 = 900;
	int valor3 = 16;
	int valor4 = 45;
	int valor5 = 560;
	int valor6 = 15;
	int auxiliar = 1000;
	size_t cantidad_invocaciones = 0;

	abb_insertar(arbol, &valor1);
	abb_insertar(arbol, &valor2);
	abb_insertar(arbol, &valor3);
	abb_insertar(arbol, &valor4);
	abb_insertar(arbol, &valor5);
	abb_insertar(arbol, &valor6);

	cantidad_invocaciones = abb_con_cada_elemento(
		arbol, INORDEN, comparador_mayor_booleano, &auxiliar);
	pa2m_afirmar(cantidad_invocaciones == 1,
		     "La funcion se invoco la cantidad de veces esperada.");

	auxiliar = 500;
	cantidad_invocaciones = abb_con_cada_elemento(
		arbol, INORDEN, comparador_mayor_booleano, &auxiliar);
	pa2m_afirmar(
		cantidad_invocaciones == 1,
		"Cambiando el auxiliar, la funcion se invoca la cantidad de veces esperadas.");

	auxiliar = 1;
	cantidad_invocaciones = abb_con_cada_elemento(
		arbol, POSTORDEN, comparador_mayor_booleano, &auxiliar);
	pa2m_afirmar(
		cantidad_invocaciones == 6,
		"Cambiando el auxiliar y el recorrido, la funcion se invoca la cantidad de veces esperadas.");

	abb_destruir(arbol);
}

void pruebas_abb_a_array()
{
	abb_t *arbol = abb_crear(comparador_enteros);
	if (!arbol)
		return;

	int valor1 = 5;
	int valor2 = 9;
	int valor3 = 1;
	int valor4 = 7;
	size_t tamanio_arr = 4;

	void *array[tamanio_arr];

	abb_insertar(arbol, &valor1);
	abb_insertar(arbol, &valor2);
	abb_insertar(arbol, &valor3);
	abb_insertar(arbol, &valor4);

	abb_recorrer(arbol, INORDEN, array, tamanio_arr);
	pa2m_afirmar(
		*(int *)array[0] == valor3,
		"Guardando los elementos INORDEN, el primer elemento de array es correcto.");
	pa2m_afirmar(
		*(int *)array[1] == valor1,
		"Guardando los elementos INORDEN, el segundo elemento de array es correcto.");
	pa2m_afirmar(
		*(int *)array[2] == valor4,
		"Guardando los elementos INORDEN, el tercero elemento de array es correcto.");
	pa2m_afirmar(
		*(int *)array[3] == valor2,
		"Guardando los elementos INORDEN, el cuarto elemento de array es correcto.\n");

	abb_recorrer(arbol, PREORDEN, array, tamanio_arr);
	pa2m_afirmar(
		*(int *)array[0] == valor1,
		"Guardando los elementos PREORDEN, el primer elemento de array es correcto.");
	pa2m_afirmar(
		*(int *)array[1] == valor3,
		"Guardando los elementos PREORDEN, el segundo elemento de array es correcto.");
	pa2m_afirmar(
		*(int *)array[2] == valor2,
		"Guardando los elementos PREORDEN, el tercero elemento de array es correcto.");
	pa2m_afirmar(
		*(int *)array[3] == valor4,
		"Guardando los elementos PREORDEN, el cuarto elemento de array es correcto.\n");

	abb_recorrer(arbol, POSTORDEN, array, tamanio_arr);
	pa2m_afirmar(
		*(int *)array[0] == valor3,
		"Guardando los elementos POSTORDEN, el primer elemento de array es correcto.");
	pa2m_afirmar(
		*(int *)array[1] == valor4,
		"Guardando los elementos POSTORDEN, el segundo elemento de array es correcto.");
	pa2m_afirmar(
		*(int *)array[2] == valor2,
		"Guardando los elementos POSTORDEN, el tercero elemento de array es correcto.");
	pa2m_afirmar(
		*(int *)array[3] == valor1,
		"Guardando los elementos POSTORDEN, el cuarto elemento de array es correcto.");

	abb_destruir(arbol);
}

void pruebas_destruir_todo()
{
	abb_t *arbol = abb_crear(comparador_enteros);
	if (!arbol)
		return;

	int valor1 = 5;
	int valor2 = 9;
	int valor3 = 6;
	int valor4 = 7;

	abb_insertar(arbol, &valor1);
	abb_insertar(arbol, &valor2);
	abb_insertar(arbol, &valor3);
	abb_insertar(arbol, &valor4);

	pa2m_afirmar(abb_tamanio(arbol) == 4, "Se insertan 4 elementos.");
	abb_destruir_todo(arbol, sumar_uno);

	pa2m_afirmar(
		valor1 == 6 && valor2 == 10 && valor3 == 7 && valor4 == 8,
		"Se aplico correctamente la funcion enviada a destruir_todo a cada elemento del arbol.");
}

void pruebas_quitar_elementos()
{
	abb_t *arbol = abb_crear(comparador_enteros);
	if (!arbol)
		return;

	int valor1 = 5;
	int valor2 = 9;
	int valor3 = 6;
	int valor4 = 7;
	void *auxiliar;

	abb_insertar(arbol, &valor1);
	abb_insertar(arbol, &valor2);
	abb_insertar(arbol, &valor3);
	abb_insertar(arbol, &valor4);

	auxiliar = abb_quitar(arbol, &valor3);
	pa2m_afirmar(
		*(int *)auxiliar == valor3,
		"El elemento devuelto por la funcion quitar es el correcto.");
	pa2m_afirmar(abb_tamanio(arbol) == 3,
		     "Luego de quitar un elemento el tamanio es el correcto.");

	auxiliar = abb_quitar(arbol, &valor3);
	pa2m_afirmar(auxiliar == NULL,
		     "Intentar quitar un elemento inexistente devuelve NULL.");
	pa2m_afirmar(
		abb_tamanio(arbol) == 3,
		"Luego de intentar quitar un elemento inexistente el tamanio es el correcto.");

	abb_quitar(arbol, &valor1);
	abb_quitar(arbol, &valor2);
	abb_quitar(arbol, &valor4);
	pa2m_afirmar(
		abb_vacio(arbol) == true,
		"Luego de eliminar todos los elementos el arbol queda vacio.");
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "El tamanio del arbol es el correcto.");

	auxiliar = abb_quitar(arbol, NULL);
	pa2m_afirmar(auxiliar == NULL,
		     "Eliminar un elemento NULL, devuelve NULL.");
	pa2m_afirmar(
		abb_tamanio(arbol) == 0,
		"Luego de intentar eliminar un elemento inexistente el tamanio es el correcto.");

	auxiliar = abb_quitar(arbol, &valor1);
	pa2m_afirmar(
		auxiliar == NULL,
		"Intentar quitar un elemento de un arbol vacio devuelve NULL.");

	abb_destruir(arbol);
}

void pruebas_de_insercion()
{
	abb_t *arbol = abb_crear(comparador_enteros);
	if (!arbol)
		return;

	int cantidad_insertados = 0;
	int valor1 = 5;
	int valor2 = 9;
	int valor3 = 6;
	int valor4 = 7;

	abb_insertar(arbol, &valor1);
	pa2m_afirmar(
		abb_tamanio(arbol) == 1,
		"El arbol tiene el tamanio correcto luego de insertar un elemento.");
	pa2m_afirmar(*(int *)abb_buscar(arbol, &valor1) == valor1,
		     "El elemento se inserto correctamente.");
	abb_insertar(arbol, &valor2);
	abb_insertar(arbol, &valor3);
	abb_insertar(arbol, &valor4);

	if (abb_buscar(arbol, &valor1) != NULL)
		cantidad_insertados++;
	if (abb_buscar(arbol, &valor2) != NULL)
		cantidad_insertados++;
	if (abb_buscar(arbol, &valor3) != NULL)
		cantidad_insertados++;
	if (abb_buscar(arbol, &valor4) != NULL)
		cantidad_insertados++;
	pa2m_afirmar(cantidad_insertados == abb_tamanio(arbol),
		     "Se buscan todos los elementos correctamente.");
	pa2m_afirmar(
		abb_tamanio(arbol) == 4,
		"El arbol tiene el tamanio correcto luego de insertar varios elementos.");

	abb_destruir(arbol);
	return;
}

void pruebas_creacion_arbol()
{
	abb_t *arbol = abb_crear(NULL);
	pa2m_afirmar(arbol == NULL,
		     "No se puede crear un arbol con un comparador NULO");

	arbol = abb_crear(comparador_enteros);
	if (!arbol)
		return;
	pa2m_afirmar(arbol != NULL, "Se crea correctamente el arbol.");
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "El tamanio de un arbol recien creado es 0.");

	abb_destruir(arbol);
}

int main()
{
	pa2m_nuevo_grupo("Prueba Creacion de arbol.");
	pruebas_creacion_arbol();
	pa2m_nuevo_grupo("Pruebas de insercion y busqueda.");
	pruebas_de_insercion();
	pa2m_nuevo_grupo("Pruebas de quitar elementos.");
	pruebas_quitar_elementos();
	pa2m_nuevo_grupo("Pruebas Destruir todo.");
	pruebas_destruir_todo();
	pa2m_nuevo_grupo("Pruebas con Arrays");
	pruebas_abb_a_array();
	pa2m_nuevo_grupo("Pruebas funcion a cada elemento.");
	prueba_abb_cada_elemento();
	return pa2m_mostrar_reporte();
}
