/********************************************************************************/
/*					Ficheiro: projeto1.c 										*/												
/*					Autor : João Caldeira (ist93729)							*/											
/*					Descrição : Sistema de logística de encomendas e produtos	*/
/********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ENCOMENDAS 500		/* Numero maximo de encomendas no sistema */  
#define MAX_PRODUTOS 10000		/* Numero maximo de produtos no sistema */
#define MAX_PESO 200			/* Peso maximo numa encomenda */
#define MAX_LINHA 112			/* Tamanho maximo de uma linha de input */
#define MAX_PARTICAO 4			/* Quantidade maxima de sub divisoes de uma linha de imput */
#define MAX_DESC 64				/* Tamanho maximo para a descricao de um produto */

typedef struct produto{
	/* identificador; preco; peso e quantidade do produto */
	int id, preco, peso, quantidade;
	/* descricao o produto */
	char descricao[MAX_DESC];
}Produto;
 
typedef struct encomenda{
	/* identificador; peso e numero de produtos numa encomenda */
	int id,peso,nprodutos;
	/* array que guarda uma codificacao dos detalhes para cada produto de uma encomenda */
	int prod_details[MAX_PRODUTOS]; 
}Encomenda;

/* array que guarda as encomendas do sistema */
Encomenda sistema_encomendas[MAX_ENCOMENDAS];  

/* Variavel que guarda o ultimo id de encomenda */
int id_encomendas = -1;	   

/* array que guarda os produtos do sistema */
Produto sistema_produtos[MAX_PRODUTOS];        
 
/* Variavel que guarda o ultimo id de produto */
int id_produtos = -1;

/********************************************************************************/
/***************************** Funcoes Auxiliares *******************************/
/********************************************************************************/

/* obtem do stdin uma linha de input ate encontrar o fim da string '\0' */  
void obtem_input(char input[]){
	int c, j = 0;

	getchar();
	while ((c = getchar()) != '\n')
		input[j++] = c;
	input[j] = '\0';
}

/* divide a string arg vezes, que é igual a: (numero de vezes que o caracter ":" aparece) + 1, e guarda em: final */
void trata_input(char string[], char *final[], int args){
	int j = 0;

	final[j] = strtok(string, ":");
	for (j = 1; j < args; j++)
		final[j] = strtok(NULL, ":");
}

/* recebe um natural n e verifica se corresponde a um id */
/*           de produto existente no sistema             */
int procuraProduto(int n){
	if(n <= id_produtos && id_produtos > -1)
		return 1;
	return -1;
}

/* recebe um natural n e verifica se corresponde a um id */
/* de encomenda existente no sistema           			 */
int verificaEncomenda(int n){
	if (n <= id_encomendas && id_encomendas > -1)
		return 1;
	return -1;
}

/* ordena um vetor de inteiros utilizando o algoritmo quicksort */
void quicksort(int vetor[],int esq,int dir){
   int i, j, pivot, temp;

   if(esq < dir){
      pivot = esq;
      i = esq;
      j = dir;

      while(i < j){
         while(vetor[i] <= vetor[pivot] && i < dir)
            i++;
         while(vetor[j] > vetor[pivot])
            j--;
         if(i < j){
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
         }
      }

      temp = vetor[pivot];
      vetor[pivot] = vetor[j];
      vetor[j] = temp;
      quicksort(vetor, esq, j-1);
      quicksort(vetor, j+1, dir);
   }
}

/* codifica o id e a quantidade de um produto */
/* quando adicionado a uma encomenda */
int cria_codigo(int id,int qtd){
	return MAX_PRODUTOS*qtd +id;
}

/********getters************/
int obterPesoAtualEncomenda(int id){
	return sistema_encomendas[id].peso;
}

int obterStockProduto(int id){
	return sistema_produtos[id].quantidade;
}

int obterPesoProduto(int id){
	return sistema_produtos[id].peso;
}

int obterPrecoProduto(int id){
	return sistema_produtos[id].preco;
}

char* obterDescProduto(int id){
	return sistema_produtos[id].descricao;
}

