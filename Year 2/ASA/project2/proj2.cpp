/************************************************ Joao Caldeira ist193729 Grupo:tp020 *************************************************/
using namespace std;
#include <iostream>
#include  <vector>
#include <queue>

/* estrutura que guarda o fluxo de cada vertice */
struct FlowEdge {
    
    int v, u;
    
    long long cap, flow = 0;
    
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

/* estrutura que processa o algoritmo de Dinic */
struct Dinic {
    
    const long long flow_inf = 1e18;
    
    vector<FlowEdge> edges;
    
    vector<vector<int>> adj;
    
    int n, m = 0;
    
    int s, t;
    
    vector<int> level, ptr;
    
    queue<int> q;

    /* construtor */
    Dinic(int n, int s, int t) : n(n), s(s), t(t){
            
        adj.resize(n);
            
        level.resize(n);
            
        ptr.resize(n);
    }

    /* adiciona arco ao vertice */
    void add_edge(int v, int u, long long cap) {
            
        edges.emplace_back(v, u, cap);
            
        edges.emplace_back(u, v, 0);
            
        adj[v].push_back(m);
            
        adj[u].push_back(m + 1);
            
        m += 2;
    }

    bool bfs() {
            
        while (!q.empty()) {
                
            int v = q.front();
                
            q.pop();
                
            for (int id : adj[v]) {
                    
                if (edges[id].cap - edges[id].flow < 1) { 
                        
                    continue;
                }
                    
                if (level[edges[id].u] != -1) {
                        
                    continue;
                }
                    
                level[edges[id].u] = level[v] + 1;
                    
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
            
        if (pushed == 0) {
               
            return 0;
        }
            
        if (v == t) {
                
            return pushed;
        }
            
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
                
            int id = adj[v][cid];
                
            int u = edges[id].u;
                
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) {
                    
                continue;
            }
                
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
                
            if (tr == 0) {
                    
                continue;
            }    
                
            edges[id].flow += tr;
                
            edges[id ^ 1].flow -= tr;
                
            return tr;
        }
        return 0;
    }

    /* funcao que processa o fluxo do grafico */
    long long flow() {
            
        long long f = 0;
            
        while (true) {
                
            fill(level.begin(), level.end(), -1);
                
            level[s] = 0;
                
            q.push(s);
                
            if (!bfs()) {
                    
                break;
            }
                
            fill(ptr.begin(), ptr.end(), 0);
                
            while (long long pushed = dfs(s, flow_inf)) {
                    
                f += pushed;
            }
        }
        return f;
    }

    /* funcao auxiliar que dado uma avenida e uma rua codifica a posicao */
            /* num inteiro que representa o numero do vertice */
    int obtemPosicao(int avenida, int rua, int tam){
        return avenida + tam *(rua - 1);
    }   

    /* funcao que constroi o grafo */
    void trataMatriz(int nAvenidas, int nRuas) {

        for(int r = 1; r <= nRuas; r++){
            for(int a = 1; a <= nAvenidas;a++){
                if(obtemPosicao(a,r,nAvenidas) % 2 != 0)
                    add_edge(obtemPosicao(a,r,nAvenidas), obtemPosicao(a,r,nAvenidas) + 1, 1);
                else{
                    if(a != 2)
                        add_edge(obtemPosicao(a,r,nAvenidas),obtemPosicao(a,r,nAvenidas) - 3,1);
                    if(a != nAvenidas)
                        add_edge(obtemPosicao(a,r,nAvenidas),obtemPosicao(a,r,nAvenidas) + 1,1);
                    if(r != 1)
                        add_edge(obtemPosicao(a,r,nAvenidas),obtemPosicao(a,(r-1),nAvenidas) - 1,1);
                    if(r != nRuas)
                        add_edge(obtemPosicao(a,r,nAvenidas),obtemPosicao(a,(r+1),nAvenidas) - 1,1);
                }
            }
        }
    }
    
    /* funcao que liga o super sink a todos os cidadaos */
        /* e liga o super target a todos os mercados */                                                                                     
    void setSinkTarget(int nMercados, int nCidadaos, int nAvenidas) {                  
        int a,r;                                                                           
        for (int i = 0; i < nMercados; i++)                                            
        {
            scanf("%d %d", &a, &r);
            add_edge(obtemPosicao(2*a,r,nAvenidas), t, 1);
        }
        for (int i = 0; i < nCidadaos; i++)
        {
            scanf("%d %d", &a, &r);
            add_edge(s,obtemPosicao(2*a - 1,r,nAvenidas), 1);
        }
        
    }
};

    /* funcao que processa o input */
/* inicia o grafo e a resolucao do fluxo maximo */
void processInput(){
    int nAvenidas, nRuas, nMercados, nCidadaos;
    scanf("%d %d\n%d %d",&nAvenidas,&nRuas,&nMercados,&nCidadaos);
    int V = nAvenidas*nRuas*2 + 2;

    Dinic g(V,0,V-1);
    g.trataMatriz(nAvenidas*2, nRuas);
    g.setSinkTarget(nMercados, nCidadaos, nAvenidas*2);

    printf("%lld\n",g.flow());
}

/* Programa */
int main() {
    processInput();
    return 0;
}