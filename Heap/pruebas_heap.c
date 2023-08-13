#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM_VOL 2000

// funcion de comparar
int cmp (const void* a, const void* b) {
	int *izq = (int*)a; 
	int *der = (int*)b;
	if (*izq < *der) {
		return -1; 
	}
	else if (*izq > *der) {
		return 1; 
	}
	return 0; 
}

/* Pruebas para un heap vacio */
static void prueba_heap_vacio(void) {
    printf("INICIO DE PRUEBAS CON HEAP VACIO\n");

    /* Creo un heap */
    heap_t *heap = heap_crear(cmp);

    print_test("crear heap", heap != NULL);
    print_test("el heap nuevo esta vacio", heap_esta_vacio(heap));
    print_test("el heap no tiene maximo", heap_ver_max(heap) == NULL);
    print_test("la cantidad del heap es 0", heap_cantidad(heap) == 0);
    print_test("desencolar es NULL", heap_desencolar(heap) == NULL);

    /* Destruyo el heap */
    heap_destruir(heap, NULL);
    print_test("el heap fue destruido", true);
}

/* Pruebas del heap con algunos elementos */
static void prueba_heap_algunos_elementos(void) {
    printf("\nINICIO DE PRUBEAS CON ALGUNOS ELEMENTOS\n");

    /* Declaro las variables a utilizar */
    int numeros_enteros[] = {10, 20, 30, 40, 50};
    
    /* Creo un heap */
    heap_t *heap = heap_crear(cmp);
    print_test("crear heap", heap != NULL);

    /* Pruebo encolar algunos elementos */
    print_test("se encolo un elemento", heap_encolar(heap, &numeros_enteros[0]));
    print_test("se encolo un elemento", heap_encolar(heap, &numeros_enteros[1]));
    print_test("se encolo un elemento", heap_encolar(heap, &numeros_enteros[2]));
    print_test("se encolo un elemento", heap_encolar(heap, &numeros_enteros[3]));
    print_test("se encolo un elemento", heap_encolar(heap, &numeros_enteros[4]));

    print_test("el heap no esta vacio", !heap_esta_vacio(heap));
    print_test("la cantidad del heap es 5", heap_cantidad(heap) == 5);
    print_test("el maximo del heap es el maximo valor encolado", heap_ver_max(heap) == &numeros_enteros[4]);
    print_test("desencolar devuelve el valor max del heap", heap_desencolar(heap) == &numeros_enteros[4]);
    print_test("el maximo del heap es el segundo maximo valor encolado", heap_ver_max(heap) == &numeros_enteros[3]);
    print_test("desencolar devuelve el valor max del heap", heap_desencolar(heap) == &numeros_enteros[3]);
    print_test("desencolar devuelve el valor max del heap", heap_desencolar(heap) == &numeros_enteros[2]);
    print_test("desencolar devuelve el valor max del heap", heap_desencolar(heap) == &numeros_enteros[1]);
    print_test("desencolar devuelve el valor max del heap", heap_desencolar(heap) == &numeros_enteros[0]);

    print_test("al desencolar todos los elementos el heap esta vacio", heap_esta_vacio(heap));
    print_test("la cantidad del heap es 0", heap_cantidad(heap) == 0);
    print_test("desencolar es NULL", heap_desencolar(heap) == NULL);

    /* Destruyo el heap */
    heap_destruir(heap, NULL);
    print_test("el heap fue destruido", true);

}
/* Pruebas del heap con un volumen grande de elementos */
static void prueba_heap_volumen(void) {
    printf("\nINICIO DE PRUBEAS DE VOLUMEN\n");
    
    /* Declaro las variables a utilizar */
    int *enteros = malloc(sizeof(int) * TAM_VOL );
    bool ok = true;

    /* Creo un heap */
    heap_t *heap = heap_crear(cmp);
    print_test("crear heap", heap != NULL);

    /* Pruebo encolar todos los elementos */
    for (int i = 0; i < TAM_VOL; i++) {
        enteros[i] = i;
        if (!heap_encolar(heap, &enteros[i])) ok = false;
    }
    print_test("se encolaron 2000 elementos correctamente", ok);
    print_test("la cantidad del heap es 2000", heap_cantidad(heap) == 2000);
    print_test("el heap no esta vacio", !heap_esta_vacio(heap));

    ok = true;
    for (int j = TAM_VOL - 1; j >= 0; j--) {
        if (heap_desencolar(heap) != &enteros[j]) ok = false;
    }

    print_test("se desencolaron todos los elementos y se cumplio el invariante", ok);
    print_test("la cantidad del heap es 0", heap_cantidad(heap) == 0);
    print_test("el heap esta vacio", heap_esta_vacio(heap));
    
    free(enteros);

    /* Destruyo el heap */
    heap_destruir(heap, NULL);
    print_test("el heap fue destruido", true);
    

}