int obterIdCodigo(int codigo){
	return codigo % MAX_PRODUTOS;
}

int obterQtdCodigo(int codigo){
	return codigo / MAX_PRODUTOS;
}

/********************************************************************************/
/***************************** Funcoes Principais *******************************/
/********************************************************************************/

/* cria um produto */
Produto cria_produto(char *string[]){
	Produto produto;

	strcpy(produto.descricao,string[0]);
	produto.preco = atoi(string[1]);
	produto.peso = atoi(string[2]);
	produto.quantidade = atoi(string[3]);	
	return produto;
}

/* adiciona o produto ao sistema */
void add_produto(Produto p){
	int posicao;
	if(MAX_PRODUTOS >= id_produtos){
		id_produtos++;
		posicao = id_produtos;
		p.id = posicao;
		sistema_produtos[posicao] = p;
		printf("Novo produto %d.\n",posicao);
	}
}

/* adiciona uma quantidade ao stock de um produto */
void add_stock(char *string[]){
	int idp = atoi(string[0]);

	if (procuraProduto(idp) < 0){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
	}
	else
		sistema_produtos[idp].quantidade += atoi(string[1]);
}

/* cria encomenda */
void cria_encomenda(){
	Encomenda encomenda;
	int posicao;

	if(MAX_ENCOMENDAS >= id_encomendas){
		id_encomendas++;
		posicao = id_encomendas;
		if (posicao >= 0){
			encomenda.peso = 0;
			encomenda.nprodutos = 0;
			encomenda.id = posicao;
			sistema_encomendas[posicao] = encomenda;
			printf("Nova encomenda %d.\n", posicao);
		}
	}
}

/* coloca um produto numa encomenda */
void produtoParaEncomenda(char *string[]){
	int ide = atoi(string[0]), idp = atoi(string[1]), qtd = atoi(string[2]);

	if (verificaEncomenda(ide) < 0){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
	}
	else if(procuraProduto(idp) < 0){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
	}
	else if(obterStockProduto(idp) < qtd){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp,ide);
	}
	else if(obterPesoAtualEncomenda(ide) + (obterPesoProduto(idp) * qtd) > MAX_PESO){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
	}
	else{
		int n,i,flag = 1;
		n = sistema_encomendas[ide].nprodutos;
		for(i = 0;i < n; i++){
			if(obterIdCodigo(sistema_encomendas[ide].prod_details[i]) == idp){
				sistema_encomendas[ide].prod_details[i] += qtd * MAX_PRODUTOS;
				sistema_produtos[idp].quantidade -= qtd;
				sistema_encomendas[ide].peso += obterPesoProduto(idp) * qtd;
				flag = 0;
				break;
			}
		}
		if(flag){
			sistema_encomendas[ide].prod_details[n] = cria_codigo(idp,qtd);
			sistema_encomendas[ide].nprodutos += 1;
			sistema_encomendas[ide].peso += obterPesoProduto(idp) * qtd;
			sistema_produtos[idp].quantidade -= qtd;
		}
	}
}

/* retira uma quantidade ao stock de um produto*/
void removeStock(char *string[]){
	int idp = atoi(string[0]), qtd = atoi(string[1]);

	if(procuraProduto(idp) < 0){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
	}
	else if(obterStockProduto(idp) - qtd < 0){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
	}
	else{
		sistema_produtos[idp].quantidade -= atoi(string[1]);
	}
}

/* remove um certo produto de uma determinada encomenda */
void removeProdutoEncomenda(char *string[]){
	int ide = atoi(string[0]), idp = atoi(string[1]);

	if (verificaEncomenda(ide) < 0){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
	}
	else if(procuraProduto(idp) < 0){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
	}
	else{
		int i,nprod;
		nprod = sistema_encomendas[ide].nprodutos;
			for(i = 0;i < nprod; i++){
			if (obterIdCodigo(sistema_encomendas[ide].prod_details[i]) == idp){
				sistema_produtos[idp].quantidade += obterQtdCodigo(sistema_encomendas[ide].prod_details[i]);
				sistema_encomendas[ide].peso -= obterQtdCodigo(sistema_encomendas[ide].prod_details[i]) * obterPesoProduto(idp);
				sistema_encomendas[ide].nprodutos -= 1;
				break;
			}
		}
		for(; i < nprod; i++){
			sistema_encomendas[ide].prod_details[i] = sistema_encomendas[ide].prod_details[i+1];
		}
	}
}

