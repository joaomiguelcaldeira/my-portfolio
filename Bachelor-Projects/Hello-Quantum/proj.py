# Joao Miguel Pipa Ferreira Caldeira 93729

def eh_tabuleiro(t):        #esta funcao ira filtrar "candidatos" a tabuleiro de jogo
    if type(t)==tuple:      #verifica_se se o elemento dado e um tuplo               
        if len(t)==3:       #verifica_se se o tuplo dado tem 3 elementos e caso alguma destes requisitos nao seja cumprido, a funcao da False                   
            #nomeio cada subtuplo do tuplo principal com v1,v2,v3
            v1=t[0]                                          
            v2=t[1]
            v3=t[2]
            if type(v1)!=tuple or type(v2)!=tuple or type(v3)!=tuple:
                return False
            if len(v1)!=3 or len(v2)!=3 or len(v3)!=2:      # verifica_se o comprimento dos subtuplos e se nao estiver de acordo com os requisitos da False  
                return False
            
            # verifica_se os elementos dos subtuplos que podem apenas ser (-1),(1) e (0) de outra forma ira retornar False
            for e in v1:
                if not(e==-1 or e==0 or e==1):              
                    return False
            for e in v2:
                if not(e==-1 or e==0 or e==1):
                    return False
            for e in v3:
                if not(e==-1 or e==0 or e==1):
                    return False
            else:
                return True   # se todos os requisitos forem cumpridos a funcao retorna True
        return False
    return False

def tabuleiro_str(t):        #esta funcao ira arranjar o tabuleiro de jogo conforme os dados do tabuleiro dado(t)
    lista=()
    if not eh_tabuleiro(t):  # verifica_se se o tabuleiro em questao e valido
        raise ValueError("tabuleiro_str: argumento invalido")
    for e in t:
        for f in e:
            if f==-1:
                f='x'
                lista=lista+(f,)
            else:
                lista=lista+(f,)
    return '+-------+\n|...'+str(lista[2])+'...|\n|..'+str(lista[1])+'.'+str(lista[5])+'..|\n|.'+str(lista[0])+'.'+str(lista[4])+'.'+str(lista[7])+'.|\n|..'+str(lista[3])+'.'+str(lista[6])+'..|\n+-------+'
        
def tabuleiros_iguais(x,y):    #esta funcao ira verificar se quando dados dois tabuleiros, estes sao iguais, sendo os argumentos x e y
    if not (eh_tabuleiro(x)and eh_tabuleiro(y)):             #verifica_se se os tabuleiros em questao sao tabuleiros validos
        raise ValueError("tabuleiros_iguais: um dos argumentos nao e tabuleiro")
    if x==y:                # se o tabuleiro x for igual ao tabuleiro y a funcao retorna True
        return True
    else:                   #se os tabuleiros forem diferentes a funcao retorna False
        return False

def porta_x(t,x):           # esta funcao recebe um tabuleiro e atraves do segundo elemento (D ou E) altera o tabuleiro tendo como argumentos x e y e
                            #obtem se um tabuleiro novo ou seja retorna um novo tabuleiro resultante de uma atuacao no qubit da esquerda ou direita 
    tn=()                   #cria_se um tuplo auxiliar vazio
    if not eh_tabuleiro(t) or x not in ["E","D"]:   # verifica_se se o tabuleiro em questao e valido 
       raise ValueError("porta_x: um dos argumentos e invalido")
    if eh_tabuleiro(t):                             # se o tabuleiro e valido entao:
       if x=="E":                                   # se o segundo elemento for "E" a funcao ira alterar o segundo subtuplo do tabuleiro t[1]
            for e in t[1]:
                if e==1:                            #o elemento 1 passa a elemento 0 e vice versa enquanto que o elemento -1 mantem_se
                    tn=tn+(0,)
                if e==0:
                    tn=tn+(1,)
                if e==-1:
                    tn=tn+(-1,)
                taux=(t[0],tn,t[2])
            return taux
       if x=="D":                       #se o segundo elemento for "D" a funcao ira alterar os subtuplos todos 
           t=tuple_go_lista(t)
           for i in range(len(t)):      #o elemento 1 passa a elemento 0 e vice versa enquanto que o elemento -1 mantem_se
               t[i][-2]=trocas(t[i][-2])          
           return lista_go_tuple(t)    

def lista_go_tuple(t):                  #funcao auxiliar que transforma as listas em tuplos, ou seja recebe uma lista e retorna um tuplo                 
    for i in range(len(t)):
        t[i]=tuple(t[i])
    t=tuple(t)
    return t    

def tuple_go_lista(t):                  #funcao auxiliar que transforma os tuplos em listas, ou seja recebe um tuplo e retorna uma lista 
    t=list(t)
    for i in range(len(t)):
        t[i]=list(t[i])
    return t    

def trocas(i):                          #funcao auxiliar que transforma o elemento 1 em 0 e vice versa
    if i==-1:
        return -1
    elif i==0:
        return 1
    elif i==1:
        return 0

def porta_z(t,x):                       #funcao que transforma o tabuleiro conforme o segundo carater ("E" ou "D") e
                                        #retorna um novo tabuleiro resultante de uma atuacao no qubit da esquerda ou direita
    tn=()
    if not eh_tabuleiro(t) or x not in ["E","D"]:
       raise ValueError("porta_z: um dos argumentos e invalido")
    if eh_tabuleiro(t):
        if x=="E":
            for e in t[0]:            #o elemento 1 passa a elemento 0 e vice versa enquanto que o elemento -1 mantem_se
                if e==1:
                    tn=tn+(0,)
                if e==0:
                    tn=tn+(1,)
                if e==-1:
                    tn=tn+(-1,)
                taux=(tn,t[1],t[2])
            return taux
        if x=="D":
           t=tuple_go_lista(t)
           for i in range(len(t)):
               t[i][-1]=trocas(t[i][-1])
           return lista_go_tuple(t)

def porta_h(t,x):                      #funcao que recebe um tabuleiro (t) e devolve um novo tabuleiro
                                        #conforme a atuacao do qubit da esquerda ou direita que troca os elementos do tabuleiro
    tn=()
    if not eh_tabuleiro(t) or x not in ["E","D"]:       #verifica se o tabuleiro e valido e se o segundo carater e "E" ou "D"
       raise ValueError("porta_h: um dos argumentos e invalido")
    if eh_tabuleiro(t):
        if x=="E":
            tn=(t[1],t[0],t[2])
            return tn
        if x=="D":
            t=tuple_go_lista(t)
            t[0][1], t[1][1], t[2][0], t[0][2], t[1][2], t[2][1] =\
            t[0][2], t[1][2], t[2][1], t[0][1], t[1][1], t[2][0]
            t=lista_go_tuple(t)
            return t
            


    
    
    
    
                   
                
                
        
    
        
            
                  
    
   
                   
        
        
    
    
    
    
        
    
    
   
        
    
 
        
    
