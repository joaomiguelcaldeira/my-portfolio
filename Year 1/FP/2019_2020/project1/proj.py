#Joao Miguel Caldeira ist193729

###########################################
#funcao que recebe um argumento e verifica#
#            se e um labirinto            #
###########################################
""" universal --> boolean """
def eh_labirinto(l):
    # verifica se e um tumplo com tamanho superior a 3
    if type(l) != tuple or len(l) < 3:
        return False
    # verifica se o primeiro e ultimo tuplo tem apenas 1
    # ou seja sao paredes
    for j in l[0]:
        if j != 1:
            return False
    for i in l[-1]:
        if i != 1:
            return False
    for e in l:
        # verifica se os elementos do tuplo principal
        # sao tuplos de tamanho superior a 3
        if type(e) != tuple or len(e) < 3:
            return False
        # verifica se os elementos exteriores do tuplo
        # sao paredes ou seja 1
        if e[0] != 1 or e[-1] != 1:
            return False
    # verifica se os tuplos do tuplo teem o mesmo tamanho
    for m in range(len(l) - 1):
        if len(l[m]) != len(l[m + 1]):
            return False
    # verifica se os tuplos do tuplo teem apenas 0 ou 1
    for e in l:
        for k in e:
            if (k != 0 and k != 1) or type(k) != int:
                return False
    else:
        return True

###########################################
#funcao que recebe um argumento e verifica#
#            se e uma posicao             #
###########################################
""" universal --> boolean """      
def eh_posicao(posicao):
        #verifica se o argumento e um tuplo
        if type(posicao)!=tuple:
                return False
        #verifica se o tuplo tem tamanho diferente de 2
        if len(posicao)!=2:
                return False
        #verifica se os elementos do tuplo sao inteiros
        for i in posicao:
                if type(i)!=int or i<0:
                        return False
        return True


###########################################
#funcao que recebe um argumento e verifica#
#      se e um conjunto de posicoes       #
###########################################
""" universal --> boolean"""       
def eh_conj_posicoes(conj):
    # verifica se o argumento e um tuplo
    if type(conj) != tuple:
        return False
    # verifica se e um tuplo com apenas 1 elemento
    # e se e uma posicao unica
    if len(conj)==1 and eh_posicao(conj[0]):
        return True
    # verifica se cada posicao e unica e se sao posicoes
    for j in conj:
        if not (eh_posicao(j)):
            return False
        if conj.count(j) > 1:
            return False
    else:
        return True
############################################
#funcao que recebe um labirinto e retorna  #
#                o seu tamanho             #
############################################
""" labirinto --> tamanho"""               
def tamanho_labirinto(l):
        nx=0
        ny=0
        #verifica se e um labirinto e por cada
        #elemento conta o numero de linhas e colunas
        if eh_labirinto(l):
                for e in range(len(l)):
                        nx=nx+1
                for e in range(len(l[0])):
                        ny=ny+1
                return (nx,ny)
        else:
                raise ValueError('tamanho_labirinto: argumento invalido')


################################################
#funcao que recebe um labirinto e um conjunto  #
#        de posicoes e verifica se as posicoes #
#         sao compativeis com o labirinto      #                   
################################################
""" labirinto,conjunto de posicoes --> boolean """
def eh_mapa_valido(l, conj):
    # verificacao dos argumentos
    if eh_labirinto(l) and eh_conj_posicoes(conj):
        # se o conjunto dado for vazio o mapa e sempre valido
        if conj == ():
            return True
        tam = tamanho_labirinto(l)
        for j in range(len(conj)):
            posX = conj[j][0]
            posY = conj[j][1]
            # verifica se o conjunto de posicoes se encontra fora dos corredores
            if (posX < 1) or (posX >= tam[0]-1) or (posY < 1) or (posY >= tam[1]-1):
                return False
                # verifica se o conjunto de posicoes se encontra numa parede
            elif l[posX][posY] == 1:
                return False           
        return True
    else:
        raise ValueError('eh_mapa_valido: algum dos argumentos e invalido')