/* Pruebas de destruir un heap con punteros adentro */
static void prueba_heap_destruir(void) {
     printf("\nINICIO DE PRUBEAS DE DESTRUCCION CON ELEMENTOS ADENTRO\n");
    /* Declaro las variables a utilizar */
    int *num_1 = malloc(sizeof(int));
    int *num_2 = malloc(sizeof(int));
    int *num_3 = malloc(sizeof(int));
    int *num_4 = malloc(sizeof(int));
    int *num_5 = malloc(sizeof(int));
    *num_1 = 5;
    *num_2 = 10;
    *num_3 = 15;
    *num_4 = 20;
    *num_5 = 25;
    
    /* Creo un heap */
    heap_t *heap = heap_crear(cmp);
    print_test("crear heap", heap != NULL);

    /* Encolo los elementos */
    print_test("se encolo un elemento", heap_encolar(heap, num_1));
    print_test("se encolo un elemento", heap_encolar(heap, num_2));
    print_test("se encolo un elemento", heap_encolar(heap, num_3));
    print_test("se encolo un elemento", heap_encolar(heap, num_4));
    print_test("se encolo un elemento", heap_encolar(heap, num_5));

    /* Destruyo el heap */
    heap_destruir(heap, free);
    print_test("el heap fue destruido", true);
}



static void prueba_heap_desencolar(void) {
	printf("\nPRUEBAS HEAP DESENCOLAR\n");
	//Primera parte
	bool ok_desencolar = true, ok_max = true;
	int arreglo1[11] = {3,8,5,6,7,10,5,2,4,0,1}, arreglo1_desencolado[11] = {10,8,7,6,5,5,4,3,2,1,0}; 
	void* arreglo1_p[11];
	for(int i= 0; i < 11;i++) {
		arreglo1_p[i] = &arreglo1[i];
	}
	heap_t* heap1 = heap_crear_arr(arreglo1_p, 11, cmp);
	print_test("Prueba crear el heap1 con un array", heap1);
	for(int i= 0; i < 11;i++) {
		int* aux = (int*)heap_ver_max(heap1);
		if (*aux != arreglo1_desencolado[i]) ok_max = false;
		aux = (int*) heap_desencolar(heap1);
		if (*aux != arreglo1_desencolado[i]) {
			ok_desencolar = false;
		}
	} 
	print_test("Prueba desencolar el heap1", ok_desencolar);
	print_test("Prueba el maximo fue correcto", ok_max);
	print_test("Prueba desencolar el heap1 es NULL", !heap_desencolar(heap1));
	print_test("Prueba heap1 esta vacio", heap_esta_vacio(heap1)); 
	heap_destruir(heap1, NULL); 
	print_test("Prueba destruir el heap1", true);
	//Segunda parte 
	ok_desencolar = true, ok_max = true;
	int arreglo2[12] = {2,6,7,9,2,5,6,7,4,10,22,16}, arreglo2_desencolado[12] = {22,16,10,9,7,7,6,6,5,4,2,2};
	void* arreglo2_p[12];
	for(int i= 0; i < 12;i++) {
		arreglo2_p[i] = &arreglo2[i];
	}
	heap_t* heap2 = heap_crear_arr(arreglo2_p, 12, cmp);
	print_test("Prueba crear el heap2 con un array", heap2);
	for(int i= 0; i < 12;i++) {
		int* aux = (int*)heap_ver_max(heap2);
		if (*aux != arreglo2_desencolado[i]) ok_max = false;
		aux = (int*) heap_desencolar(heap2);;
		if (*aux != arreglo2_desencolado[i]) {
			ok_desencolar = false;
		}
	} 
	print_test("Prueba desencolar el heap2", ok_desencolar);
	print_test("Prueba el maximo fue correcto", ok_max);
	print_test("Prueba desencolar el heap2 es NULL", !heap_desencolar(heap2));
	print_test("Prueba heap esta vacio2", heap_esta_vacio(heap2)); 
	heap_destruir(heap2, NULL); 
	print_test("Prueba destruir el heap2", true);
}
static void prueba_heapsort() {
	printf("\nPRUEBAS HEAPSORT\n");
	bool ok = true;
	int arreglo1[20] = {30,16,24,77,65,3,8,1,49,34,21,0,3,5,15,23,90,44,50,10}, 
	arreglo1_ordenado[20] = {0,1,3,3,5,8,10,15,16,21,23,24,30,34,44,49,50,65,77,90};
	void* arreglo1_p[20]; 
	for(int i = 0; i < 20; i++) {
		arreglo1_p[i] = &arreglo1[i];
	}
	heap_sort(arreglo1_p, 20, cmp);
	for(int i = 0; i < 20; i++) {
		int* aux = (int*)arreglo1_p[i];
		if (*aux != arreglo1_ordenado[i]) {
			ok = false;
		}
	}
	print_test("Prueba #1 heapsort correcta" ,ok); 
	ok = true;                    
	int arreglo2_ordenado[35] = {1,7,8,14,15,18,19,20,21,32,33,35,40,41,43,45,48,49,50,51,55,57,61,65,69,71,75,76,77,82,85,86,91,95,99},
	arreglo2[35] = {45,35,14,8,7,55,95,61,82,99,91,86,20,15,50,1,69,18,43,19,57,21,71,75,65,32,77,33,40,41,85,51,76,48,49};
	void* arreglo2_p[35];
	for(int i = 0; i < 35; i++) {
		arreglo2_p[i] = &arreglo2[i];
	}
	heap_sort(arreglo2_p, 35, cmp);
	for(int i = 0; i < 35; i++) {
		int* aux = (int*)arreglo2_p[i];
		if (*aux != arreglo2_ordenado[i]) {
			ok = false;
		}
	}
	print_test("Prueba #2 heapsort correcta" ,ok);
	
}

void pruebas_heap_estudiante() {
    /* Ejecuta todas las pruebas unitarias. */
    prueba_heap_vacio();
    prueba_heap_algunos_elementos();
    prueba_heap_volumen();
    prueba_heap_destruir();
    prueba_heap_desencolar();
	prueba_heapsort();
}
