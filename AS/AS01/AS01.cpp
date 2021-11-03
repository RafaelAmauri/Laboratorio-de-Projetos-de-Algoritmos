// Rafael Amauri Diniz Augusto -- 651047
// Complexidade: O(N), onde N é o número de pares de números na entrada

#include <iostream>

// Retorna um unsigned long int, pois os valores podem ser muito grandes
unsigned long int fac(int num)
{
	unsigned long int res = 1;

	// Para cada número <num>, multiplicar a variavel res por cada número entre 1 e <num>;
	for(short i = 1; i < num; i++)
		res = res * (i+1);

	return res;
}


int main()
{
	short num1, num2;
	
	// Scanear 2 valores até encontrar um EOF
	while(fscanf(stdin, "%hd %hd", &num1, &num2) != EOF)
		std::cout <<  fac(num1) + fac(num2) << "\n";

	return 0;
}