/* calcula o custo de uma encomenda */
void calculaCusto(char *string[]){
	int ide = atoi(string[0]),nprod, i, precoTotal = 0;

	if (verificaEncomenda(ide) < 0){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
	}
	else{
		nprod = sistema_encomendas[ide].nprodutos;
		for(i = 0; i < nprod; i++){
			precoTotal += obterPrecoProduto(obterIdCodigo(sistema_encomendas[ide].prod_details[i])) * obterQtdCodigo(sistema_encomendas[ide].prod_details[i]);
		}
		printf("Custo da encomenda %d %d.\n",ide,precoTotal);

	}
}

/* altera o preco de um produto */
void alteraPreco(char *string[]){
	int idp = atoi(string[0]), newPreco = atoi(string[1]);

	if(procuraProduto(idp) < 0){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
	}
	else{
		sistema_produtos[idp].preco = newPreco;
	}
}

/* mostra a descricao e quantidade de um dado produto numa encomenda */
void listaProduto(char *string[]){
	int ide = atoi(string[0]), idp = atoi(string[1]);

	if (verificaEncomenda(ide) < 0){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
	}
	else if(procuraProduto(idp) < 0){
		printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
	}
	else{
		int qtd,i,nprod,flag = 0;
		char desc[MAX_DESC];
		nprod = sistema_encomendas[ide].nprodutos;
		for(i = 0; i < nprod; i++){
			if(obterIdCodigo(sistema_encomendas[ide].prod_details[i]) == idp){
				qtd = obterQtdCodigo(sistema_encomendas[ide].prod_details[i]);
				strcpy(desc,obterDescProduto(idp));
				flag = 1;
				break;
			}
		}
		if (flag)
			printf("%s %d.\n",desc,qtd);
		else
			printf("%s %d.\n",sistema_produtos[idp].descricao,0);
	}
}

/* mostra o produto com mais ocorrências e */
/* a encomenda onde se encontram as ocorrencias */
void produtoMaisEncomendado(char *string[]){
	int idp = atoi(string[0]);

	if(procuraProduto(idp) < 0){
		printf("Impossivel listar maximo do produto %s. Produto inexistente.\n",(string[0]));
	}
	else{
		int i,nencomendas,j,nprod,ide,qtd = 0;
		nencomendas = id_encomendas + 1;
		for(i = 0; i < nencomendas; i++){
			nprod = sistema_encomendas[i].nprodutos;
			for(j = 0;j < nprod; j++){
				if(obterIdCodigo(sistema_encomendas[i].prod_details[j]) == idp){
					if(obterQtdCodigo(sistema_encomendas[i].prod_details[j]) > qtd){
						qtd = obterQtdCodigo(sistema_encomendas[i].prod_details[j]);
						ide = i;
					}
					break;
				}
			}
		}
		if(qtd > 0){
			printf("Maximo produto %d %d %d.\n",idp,ide,qtd);
		}
	}
}

/* lista todos os produtos existentes no sistema pela ordem crescente do seu preco */
void listaPreco(){
	int nprod,k,i,precos[MAX_PRODUTOS];

	nprod = id_produtos + 1;
	if(nprod > 0){
		for(i = 0; i < nprod; i++){
			precos[i] = sistema_produtos[i].preco;
		}
		quicksort(precos, 0, nprod - 1) ;
	}
	printf("Produtos\n");
	k = 0;
	i = 0;
	while(i < nprod && k < nprod){
		if(precos[k] == sistema_produtos[i].preco){
			printf("* %s %d %d\n",sistema_produtos[i].descricao,sistema_produtos[i].preco,sistema_produtos[i].quantidade);
			if(k+1 < nprod && precos[k] == precos[k+1]){
				k++;
				i++;
			}
			else{
				k++;
				i = 0;
			}
		}
		else
			i++;
	}
}

