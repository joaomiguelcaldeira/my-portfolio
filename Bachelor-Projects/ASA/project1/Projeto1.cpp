#include <stdio.h>
#include <stdlib.h>
#include<bits/stdc++.h>

using namespace std; 
class Graph 
{ 
    int V;              /* Numero de Vertices */
    list<int> *adj;     /* Lista de Vertices Adjacentes */
    vector<int> alunos; /* Vetor que guarda as notas dos alunos */

public: 
    Graph(int V,vector<int> alunos);            /* Construtor do grafo */
    void addEdge(int v, int w);                 /* Adiciona um Vertice ao Grafo */ 
    void DFS();                                 /* Inicia a DFS no Grafo */ 
    void DFSUtil(int s, vector<bool> &visited); /* Realizia a DFS comecando no Vertice indicado como argumento */
}; 

/* Construtor do grafo */  
Graph::Graph(int V,vector<int> alunos) 
{ 
    this->V = V; 
    adj = new list<int>[V];
    this->alunos = alunos;
}

/* Adiciona o vertice w na Lista de Vertices Adjacentes de v */  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w);
} 
  
/* Realizia a DFS comecando no Vertice indicado como argumento */ 
void Graph::DFSUtil(int s, vector<bool> &visited) 
{ 
    /* Inicializacao do Stack para a DFS partindo do Vertice s */ 
    stack<int> stack;  
    stack.push(s);

    /*Guardar Vertice Inicial*/
    int starter = s;

    /*Ciclo da DFS*/
    while (!stack.empty()) 
    { 
        /* Escolhe e retira o ultimo elemento do Stack*/ 
        s = stack.top(); 
        stack.pop();

        /* Marcar o Vertice atual como visitado na lista de visitados. */ 
        if (!visited[s]) 
        {
            visited[s] = true; 
            /* Iterar a Lista de Vertices Adjacentes a S*/
            /* Verificar se o Vertice Adjacente (aluno), tem uma nota melhor que o vertice s */
            /* Se esta condicao se verificar reinicia a DFS no vertice s, atualizando a nota do aluno (s) */
            /* Verificar se o Vertice Adjacente (aluno) não foi visitado mas tem nota menor que o aluno (s) */
            /* Se esta condicao se verificar, colocar o Vertice Adjacente no Stack a explorar */ 
            for (auto i = adj[s].begin(); i != adj[s].end(); ++i){
                if (alunos[*i-1] > alunos[s-1]){
                    fill(visited.begin(),visited.end(),false);
                    stack.push(starter);
                    alunos[s-1] = alunos[*i-1];
                    break; 
                }
                if (!visited[*i] && alunos[*i-1] <= alunos[s-1]){
                    stack.push(*i);
                }
            }
        }
    }
}

/* Inicia a DFS no Grafo */ 
void Graph::DFS() 
{ 
    /* Inicializar os Vertices como nao visitados */
    vector<bool> visited(V, false);
    /* Realizar a DFS para todos os Vertices do Grafo ainda nao visitados */   
    for (int i = 1; i < V; i++) 
        if (!visited[i]) 
            DFSUtil(i, visited);

    /* Imprimir no stdout as notas atualizadas dos alunos */
    for (int j = 0; j < (int) alunos.size(); j++) {
        std::cout << alunos.at(j) << '\n';
    }
    /* Libertar a Lista de Vertices Adjacentes alocada */
    delete[] adj;
}


/* Obtem do stdin as notas dos alunos e retorna um vetor */
/* com as notas dos alunos por ordem de insercao */
vector<int> trataAlunos(int n){
    int nota,i = 0;
    vector<int> alunos;
    while(n > i){
        scanf("%d",&nota);
        alunos.push_back(nota);
        i++;
    } 
    return alunos;
} 

/* Adiciona as ligacoes ao grafo */
void trataRelacoes(int n,Graph g){
    int v,e,i = 0;
    while(n > i){
        scanf("%d %d",&v,&e);
        g.addEdge(v,e);
        i++;
    }
}

/* Programa */
int main(){
	int nalunos,nrelacoes;
    /* Obtem do stdin o numero de alunos e o numero de relacoes entre os mesmos */
	scanf("%d,%d",&nalunos,&nrelacoes);
    /*numero de alunos+1 excluindo assim o vertice "0"*/            
	Graph g(nalunos+1,trataAlunos(nalunos)); 
    trataRelacoes(nrelacoes,g);                    
    g.DFS();
    return 0;
}