################################################
#  funcao que recebe um labirinto  um conjunto #
#        de posicoes e uma posicao e verifica  #
#         se a posicao esta livre              #                   
################################################
""" labirinto,conjunto de posicoes,posicao --> boolean """
def eh_posicao_livre(l, conj, posicao):
    try:
        # verificacao dos argumentos
        if eh_labirinto(l) and eh_conj_posicoes(conj) and eh_posicao(posicao) and eh_mapa_valido(l, conj):
            #verifica se a posicao coincide com as paredes e valida a posicao
            #relativamente ao labirinto dado
            if eh_mapa_valido(l,(posicao,)):
                for j in conj:
                    # verifica se algum elemento do conjunto
                    # coincide com a posicao
                    if j == posicao:
                        return False

                return True
            else:
                return False
        raise ValueError('eh_posicao_livre: algum dos argumentos e invalido')
    except:
        raise ValueError('eh_posicao_livre: algum dos argumentos e invalido')

################################################
#  funcao que recebe uma posicao e retorna     #
#        as suas posicoes adjacentes           #
################################################
""" posicao --> posicoes adjacentes """
def posicoes_adjacentes(posicao):
        #verificacao do argumento
        if eh_posicao(posicao):
                startpoint=(posicao[0]-1,posicao[1]-1)
                contador=0
                new1=()
                new2=()
                res=()
                adjacentes=()
                #ciclo que verifica e coloca as posicoes
                #adjacentes no tuplo a retornar
                while contador<2:
                        new1=(startpoint[0]+1,startpoint[1])
                        if eh_posicao(new1):
                                res+=(new1,)
                        new2=(startpoint[0],startpoint[1]+1)
                        if eh_posicao(new2):
                                res+=(new2,)
                        startpoint=posicao
                        contador=contador+1
                return res
        else:
                raise ValueError("posicoes_adjacentes: argumento invalido")

###############################################
#funcao auxiliar que recebe um tuplo e devolve#
#             o tuplo listificado             #
###############################################
""" tuplo --> lista"""
def tuple_go_lista(t):                  
    t=list(t)
    for i in range(len(t)):
        t[i]=list(t[i])
    return t


################################################
#funcao que recebe um labirinto e um conjunto  #
#        de posicoes e retorna a representacao #
#             do mapa em forma de string      #                   
################################################
""" labirinto,conjunto de posicoes --> cadeia de caracteres """
def mapa_str(l,conj):
        mapa=[]
        contador=1 
        index1=0
        index2=0
        p=[]
        #verificacao dos argumentos      
        if eh_labirinto(l) and eh_conj_posicoes(conj) and eh_mapa_valido(l,conj):
                tam= tamanho_labirinto(l)
                p=tuple_go_lista(l)
                #marcacao das unidades no mapa
                for e in conj:
                        p[e[0]][e[1]]="O"
                #transposicao dos tuplos do labirinto
                #de forma a realizar a representacao
                transposta =[[p[j][i] for j in range(len(p))] for i in range(len(p[0]))]
                #transformacao do labirinto na representacao
                for e in transposta:
                        for j in e:
                                if j==1:
                                        j='#'
                                        mapa.append(j)
                                        
                                elif j==0:
                                        j='.'
                                        mapa.append(j)
                                else:
                                        mapa.append(j)
                        contador+=1
                        if contador>tam[1]:
                                break
                        mapa.append("\n")
                string=''.join(mapa)                
                return string
        else:
                raise ValueError("mapa_str: algum dos argumentos e invalido")

#####################################
#funcao auxiliar que retorna True se#
#             x e elemento de y     #
#####################################
""" x,y --> boolean """
def iselementof(x,y):
        for e in x:
                if e==y:
                        return True
        if x==y:
                return True
        else:
                return False


################################################
#  funcao que recebe um labirinto  um conjunto #
#        de posicoes e uma posicao e retorna   #
#    o conjunto de posicoes adjacentes que     #
#                    sera os objetivos         #                   
################################################
""" labirinto,conjunto de posices, posicao --> objetivos """
def obter_objetivos(l, conj, posicao):
    if eh_mapa_valido(l, conj) and eh_posicao(posicao) and eh_conj_posicoes(conj) and eh_labirinto(l) and posicao in conj:
        list_conj = tuple_go_lista(conj)
        list_posicao = list(posicao)
        list_conj.remove(list_posicao)
        mod_adj = [tuple(e) for e in list_conj]
        conj_obj = []
        for e in range(len(mod_adj)):
            for j in posicoes_adjacentes((mod_adj[i])):
                if eh_posicao_livre(l,conj,j):
                    conj_obj+= [list(j)]
        tuple_conj_obj = tuple(tuple(e) for e in conj_obj)
        obj_final = tuple(set(tuple_conj_obj))
        return(obj_final)
    else:
        raise ValueError("obter_objetivos: algum dos argumentos e invalido")
