#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

struct musicas {
	long long plays;
	char nome[60], artista[100], genero[20];
	int ranking;
};

int particiona (musicas v[], int comeco, int fim){
	musicas pivo = v[fim];
	int j = comeco, i;
	
	for (i=comeco; i < fim; i++){
		if (v[i].plays > pivo.plays){
			swap (v[j], v[i]);
			j++;
		}
	}
	swap (v[j],v[fim]);
	return j;
}

void quicksort (musicas v[], int pos_pivo, int fim){
	int pos_novo_pivo;
	if (pos_pivo < fim){
		pos_novo_pivo = particiona (v,pos_pivo,fim);
		quicksort (v,pos_pivo,pos_novo_pivo-1);
		quicksort (v,pos_novo_pivo+1,fim);
	}
}

void escrever_ranking (musicas musica[], int posicao_inicial, int posicao_final){
	int i;

	for (i= posicao_inicial; i < posicao_final; i++){
		cout <<i+1 <<"º: " <<musica[i].nome << "\t"<<musica[i].artista<<"\t" << musica[i].plays<<"\t"<< musica[i].genero << endl;
	}
}

void buscarPelonome (musicas musica[], string nome_busca, int tamanho){
	int x = nome_busca.size(), i, cont=0,tamanho_nome, j, musicaencontrada=0;

	for (i =0; i < tamanho; i++){
		tamanho_nome = strlen(musica[i].nome);
		if (tamanho_nome == x){
			cont =0;
				for (j =0; j < x; j++){
					if (tolower (nome_busca[j]) == tolower (musica[i].nome[j])){
						cont++;
					}
				}
			if (cont == x){
				cout <<i+1 <<"º: " <<musica[i].nome << "\t"<<musica[i].artista<<"\t" << musica[i].plays<<"\t"<< musica[i].genero << endl;
				musicaencontrada++;
			}
		}
	}
	if (musicaencontrada==0){
		cout <<"Essa musica nao se encontra na lista atual ";
	}
}

void buscarGenero (string busca_genero, int tamanho, musicas musica[]){
	int i, generobuscado=0; 
	for(i = 0; i < tamanho; i++){
		if(busca_genero.size() == strlen(musica[i].genero) and tolower(busca_genero[0]) == tolower(musica[i].genero[0]) and tolower(busca_genero[1]) == tolower(musica[i].genero[1])){
			cout << i+1<<"º: " << musica[i].nome << "\t" << musica[i].artista << "\t" << musica[i].plays << "\t" << musica[i].genero<<"\t" << endl;
			generobuscado++;
		}
	}
	if(generobuscado == 0){
    cout << "Nenhuma musica desse genero foi encontrada";
	}
}

void buscarPeloartista (musicas musica[], string busca_artista, int tamanho){
	int tamanho_busca = busca_artista.size(), i, j=0, cont, tamanho_artistaMusica, artista_encontrado=0;

	for (i=0; i < tamanho; i++){
		tamanho_artistaMusica = strlen(musica[i].artista);
		cont =0;
		j=0;
		while (j < tamanho_artistaMusica){
			if (musica[i].artista[j] != ','){
				if ( tolower(musica[i].artista[j]) ==tolower (busca_artista[cont])){
					cont++;
				}
			}
			else if((musica[i].artista[j] = ',') and (cont != tamanho_busca)) {
				j++;
				cont =0;
				if ( tolower(musica[i].artista[j]) ==tolower (busca_artista[cont])){
					cont++;
				}
			}	
		j++;
		}
		if (cont == tamanho_busca){
			artista_encontrado++;
			cout <<i+1 <<"º: " <<musica[i].nome << "\t"<<musica[i].artista<<"\t" << musica[i].plays<<"\t"<< musica[i].genero << endl;
		}
	}
	if (artista_encontrado ==0){
    cout <<"O artista pesquisado nao possui musicas no top 100 ou listadas" << endl;
	}

}

void buscarRanking (int tamanho, int buscaR, musicas musica[]){
	int i;
	for(i = 0; i < tamanho; i++){
		if(buscaR == (i+1)){
			cout << i+1 << "º: " << musica[i].nome << "\t" << musica[i].artista << "\t" << musica[i].plays << "\t" << musica[i].genero << endl;
		}
	}
}

