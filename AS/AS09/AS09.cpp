// Autor: Rafael Amauri
// Tarefa: Maçãs
// ID da Tarefa: 1517
// URL: https://www.beecrowd.com.br/judge/pt/problems/view/1517
// Complexidade: O(N^2), onde N é o número de macas que caem


#include <iostream>


// Declaracao da classe maca, que indica quantas mapa caem em qual posicao em qual tempo
class Maca
{
	private:
		// Posicao no eixo X
		short x;
		// Posicao no eixo Y
		short y;
		// Tempo em que a maca cai
		short tempo_queda;
		// Quantidade de mapa
		short quantidade;

	public:
	// getter e setter para a posicao no eixo x
		short get_pos_x(){ return this->x; }

		void set_pos_x(short x){ this->x = x; }

	// getter e setter para a posicao no eixo y
		short get_pos_y(){ return this->y; }

		void set_pos_y(short y){ this->y = y; }

	// getter e setter para o tempo que a maca cai
		short get_tempo(){ return this->tempo_queda; }

		void set_tempo(short tempo){ this->tempo_queda = tempo; }
		
	// getter e setter para a quantidade de mapa que caem
		short get_quant(){ return this->quantidade; }
		
		void set_quant(short quantidade){ this->quantidade = quantidade; }
};

// Calcula a diferenca entre o eixo X de duas macas
int diferenca_pos_x_macas(Maca a, Maca b);

// Calcula a diferenca entre o eixo Y de duas macas
int diferenca_pos_y_macas(Maca a, Maca b);


int main (){

 	int N = 0, M = 0, K = 0, i = 0, j = 0, posicao = 0, maximo = 0;
	bool end = false;

 	while(!end){

		std::cin >> N >> M >> K;
		
		// Sai do programa se N, M e K forem igual a zero
 		if(N == 0 && M == 0 && K == 0)
		{
 			end = true;
			continue;
		}

		// O mapa da area, com K macas
		Maca mapa[K];

		// Posicao x, y e tempo
		int x, y, tempo;

		for (i = 1; i <= K; i++){
			std::cin >> x >> y >> tempo;

			mapa[i].set_pos_x(x);
			mapa[i].set_pos_y(y);
			mapa[i].set_tempo(tempo);
		}

		// Posicao de Rafael
		std::cin >> x >> y;

		mapa[0].set_pos_x(x);
		mapa[0].set_pos_y(y);
		mapa[0].set_tempo(0);


		i = K;
		do
		{
			posicao = i;
			mapa[posicao].set_quant(1);

			maximo = 0;

			for(j = (posicao+1); j <= K; j++)
			{
				
				// Mostra quantas mapa Rafael consegueria pegar na posicao onde ele esta
				int distancia_x = diferenca_pos_x_macas(mapa[i], mapa[j]);
				int distancia_y = diferenca_pos_y_macas(mapa[i], mapa[j]);

				int distancia;
				
				if(distancia_x > distancia_y)
				{
					distancia = distancia_x; 
				}
				else
				{
					distancia = distancia_y;
				}

				int tempo   =  mapa[j].get_tempo() - mapa[i].get_tempo();

				if (distancia <= tempo && mapa[j].get_quant() > maximo)
				{
					maximo = mapa[j].get_quant();
				}
			}

			if (maximo != 0)
			{
				mapa[posicao].set_quant(1 + maximo);
			}
			
			i--;
		}while(i >= 0);

		std::cout << mapa[0].get_quant() - 1 << "\n";
	}

	return 0;
}


int diferenca_pos_y_macas(Maca a, Maca b)
{
	int dif = a.get_pos_y() - b.get_pos_y();

	if(dif < 0)
	{
		dif = dif * -1;
	}

	return dif;
}


int diferenca_pos_x_macas(Maca a, Maca b)
{
	int dif = a.get_pos_x() - b.get_pos_x();

	if(dif < 0)
	{
		dif = dif * -1;
	}

	return dif;
}