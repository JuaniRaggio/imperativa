#define N 10
#define M 20


int
main (void)
{
	int dim = 7;
	int vectorA[ M * N];
	int vectorB[ -10 ]; // No puede ser negativo
	int vectorC[ 10.0 ]; // No puede ser un numero no entero
	int vectorD[dim]; // No puede ser una variable
	vectorC[2.5] = 'a'; // 2.5 no puede ser no entero
	vectorB[-1] = 5; // Simplemente hace la cuenta
	vectorA['0'] = 10; // Idem
	vectorC[vectorA[48]] = 5.5; // Puede que falle en tiempo de ejecucion
	vectorA[1000] = 0; // Puede que falle en tiempo de ejecucion
	vectorA[M * N] = 10;
	return 0;
}