musicas* aumentar_vetor(musicas *vetor, int &tamanho, int aumentar){
	int i;
	musicas *musica_aux;
	
	musica_aux = new musicas [aumentar+tamanho];
	
	for(i=0; i<tamanho; i++){
		musica_aux[i] = vetor[i];
	}
	
	tamanho = tamanho+aumentar;
	
	delete [] vetor;
	return musica_aux;
} 

musicas* diminuir_vetor (musicas vetor[], int &tamanho){
	int i;
	musicas *novo_vetor;
	
	novo_vetor = new musicas [tamanho-1];
	
	for (i=0; i < tamanho-1;i++){
		novo_vetor[i]=vetor[i];
	}
	tamanho--;
	
	delete [] vetor;
	return novo_vetor;
}

void escrever_csv (musicas musica[], int tamanho){
	int i;
	ofstream escrever ("top100musicas.csv");
	
	for (i=0; i < tamanho; i++){
		escrever <<musica[i].nome<<','<<'"'<<musica[i].artista<<'"'<<','<<musica[i].plays<<','<<musica[i].genero<<endl;
	}
}

musicas* aumentar_vetor_1(musicas musica[],int &tamanho){
	int i;
	musicas *novo_vetor;
	
	novo_vetor = new musicas [tamanho+1];
	
	for (i=0; i < tamanho;i++){
		novo_vetor[i]=musica[i];
	}
	tamanho++;
	
	delete [] musica;
	return novo_vetor;
}

