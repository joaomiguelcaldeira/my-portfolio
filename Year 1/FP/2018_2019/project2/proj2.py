#João Caldeira TP-93729
from typing import Tuple


def cria_celula(x): #(-1,0,1)-->celula  a funcao cria uma celula
    if x==0:
        return "inativo"
    if x==1:
        return "ativo"
    if x==-1:
        return "incerto"
    else:
        raise ValueError("cria_celula: argumento invalido.") #se o valor dado nao estiver dentro do conjunto(-1,0,1), a funcao da erro
                                                              
    
        
def obter_valor(cel): #celula-->(-1,0,1)   a funcao obtem o valor correspondente a celula argumento
    if cel=="inativo":
        return 0
    if cel=="ativo":
        return 1
    if cel=="incerto":
        return -1
    else:
        raise ValueError("obter_valor: argumento invalido")  #se o argumento nao for uma celula, ou seja uma string que so poder ser:(incerto,inativo ou ativo) a funcao da erro
    
def inverte_estado(cel): #celula-->celula    inverte o estado de uma celula
    if obter_valor(cel)==0:    #a funcao obter_valor permite obter o valor da celula argumento
        return "ativo"         #a funcao da return na celula "ativo" caso a celula original seja "inativo" e vice-versa
    if obter_valor(cel)==1:    
        return "inativo"
    if obter_valor(cel)==-1:
        return "incerto"       #no caso do argumento ser uma celula "incerto" a funcao retorna uma celula igual
    else:
        raise ValueError("inverte: argumento invalido")   #se o argumento nao for uma celula, ou seja uma string que so poder ser:(incerto,inativo ou ativo) a funcao da erro

def eh_celula(u): #universal-->logico    a funcao verifica se o argumento e uma celula
    if u=="incerto" or u=="ativo" or u=="inativo": 
        return True
    else:
        return False     #se o argumento nao for uma celula, ou seja uma string que so poder ser:(incerto,inativo ou ativo) a funcao da return false

def celulas_iguais(celx,cely): #celula,celula-->logico    a funcao verifica se os argumentos sao celulas iguais
    if eh_celula(celx) and eh_celula(cely):    #verifica se ambos os elementos sao celulas
        if obter_valor(celx)==obter_valor(cely): #verifica se as celulas sao iguais
            return True
        else:
            return False
    else:
        return False
def celula_para_str(cel): #celula-->cad. caracteres   a funcao recebe uma celula e transforma no valor correspondente em string
    if eh_celula(cel):    #verifica se o argumento e celula
        if cel=="incerto":
            return "-1"
        if cel=="ativo":
            return "1"
        if cel=="inativo":
            return "0"
    else:
        raise ValueError("celula_para_str: argumento invalido")

def cria_coordenada(l,c):#N2-->coordenada  a funcao recebe dois numeros e devolve uma coordenada
    num_valid=(0,1,2)    #conjunto de numeros validos para os argumentos
    if l in num_valid and c in num_valid:  #verifica se os argumentos estao dentro do conjunto de numeros validos
        return l,c
    else:
        raise ValueError("cria_coordenada: argumentos invalidos.")

def eh_coordenada(arg):#universal-->logico  a funcao verifica se o argumento e uma coordenada
    num_valid=(0,1,2)    #conjunto de numeros validos para os argumentos
    if type(arg)==tuple:    
        if len(arg)==2:
            for e in arg:
                if e in num_valid:
                    return True
                else:
                    return False
        else:
            return False
    else:
        return False

def coordenada_linha(l):#coordenada-->N funcao devolve o natural correspondente a linha da coordenada
    if eh_coordenada(l):
        return l[0]

def coordenada_coluna(c):#coordenada-->N funcao devolve o natural correspondente a coluna da coordena
    if eh_coordenada(c):
        return c[1]

def coordenadas_iguais(c1,c2):#coordenada x coordenada-->logico  a funcao verifica se os argumentos sao coordenadas iguais
    if eh_coordenada(c1) and eh_coordenada(c2):  #verifica se os argumentos sao coordenadas
        if c1[0]==c2[0] and c1[1]==c2[1]:
            return True
        else:
            return False
    else:
        return False

def coordenada_para_str(c):#coordenada-->cad.caracteres  a funcao devolve uma coordenada em string
    if eh_coordenada(c):   #verifica se e coordenada
        return str (c)

def eh_coordenada_tabuleiro(c):#coordenada-->logico  a funcao verifica se uma coordenada aplicavel a um tabuleiro
    if eh_coordenada(c):       #verifica se o argumento e uma coordenada
        if not (c[0]==2 and c[1]==0):  #verifica se a coordenada e (2,0)
            return True
        else:
            return False
    else:
        return False