/* lista todos os produtos numa encomenda pela ordem alfabetica da sua descricao */
void listaEncomenda(char *string[]){
	int ide = atoi(string[0]);

	if (verificaEncomenda(ide) < 0){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
	}
	else{
		int i,j,k;
		char temp[MAX_DESC];
		Produto copiaOrdenada[MAX_PRODUTOS];
		for(i = 0;i < sistema_encomendas[ide].nprodutos; i++){
			copiaOrdenada[i] = sistema_produtos[obterIdCodigo(sistema_encomendas[ide].prod_details[i])];			
		}
		for(i = 0; i < sistema_encomendas[ide].nprodutos; i++){
	      for(j = i+1; j < sistema_encomendas[ide].nprodutos; j++){
	         	if(strcmp(copiaOrdenada[i].descricao,copiaOrdenada[j].descricao)>0){
		            strcpy(temp,copiaOrdenada[i].descricao);
		            strcpy(copiaOrdenada[i].descricao,copiaOrdenada[j].descricao);
		            strcpy(copiaOrdenada[j].descricao,temp);
         		}
      		}
		}
		i = 0;
		k = 0;
		printf("Encomenda %d\n",ide);
		while(i < sistema_encomendas[ide].nprodutos && k < sistema_encomendas[ide].nprodutos){
			if( strcmp(copiaOrdenada[k].descricao, obterDescProduto(obterIdCodigo(sistema_encomendas[ide].prod_details[i]))) == 0){
				printf("* %s %d %d\n",obterDescProduto(obterIdCodigo(sistema_encomendas[ide].prod_details[i])),obterPrecoProduto(obterIdCodigo(sistema_encomendas[ide].prod_details[i])),obterQtdCodigo(sistema_encomendas[ide].prod_details[i]));
				if (k+1 < sistema_encomendas[ide].nprodutos && strcmp(copiaOrdenada[k].descricao,copiaOrdenada[k+1].descricao) == 0){
					k++;
					i++;
				}
				else{
					k++;
					i = 0;
				}
			}
			else
				i++;				
		}
	}
}

/* recebe o input dos comandos e controla as suas expecificacoes ate ler o comando 'x', que indica o fim do programa */
int main(){
	int comando;
	char input[MAX_LINHA], *inputRefinado[MAX_PARTICAO];
	while((comando = getchar()) != 'x'){
		switch(comando){
			case 'a':
				obtem_input(input);
				trata_input(input,inputRefinado,MAX_PARTICAO);
				add_produto(cria_produto(inputRefinado));
				break;

			case 'q':
				obtem_input(input);
				trata_input(input,inputRefinado,2);
				add_stock(inputRefinado);
				break;

			case 'N':
				cria_encomenda();
				break;

			case 'A':
				obtem_input(input);
				trata_input(input,inputRefinado,3);
				produtoParaEncomenda(inputRefinado);
				break;

			case 'r':
				obtem_input(input);
				trata_input(input,inputRefinado,2);
				removeStock(inputRefinado);
				break;

			case 'R':
				obtem_input(input);
				trata_input(input,inputRefinado,2);
				removeProdutoEncomenda(inputRefinado);
				break;

			case 'C':
				obtem_input(input);
				trata_input(input,inputRefinado,1);
				calculaCusto(inputRefinado);
				break;

			case 'p':
				obtem_input(input);
				trata_input(input,inputRefinado,2);
				alteraPreco(inputRefinado);
				break;

			case 'E':
				obtem_input(input);
				trata_input(input,inputRefinado,2);
				listaProduto(inputRefinado);
				break;

			case 'm':
				obtem_input(input);
				trata_input(input,inputRefinado,1);
				produtoMaisEncomendado(inputRefinado);
				break;

			case 'l':
				listaPreco();
				break;

			case 'L':
				obtem_input(input);
				trata_input(input,inputRefinado,1);
				listaEncomenda(inputRefinado);
				break;
		}
	}
	return 0;
}