int main(){
	int tamanho=1, aumentar;
	musicas *musica;
	musica = new musicas [tamanho];
	string busca_genero, busca_nome, busca_artista;
	int i=0, opcao, opcaovisualizar, opcaobusca, posicao_final, posicao_inicial, buscaR, opcaoexcluir;

	ifstream ler("top100musicas.csv");

	if (not(ler))
		cout <<"Arquivo não encontrado";

	else{

		while (ler.getline (musica[i].nome,60,',')){
			ler.ignore();
			ler.getline (musica[i].artista,100, '"');
			ler.ignore();
			ler >> musica[i].plays;
			ler.ignore();
			ler.getline (musica[i].genero,20);
			
			i++;
			musica=aumentar_vetor_1(musica,tamanho);

		}
		
		musica=diminuir_vetor(musica,tamanho);
		
		
		do{
			quicksort(musica,0,tamanho);
			cout << "======================"<< endl; 
			cout << "         MENU         "<< endl;
			cout << "======================"<< endl;
			cout << "1 - BUSCAR MUSICA" << endl; 
			cout << "2 - INSERIR MUSICA" << endl;
			cout << "3 - VISUALIZAR MUSICAS" << endl;
			cout << "4 - EXCLUIR MUSICA" << endl; 
			cout << "5 - ENCERRAR PROGRAMA" << endl; 
			cout << "Opcao escolhida: ";
			cin >> opcao; 
			cout << "======================"<< endl;
        
			fstream gravar;

			switch(opcao){
				case 1: 
					cout << "1: Busca por genero" << endl; 
					cout << "2: Busca por artista" << endl;
					cout << "3: Busca por ranking" << endl;
					cout << "4: Busca por nome da musica" << endl;
					cout << "Opcao escolhida: ";
					cin >> opcaobusca;

					switch(opcaobusca){
					
						case 1: 
							cout <<"Deseja ver musicas de qual genero? ";
							cin >> busca_genero; 
							buscarGenero(busca_genero, tamanho, musica);
							break;
							
						case 2: 
							cout <<"Qual artista voce deseja encontrar?";
							cin.ignore();
							getline (cin, busca_artista);
							buscarPeloartista(musica, busca_artista, tamanho);
							break;
							
						case 3:
							cout << "Informe um numero referente ao ranking: ";
							cin >> buscaR; 
							buscarRanking(tamanho, buscaR, musica);
							break;
							
						case 4:
							cout <<"Qual musica voce deseja encontrar?";
							cin.ignore();
							getline (cin, busca_nome);
							buscarPelonome(musica, busca_nome, tamanho);
							break;
							
						default: 
							cout << "Opcao invalida" << endl;
					}
					break;

				case 2:// inserir musica           
					cout << "Quantas musicas deseja inserir?" << endl;
					cin >> aumentar;
					musica = aumentar_vetor(musica, tamanho, aumentar);
					cout<< "escreva da seguinte forma: nome da musica," << '"'<<"nome do artista"<<'"'<<",numero de plays,genero da musica"<< endl <<"Numero maximo de caracteres: nome da musica = 60, nome do artista = 100, gênero = 20"<< endl;

					for (i= tamanho-aumentar; i< tamanho; i++){
						cin.ignore();
						cin.getline(musica[i].nome, 60, ',');
						cin.ignore();
						cin.getline(musica[i].artista, 100, '"');
						cin.ignore();
						cin >> musica[i].plays;
						cin.ignore();
						cin.getline (musica[i].genero,20);      
					}
            
					quicksort(musica,0,tamanho);
					escrever_csv(musica,tamanho);
					
					break;

				case 3: 
					cout << "1: Listar todas as musicas" << endl;
					cout << "2: Listar musicas do top100" << endl;
					cout << "3: Listar trecho do top100" << endl; 
					cout << "Opcao escolhida: ";
					cin >> opcaovisualizar;

					switch(opcaovisualizar){
						case 1: //listar todas as musicas;
							posicao_inicial = 0;
							posicao_final = tamanho;
							escrever_ranking (musica, posicao_inicial, posicao_final);
							break;

						case 2: //listar musicas do top100;
							posicao_inicial = 0;
							posicao_final = 100;
							escrever_ranking (musica, posicao_inicial, posicao_final);
							break; 

						case 3: //listar trecho do top100;
							cout<< "Informe a posicao inicial e a posicao final, respectivamente: ";
							cin>> posicao_inicial >> posicao_final;                
							escrever_ranking (musica, (posicao_inicial-1), (posicao_final));
							break;

						default: 
							cout << "Opcao invalida" << endl;
					}
					break;
					
				case 4: //excluir musica;
					cout << "Digite 1 para excluir uma musica pela sua posicao na lista ou 2 para excluir uma musica inserindo seu nome: ";
					cin >> opcaoexcluir;
					
					switch (opcaoexcluir){
						
						case 1:
							int posicao_excluir; 
							cout << "Digite a posicao da musica que deseja excluir: ";
							cin >> posicao_excluir;
							if (posicao_excluir > tamanho){
								cout <<"Posicao invalida"<<endl;
							}
							else{
								int b;
								for(b = 0; b< tamanho; b++){
									if(b == posicao_excluir-1){
										musica[b].plays = musica[tamanho-1].plays-1;
									}
								}
								quicksort (musica,0,tamanho);
								musica=diminuir_vetor(musica,tamanho);
								cout <<"Musica excluida com sucesso"<<endl;
								escrever_csv(musica,tamanho);
							}
							
							break;
						
						case 2:
							string nome_excluir;
							cout << "Digite o nome da musica que deseja excluir: ";
							cin.ignore(); 
							getline(cin,nome_excluir);
							int x = nome_excluir.size(), d, cont=0,tamanho_nome, f, musicaencontrada=0;

							for (d =0; d < tamanho; d++){
								tamanho_nome = strlen(musica[d].nome);
								if (tamanho_nome == x){
									cont =0;
									for (f =0; f < x; f++){
										if (tolower (nome_excluir[f]) == tolower (musica[d].nome[f])){
											cont++;
										}
									}
								if (cont == x){
									musica[d].plays = musica[tamanho-1].plays-1;
									musicaencontrada++;
								}
							}
						}
						if (musicaencontrada==0){
							cout <<"Essa musica nao se encontra na lista atual "<<endl;
						}
						else{
							quicksort (musica,0,tamanho);
							musica=diminuir_vetor(musica,tamanho);
							cout <<"Musica excluida com sucesso"<<endl;
							escrever_csv(musica,tamanho);
						}

						break;
				
					}
					break;

				case 5:
					cout <<"Encerrando programa ...";
					break;

				default:
					cout <<"Opcao invalida"<<endl;
			}
		}while (opcao != 5);
	}

	delete [] musica;
	return 0;
}