def eh_tabuleiro(arg):#universal-->logico   a funcao verifica se o argumento e um tabuleiro
    if type(arg)==tuple:  #verifica se o elemento e um tuple                     
        if len(arg)==3: #verifica o tamanho do tuplo                     
            v1=arg[0]                                          
            v2=arg[1]
            v3=arg[2]
            if type(v1)!=tuple or type(v2)!=tuple or type(v3)!=tuple: #verifica se os elementos do tuplo principal sao tambem tuplos
                return False
            if len(v1)!=3 or len(v2)!=3 or len(v3)!=2: #verifica o tamanho dos tuplos do tuplo principal       
                return False  
            for e in v1:    # verifica os elementos consituintes dos tuplos
                if not(e==-1 or e==0 or e==1):              
                    return False
            for e in v2:
                if not(e==-1 or e==0 or e==1):
                    return False
            for e in v3:
                if not(e==-1 or e==0 or e==1):
                    return False
            else:
                return True   
        return False
    return False


def tabuleiro_inicial():#()-->tabuleiro   a funcao da return no tabuleiro inicial
    return ((-1,-1,-1),(0,0,-1),(0,-1))

def tabuleiro_para_str(s):#tabuleiro-->cad.caracteres  a funcao recebe um tabuleiro e devolve a representacao do tabuleiro em jogo
    tupaux=()   #tuplo auxiliar que ira ter os elementos do tabuleiro sendo que -1=x ,qubit incerto 
    if eh_tabuleiro(s):   #verifica se e tabuleiro
        for e in s:
            for v in e:
                if v==-1: #verifica os elementos do tabuleiro e devolve o qubit incerto
                    v='x' 
                    tupaux+=(v,) 
                else:
                    tupaux+=(v,)
        return '+-------+\n|...'+str(tupaux[2])+'...|\n|..'+str(tupaux[1])+'.'+str(tupaux[5])+'..|\n|.'+str(tupaux[0])+'.'+str(tupaux[4])+'.'+str(tupaux[7])+'.|\n|..'+str(tupaux[3])+'.'+str(tupaux[6])+'..|\n+-------+'
    else:
        raise ValueError("tabuleiro_para_str: argumentos invalidos")

def tabuleiro_dimensao(t):#tabuleiro-->N   a funcao recebe um tabuleiro e devolve a sua dimensao
    if eh_tabuleiro(t): #verifica se o argumento e um tabuleiro
        linha=0   #contador da dimensao
        for e in t:
            linha+=1
        return linha
    else:
        return False

def tabuleiro_celula(t,coor):#tabuleiro x coordenada-->celula   a funcao recebe um tabuleiro e uma coordenada e devolve a celula presente na coordenada desse tabuleiro
    if eh_tabuleiro(t) and eh_coordenada_tabuleiro(coor): #verifica se os argumentos sao de facto tabuleiro e coordenadas
        x=coor[0]
        y=coor[1]
        if x!=2:           
            return cria_celula(t[x][y])
        else:                #se a coordenada for do tipo(2,y) decrementa-se o coordenada y em 1 pois a coordenada(2,0) nao existe
            y=y-1
            return cria_celula(t[x][y])
    else:
        raise ValueError("tabuleiro_celula: argumentos invalidos")
    
def tabuleiro_substitui_celula(t,cel,coor):#tabuleiro x celula x coordenada-->tabuleiro    a funcao troca a celula argumento pela celula da coordenada do tabuleiro argumento
    if eh_tabuleiro(t) and eh_coordenada_tabuleiro(coor) and eh_celula(cel): #verifica se os argumentos sao tabuleiro, coordenada e celula respetivamente
        x=coor[0]
        y=coor[1]
        if x!=2:
            t=transform_tuple_lista(t)           #transforma o tabuleiro em lista para se poderem realizar operacoes mais facilmente
            t[x][y]=obter_valor(cel)             
            return transform_lista_tuple(t)      #retorna o novo tabuleiro de lista em tuplo
        else:                                    #se a coordenada for do tipo(2,y) decrementa-se o coordenada y em 1 pois a coordenada(2,0) nao existe
            y=y-1 
            t=transform_tuple_lista(t)           #transforma o tabuleiro em lista para se poderem realizar operacoes mais facilmente
            t[x][y]=obter_valor(cel)
            return transform_lista_tuple(t)      #retorna o novo tabuleiro de lista em tuplo
    else:
        raise ValueError("tabuleiro_substitui_celula: argumentos invalidos")
    