def obter_objetivos(l, conj, posicao):
    # verificacao dos argumentos
    if eh_mapa_valido(l, conj) and eh_posicao(posicao) and eh_conj_posicoes(conj) and eh_labirinto(l) and posicao in conj:
        res = ()
        # verifica se o conjunto e apenas uma posicao
        # e atribui os elementos diferentes da posicao dada
        if (conj == posicao):
            return res
        for e in conj:
            if e != posicao:
                res += (e,)
        listadj = []
        parselist = []
        # ciclo que obtem as posicoes adjacentes
        for i in res:
            if type(i) == tuple:
                listadj += posicoes_adjacentes(i)

            if type(i) == int:
                listadj = posicoes_adjacentes(res)
        # ciclo que trata as posicoes adjacentes
        for j in listadj:
            if eh_posicao_livre(l,(), j) and j != posicao:
                parselist += [j]
        # filtra os elementos repetidos
        final = tuple(dict.fromkeys(parselist))
        return final
    else:
        raise ValueError("obter_objetivos: algum dos argumentos e invalido")



#####################################
#funcao auxiliar recursiva que faz  #
#          backtrack da bfs         #
#####################################
def recurse(caminho,iter,res):
    ladj = posicoes_adjacentes(iter)
    for e in range(len(caminho)):
        if caminho[e] in ladj:
            res+=(caminho[e],)
            return recurse(caminho,caminho[e],res)
        else:
            if caminho[0] in res:
                return res


################################################
#  funcao que recebe um labirinto  um conjunto #
#        de posicoes e uma posicao e obtem o   #
#   caminho de tamanho minimo para o objetivo  #                   
################################################
""" labirinto,conjunto de posicoes,posicao --> caminho"""
def obter_caminho(l, conj, posicao):
    # verificacao dos argumentos
    if eh_mapa_valido(l, conj) and eh_posicao(posicao) and iselementof(conj,posicao):
        explora =(posicao,)
        objetivos = obter_objetivos(l, conj, posicao)
        visitadas = ()
        caminho = ()
        i = 0
        #se o conjunto for igual a posicao entao
        #nao ha caminho a percorrer
        if conj == (posicao,):
            return caminho
        #queue do explora
        while (explora != ()):
            #atualizacao da posicao a tratar pela bfs
            if (i == 0):
                posAtual = explora[0]
            else:
                posAtual = explora[i]
            if not (posAtual in visitadas):
                caminho += (posAtual,)
                visitadas += (posAtual,)
                vizinhos = posicoes_adjacentes(posAtual)
                i += 1
                #caminho final da bfs que corresponde a encontrar um objetivo
                if (posAtual in objetivos):
                    resultado=()
                    final=()
                    resultado = recurse(caminho,caminho[-1],resultado)
                    final=resultado[::-1]
                    final+=(caminho[-1],)
                    return final
                else:
                    for e in vizinhos:
                        if eh_posicao_livre(l, conj, e):
                            explora += (e,)
                    explora += caminho
            #se a posicao atual ja foi visitada entao incrementa o indice da lista a explorar
            i+=1

    else:
        raise ValueError("obter_caminho: algum dos argumentos e invalido")


################################################
#  funcao que recebe um labirinto  um conjunto #
#        de posicoes e uma posicao e move uma  #
#   das posicoes em direcao ao objetivo        #                   
################################################
"""labirinto,conjunto de posicoes,posicao --> conjunto de posicoes"""
def mover_unidade(l,conj,posicao):
        #verificacao dos argumentos
        if eh_labirinto(l) and eh_conj_posicoes(conj) and eh_posicao(posicao) and eh_mapa_valido(l,conj) and iselementof(conj,posicao):
                unidades=()
                caminho=()
                caminho=obter_caminho(l,conj,posicao)
                #ciclo que atualiza a unidade a mover para a nova posicao
                for e in conj:
                    if e == posicao:
                        unidades+=(caminho[1],)
                    else:
                        unidades+=(e,)
                return unidades
        else:
                raise ValueError("mover_unidade: algum dos argumentos e invalido")