def tabuleiro_inverte_estado(t,coor):#tabuleiro x coordenada-->tabuleiro     a funcao inverte a celula da coordenada do tabuleiro argumento
    if eh_tabuleiro(t) and eh_coordenada_tabuleiro(coor):
        x=coor[0]
        y=coor[1]
        if x!=2:
            t=transform_tuple_lista(t)          #transforma o tabuleiro em lista para se poderem realizar operacoes mais facilmente
            val=cria_celula(t[x][y])            #obtem se a celula da coordenada argumento
            inv=inverte_estado(val)             #inverte o estado da celula da coordenada
            new_val=obter_valor(inv)            #obtem se o valor da celula invertida
            t[x][y]=new_val                     #coloca se a celula invertida na coordenada de volta
            return transform_lista_tuple(t)     #retorna o novo tabuleiro de lista em tuplo
        else:                                   #se a coordenada for do tipo(2,y) decrementa-se o coordenada y em 1 pois a coordenada(2,0) nao existe
            y=y-1
            t=transform_tuple_lista(t)          #transforma o tabuleiro em lista para se poderem realizar operacoes mais facilmente
            val=cria_celula(t[x][y])            #obtem se a celula da coordenada argumento
            inv=inverte_estado(val)             #inverte o estado da celula da coordenada
            new_val=obter_valor(inv)            #obtem se o valor da celula invertida
            t[x][y]=new_val                     #coloca se a celula invertida na coordenada de volta
            return transform_lista_tuple(t)     #retorna o novo tabuleiro de lista em tuplo
    else:
        raise ValueError("tabuleiro_inverte_estado: argumentos invalidos.")
    
def tabuleiros_iguais(t1,t2):#tabuleiro x tabuleiro-->logico   a funca verifica se os argumentos sao tabuleiros iguais
    if eh_tabuleiro(t1) and eh_tabuleiro(t2):    #verifica se os argumentos sao tabuleiros
        if t1==t2:
            return True
        else:
            return False
    else:
        return False
def str_para_tabuleiro(s):#cad.caracteres-->tabuleiro     a funcao devolve o tabuleiro da cadeia de caracteres argumentos 
    if type(s)==str:      #verifica se argumento e string
        return eval(s)
    else:
        raise ValueError("str_para_tabuleiro: argumento invalido.")
    

def porta_x(t,x):#tabuleiro x ("E","D")-->tabuleiro   a funcao devolve um tabuleiro resultante de aplicar a porta_x no qubit da esquerda ou direita                                           
    tnew=()                   
    if not eh_tabuleiro(t) or x not in ["E","D"]:   # verifica se o argumento e tabuleiro e se o segundo argumento e valido 
       raise ValueError("porta_x: argumentos invalidos.")
    if eh_tabuleiro(t):                             
       if x=="E":                                                   
            for e in t[1]:       #ciclo que introduz os elementos do primeiro tuplo do tuplo principal num novo tuplo auxiliar
                if e==1:                            
                    tnew=tnew+(0,)
                if e==0:
                    tnew=tnew+(1,)
                if e==-1:
                    tnew=tnew+(-1,)
                tupaux=(t[0],tnew,t[2])   # introduz os elementos do tuplo auxiliar na ordem requerida
            return tupaux
       if x=="D":                       
           t=transform_tuple_lista(t)
           for i in range(len(t)):
               t[i][-2]=conversoes(t[i][-2])   #o elemento 1 passa a elemento 0 e vice versa enquanto que o elemento -1 mantem_se e coloca se a ordem intencional       
           return transform_lista_tuple(t)

def porta_z(t,x):#tabuleiro x ("E","D")-->tabuleiro    a funcao devolve um tabuleiro resultante de aplicar a porta_z no qubit da esquerda ou direita                  
    tnew=()
    if not eh_tabuleiro(t) or x not in ["E","D"]:    # verifica se o argumento e tabuleiro e se o segundo argumento e valido
       raise ValueError("porta_z: argumentos invalidos.")
    if eh_tabuleiro(t):
        if x=="E":
            for e in t[0]:     #ciclo que introduz os elementos do primeiro tuplo do tuplo principal num novo tuplo auxiliar         
                if e==1:
                    tnew=tnew+(0,)
                if e==0:
                    tnew=tnew+(1,)
                if e==-1:
                    tnew=tnew+(-1,)
                tupaux=(tnew,t[1],t[2])   # introduz os elementos do tuplo auxiliar na ordem requerida
            return tupaux
        if x=="D":
           t=transform_tuple_lista(t)
           for i in range(len(t)):
               t[i][-1]=conversoes(t[i][-1])     #o elemento 1 passa a elemento 0 e vice versa enquanto que o elemento -1 mantem_se e coloca se a ordem intencional
           return transform_lista_tuple(t)

def porta_h(t,x):#tabuleiro x ("E","D")-->tabuleiro   a funcao devolve um tabuleiro resultante de aplicar a porta_h no qubit da esquerda ou direita                                                       
    tnew=()
    if not eh_tabuleiro(t) or x not in ["E","D"]:       # verifica se o argumento e tabuleiro e se o segundo argumento e valido
       raise ValueError("porta_h: argumentos invalidos.")
    if eh_tabuleiro(t):
        if x=="E":
            tnew=(t[1],t[0],t[2])     #introduz os elementos do tabuleiro num tuplo com a ordem requerida
            return tnew
        if x=="D":
            t=transform_tuple_lista(t)  #transforma o tabuleiro em lista para melhor operar sobre ele
            t[0][1], t[1][1], t[2][0], t[0][2], t[1][2], t[2][1] =\
            t[0][2], t[1][2], t[2][1], t[0][1], t[1][1], t[2][0]             #coloca os elementos na ordem requerida
            t=transform_lista_tuple(t)  #transforma o tabuleiro ja transformado novamente em tabuleiro
            return t


def conversoes(t):        #funcao auxiliar que inverte todos os elementos do tabuleiro
    return obter_valor(inverte_estado(cria_celula(t)))

def transform_tuple_lista(t): #funcao auxiliar que transforma tuplos em listas             
    t=list(t)
    for i in range(len(t)):
        t[i]=list(t[i])
    return t
def transform_lista_tuple(t):  #funcao auxiliar que transforma listas em tuplos        
    for i in range(len(t)):
        t[i]=tuple(t[i])
    t=tuple(t)
    return t

def hello_quantum(j):#cad.caracteres-->logico      funcao que permite jogar um jogo completo de Hello Quantum
    j=j.split(":")     #divide o argumento em duas partes pelo carater ":"  formando uma lista de com esses dois elementos
    tab_jogo=tabuleiro_para_str(str_para_tabuleiro(j[0]))  #tabuleiro do jogo pronto a usar dado pelo primeiro elemento da lista formada pelo split
    num_jogadas_possiveis=eval(j[1]) #numero de jogadas possiveis dadas pelo segundo elemento da lista formada pelo split
    num_jogadas=0    #numero de jogadas feitas ate ao momento
    tab_inic=tabuleiro_inicial() #tabuleiro inicial do jogador
    print("Bem-vindo ao Hello Quantum!\nO seu objetivo e chegar ao tabuleiro:")
    print(tab_jogo)
    print("Comecando com o tabuleiro que se segue:")
    print(tabuleiro_para_str(tab_inic))
    while num_jogadas<num_jogadas_possiveis: #ciclo principal de jogo
        L=input("Escolha uma porta para aplicar (X, Z ou H): ")
        direc=input("Escolha um qubit para analisar (E ou D): ")
        num_jogadas+=1 #incrementador para o numero de jogadas feitas pelo jogador
        hello_quantum_aux(tab_inic,direc,L) #chama a funcao auxiliar fornecendo o tabuleiro do jogador e a jogada do jogador
        tab_inic=hello_quantum_aux(tab_inic,direc,L) #atualiza o tabuleiro de jogo com a jogada feita
        print(tabuleiro_para_str(tab_inic))
        if tabuleiros_iguais(tab_inic,str_para_tabuleiro(j[0])): #verifica se o tabuleiro do jogo e igual ao tabuleiro do jogador 
            print("Parabens, conseguiu converter o tabuleiro em {} jogadas!".format(num_jogadas))
            return True
    return False #se o jogador exceder o numero de jogadas possiveis o funcao sai do ciclo e o jogador perde o jogo dando return false
def hello_quantum_aux(tab,direc,L): #funcao auxiliar que usa a porta argumento(L) tabuleiro argumento e na direcao argumento (direc) que pode ser "D" ou "E"
        if L=="X":
            tab_inic=porta_x(tab,direc)
            return(tab_inic)
        if L=="Z":
            tab_inic=porta_z(tab,direc)
            return(tab_inic)

        if L=="H":
            tab_inic=porta_h(tab,direc)
            return(tab_inic)
        

    
    
    
    
    
    
        
                
    
    
