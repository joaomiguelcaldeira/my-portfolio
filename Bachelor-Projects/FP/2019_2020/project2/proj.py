#Joao Miguel Caldeira ist193729

def cria_posicao(x,y):
    '''
       A funcao cria_posicao recebe valores correspondentes
       a uma posicao e devolve a posicao correspondente.

       cria_posicao: N x N -> posicao
       '''
    if type(x) == int and type(y) == int and x >= 0 and y >= 0:
        return [x,y]
    else:
        raise ValueError('cria_posicao: argumentos invalidos')

def cria_copia_posicao(p):
    '''
       A funcao cria_copia_posicao cria uma copia
       nova da posicao argumento

       cria_copia_posicao: posicao -> posicao
           '''
    return cria_posicao(p[0],p[1])

def obter_pos_x(p):
    '''
       A funcao obter_pos_x recebe uma posicao
       e devolve a componente x da posicao

       obter_pos_x: posicao -> N
       '''
    return p[0]

def obter_pos_y(p):
    '''
       A funcao obter_pos_y recebe uma posicao
       e devolve a componente y da posicao

       obter_pos_y: posicao -> N
       '''
    return p[1]

def eh_posicao(arg):
    '''
       A funcao eh_posicao recebe um argumento
       e verifica se e posicao

       eh_posicao: universal -> boolean
       '''
    return type(arg) == list and len(arg) == 2 and type(obter_pos_x(arg)) == int and type(obter_pos_y(arg)) == int and obter_pos_x(arg) >= 0 and obter_pos_y(arg) >= 0

def posicoes_iguais(p1,p2):
    '''
       A funcao  posicoes_iguais recebe
       2 posicoes e verifica se sao iguais

       posicoes_iguais: posicao x posicao -> boolean
       '''
    return eh_posicao(p1) and eh_posicao(p2) and obter_pos_x(p1) == obter_pos_x(p2) and obter_pos_y(p1) == obter_pos_y(p2)

def posicao_para_str(p):
    '''
       A funcao  posicao_para_str recebe uma
       posicao e retorna a cadeia de caracteres que a representa

       posicoes_para_str: posicao -> str
       '''
    return str(tuple(p))

def obter_posicoes_adjacentes(p):
    '''
       A funcao  obter_posicoes_adjacentes recebe uma
       posicao e retorna as posicoes adjacentes ordenadas por ordem de leitura

       obter_posicoes_adjacentes: posicao -> tuplo de posicoes
       '''
    x = obter_pos_x(p)
    y = obter_pos_y(p)
    candidatos = ([x, y - 1], [x - 1, y], [x + 1, y], [x, y + 1])
    res=()
    for e in candidatos:
        if eh_posicao(e):
            res += (tuple(e),)
    return res

def cria_unidade(p,hp,f,team):
    '''
       A funcao cria unidade recebe uma posicao, 2 naturais referentes a
       vida e forca e uma string e devolve a unidade correspondente

       cria_unidade: posicao x N x N x str -> unidade
       '''
    if eh_posicao(p) and type(hp) == int and type(f) == int and type(team) == str and len(team) > 0 and hp > 0 and f > 0:
        return [p,hp,f,team]
    raise ValueError('cria_unidade: argumentos invalidos')

def cria_copia_unidade(u):
    '''
       A funcao cria_copia_unidade cria uma copia
       nova da unidade argumento

       cria_copia_uniadade: unidade -> unidade
           '''
    return cria_unidade(cria_copia_posicao(u[0]),u[1],u[2],u[3])

def obter_posicao(u):
    '''
       A funcao obter_posicao recebe uma unidade
       e devolve a posicao da unidade

       obter_posicao: unidade -> posicao
       '''
    return u[0]

def obter_vida(u):
    '''
       A funcao obter_vida recebe uma unidade
       e devolve a vida da unidade

       obter_vida: unidade -> N
       '''
    return u[1]

def obter_forca(u):
    '''
       A funcao obter_forca recebe uma unidade
       e devolve a forca da unidade

       obter_forca: unidade -> N
       '''
    return u[2]

def obter_exercito(u):
    '''
       A funcao obter_exercito recebe uma unidade
       e devolve o exercito da unidade

       obter_exercito: unidade -> str
       '''
    return u[3]

def muda_posicao(u,p):
    '''
       A funcao muda_posicao recebe uma unidade e uma posicao e
       modifica a posicao da unidade para a posicao argumento

       muda_posicao: unidade x posicao -> unidade
       '''
    u[0] = p
    return u

def remove_vida(u,hp):
    '''
       A funcao remove_vida recebe uma unidade e um inteiro e
       modifica a vida da unidade, subtraindo a vida argumento

       remove_vida: unidade x N -> unidade
           '''
    u[1] -= hp
    return u

def eh_unidade(arg):
    '''
       A funcao eh_unidade recebe um argumento
       e verifica se e unidade

       eh_unidade: universal -> boolean
       '''
    return type(arg) == list and len(arg) == 4 and eh_posicao(obter_posicao(arg)) and type(obter_vida(arg)) == int and type(obter_forca(arg)) == int and type(obter_exercito(arg)) == str and len(obter_exercito(arg)) > 0 and obter_vida(arg) > 0 and obter_forca(arg) > 0

def unidades_iguais(u1,u2):
    '''
       A funcao unidades_iguais recebe
       2 unidades e verifica se sao iguais

       unidades_iguais: unidade x unidade -> boolean
       '''
    return eh_unidade(u1) and eh_unidade(u2) and posicoes_iguais(obter_posicao(u1),obter_posicao(u2)) and obter_forca(u1) == obter_forca(u2) and obter_vida(u1) == obter_vida(u2) and obter_exercito(u1) == obter_exercito(u2)

def unidade_para_char(u):
    '''
       A funcao  uidade_para_char recebe uma
       unidade e retorna a uma cadeia de caracteres de um elmento de define o exercito

       unidade_para_char: unidade -> str
       '''
    return obter_exercito(u)[0].upper()

def unidade_para_str(u):
    '''
       A funcao  unidade_para_str recebe uma
       unidade e retorna a cadeia de caracteres que a representa

       unidade_para_str: unidade -> str
       '''
    return str(unidade_para_char(u))+str(list((obter_vida(u),obter_forca(u))))+"@"+str(tuple(obter_posicao(u)))

def unidade_ataca(u1,u2):
    '''
       A funcao  unidade_ataca recebe 2 unidades e modifica destrutivamente
       a unidade2 retirando pontos da sua vida equivalentes a forca da unidade1

       unidade_ataca: unidade x unidade -> boolean
       '''
    return obter_vida(remove_vida(u2,obter_forca(u1))) <= 0

def ordenar_unidades(t):
    '''
      A funcao  ordenar_unidades recebe um tuplo de unidades e retorna a
      ordenacao segundo a ordem de leitura do tabuleiro

      ordenar_unidades: tuplo de unidades -> tuplo de unidades
      '''
    lis = []
    res= ()
    for e in t:
        lis += (obter_posicao(e),)
    sorter = tuple(sorted(lis, key = lambda cord: (cord[1], cord[0])))
    for j in sorter:
        for k in t:
            if obter_posicao(k) == j:
                res += (k,)
    return res

def cria_mapa(d, w, e1, e2):
    '''
       A funcao cria mapa recebe um tuplo de 2 elementos inteiros, um tuplo de 0 ou mais posicoes,
       e 2 tuplos de 1 ou mais unidades correspondentes aos exercitos do mapa e devolve o mapa correspondente

       cria_mapa: tuplo x tuplo x tuplo x tuplo -> mapa
       '''
    marca = 0
    rep = ()
    res =[]
    if type(d) == tuple and type(d[0]) == int and type(d[1]) and len(d) == 2 and d[0] >= 3 and d[1] >= 3 and type (e1) == tuple and len(e1) >= 1 and type (e2) == tuple and len(e2) >= 1:
        res = [idc for idc, x in enumerate(w) if x in w[:idc]]
        if type(w) == tuple and len(w) >= 0  and res == []:
            marca += 1
            for e in w:
                if not(eh_posicao(e)) and (e[0] >= d[0] - 1 or e[0] == 0) and (e[1] >= d[1]-1 or e[1] == 0):
                    raise ValueError("cria_mapa: argumentos invalidos")
        if type(w) == tuple and len(w) == 0:
            marca +=1
        for i in e1:
            if not eh_unidade(i):
                raise ValueError("cria_mapa: argumentos invalidos")
        for j in e2:
            if not eh_unidade(j):
                raise ValueError("cria_mapa: argumentos invalidos")
        if marca == 0:
            raise ValueError("cria_mapa: argumentos invalidos")
        else:
            return [d, w, e1, e2]
    raise ValueError("cria_mapa: argumentos invalidos")

def cria_copia_mapa(m):
    '''
       A funcao cria_copia_mapa cria uma copia
       nova do mapa argumento

       cria_copia_mapa: mapa -> mapa
           '''
    copia_w = ()
    copia_e1 = ()
    copia_e2 = ()
    for e in m[1]:
        copia_w += (cria_copia_posicao(e),)
    for e in m[2]:
        copia_e1 += (cria_copia_unidade(e),)
    for e in m[3]:
        copia_e2 += (cria_copia_unidade(e),)
    return cria_mapa(m[0],copia_w,copia_e1,copia_e2)

def obter_tamanho(m):
    '''
       A funcao obter_tamanho_reecebe um mapa
       e retorna o tuplo correspondente ao tamanho do mesmo

       obter_tamanho: mapa -> tuplo
           '''
    return m[0]

def obter_nome_exercitos(m):
    '''
       A funcao obter_nome_exercitos_recebe um mapa
       e retorna o tuplo ordenado correspondente aos nomes dos exercitos do mapa

       obter_nome_exercitos: mapa -> tuplo
    '''
    return tuple(sorted((obter_exercito(m[2][0]),obter_exercito(m[3][0]))))

def obter_unidades_exercito(m,e):
    '''
       A funcao obter_unidades_exercito_recebe um mapa e um nome de exercito
       e retorna o tuplo ordenado correspondente as unidades do mapa desse exercito

       obter_unidades_exercito: mapa x str -> tuplo
    '''
    if e == obter_exercito(m[2][0]):
        return ordenar_unidades(m[2])
    if e == obter_exercito(m[3][0]):
        return ordenar_unidades(m[3])
    else:
        return ()

def obter_todas_unidades(m):
    '''
       A funcao obter_obter_todas_unidades_recebe um mapa e retorna
        o tuplo ordenado correspondente as unidades do mapa.

       obter_todas_unidades: mapa -> tuplo
    '''
    return ordenar_unidades(m[3]+m[2])

def obter_unidade(m,p):
    '''
       A funcao obter_obter_unidade_recebe um mapa e uma posicao e retorna
        a unidade do mapa presente nessa posicao

       obter_unidade: mapa x posicao -> unidade
    '''
    for e in obter_todas_unidades(m):
        if obter_posicao(e) == p:
            return e

def eliminar_unidade(m,u):
    '''
       A funcao eliminar unidade recebe um mapa e uma unidade e
       devolve o mapa com a unidade eliminada

       eliminar_unidade: mapa x unidade -> mapa
    '''
    if u in m[2]:
        new_exercito = list(m[2])
        new_exercito.remove(u)
        m[2] = tuple(new_exercito)
    if u in m[3]:
        new_exercito =list(m[3])
        new_exercito.remove(u)
        m[3] = tuple(new_exercito)
    return m

def mover_unidade(m,u,pos):
    '''
       A funcao mover_unidade recebe um mapa, uma unidade e uma posicao
       e retorna o mapa com a unidade na nova posicao

       mover_unidade: mapa x unidade x posicao -> mapa
    '''
    copia = cria_copia_unidade(u)
    atualiza = muda_posicao(u,pos)
    if u in m[2]:
        m[2] += (atualiza,)
    if u in m[3]:
        m[3] += (atualiza,)
    return eliminar_unidade(m,copia)

def eh_posicao_unidade(m,pos):
    '''
       A funcao eh_posicao_unidade recebe um mapa e uma posicao
       e verifica se a posicao do mapa esta ocupada

       eh_posicao_unidade: mapa x posicao -> boolean
       '''
    for e in obter_todas_unidades(m):
        if obter_posicao(e) == pos:
            return True
    return False

def eh_posicao_corredor(m,pos):
    '''
       A funcao eh_posicao_corredor recebe um mapa e uma posicao
       e verifica se a posicao do mapa e um corredor

       eh_posicao_corredor: mapa x posicao -> boolean
       '''
    xmax = obter_pos_x(obter_tamanho(m))
    ymax = obter_pos_y(obter_tamanho(m))
    if xmax > obter_pos_x(pos) > 0 and ymax > obter_pos_y(pos) > 0:
        return not eh_posicao_parede(m,pos)

def eh_posicao_parede(m,pos):
    '''
       A funcao eh_posicao_parede recebe um mapa e uma posicao
       e verifica se a posicao do mapa e uma parede

       eh_posicao_parede: mapa x posicao -> boolean
       '''
    xmax = obter_pos_x(obter_tamanho(m))
    ymax = obter_pos_y(obter_tamanho(m))
    if xmax > obter_pos_x(pos) >= 0 and ymax > obter_pos_y(pos) >= 0:
        return obter_pos_x(pos) == 0 or obter_pos_y(pos) == 0 or obter_pos_x(pos) == xmax - 1 or obter_pos_y(pos) == ymax - 1 or pos in m[1]
    return False

def mapas_iguais(m1,m2):
    '''
       A funcao mapas_iguais recebe
       2 mapas e verifica se sao iguais

       mapas_iguais: mapa x mapa -> boolean
       '''
    t1 = tuple(sorted(m1[1], key=lambda cord: (cord[1], cord[0])))
    t2 = tuple(sorted(m2[1], key = lambda cord: (cord[1], cord[0])))
    return obter_todas_unidades(m1) == obter_todas_unidades(m2) and obter_tamanho(m1) == obter_tamanho(m2) and t1 == t2

def mapa_para_str(m):
    '''
       A funcao  mapa_para_str recebe um mapa
        e retorna a cadeia de caracteres que o representa

       mapa_para_str: mapa -> str
       '''
    i = 0
    j = 0
    mapa = ""
    xmax = obter_pos_x(obter_tamanho(m))
    ymax = obter_pos_y(obter_tamanho(m))
    while i < ymax:
        while j < xmax:
            if eh_posicao_parede(m,cria_posicao(j,i)) and j != xmax:
                mapa += "#"
            elif eh_posicao_unidade(m,cria_posicao(j,i)):
                mapa += unidade_para_char(obter_unidade(m,cria_posicao(j,i)))
            else:
                mapa +=(".")
            j += 1
        #previne a adicao de um "\n" extra
        if i != ymax -1:
            mapa += "\n"
        i += 1
        j = 0
    return mapa

def obter_inimigos_adjacentes(m,u):
    '''
       A funcao  obter_inimigos_adjacentes recebe um mapa e uma unidade
        e retorna um tuplo com as unidades inimigas adjacentes de acordo com a ordem de leitura

       obter_inimigos_adjacentes: mapa x unidade -> tuplo de unidades
       '''
    adja = obter_posicoes_adjacentes(obter_posicao(u))
    aliado = obter_exercito(u)
    all = obter_todas_unidades(m)
    res = ()
    for e in all:
        if obter_exercito(e) != aliado and tuple(obter_posicao(e)) in adja:
            res += (e,)
    return ordenar_unidades(res)

def obter_movimento(mapa, unit):
    '''
    A funcao obter_movimento devolve a posicao seguinte da unidade argumento
    de acordo com as regras de movimento das unidades no labirinto.

    obter_movimento: mapa x unidade -> posicao
    '''

    ######################
    # Funcoes auxiliares #
    ######################
    def pos_to_tuple(pos):
        return obter_pos_x(pos), obter_pos_y(pos)

    def tuple_to_pos(tup):
        return cria_posicao(tup[0], tup[1])

    def tira_repetidos(tup_posicoes):
        conj_tuplos = set(tuple(map(pos_to_tuple, tup_posicoes)))
        return tuple(map(tuple_to_pos, conj_tuplos))

    def obter_objetivos(source):
        enemy_side = tuple(filter(lambda u: u != obter_exercito(source), obter_nome_exercitos(mapa)))[0]
        target_units = obter_unidades_exercito(mapa, enemy_side)
        tup_com_repetidos = \
            tuple(adj
                  for other_unit in target_units
                  for adj in obter_posicoes_adjacentes(obter_posicao(other_unit))
                  if eh_posicao_corredor(mapa, adj) and not eh_posicao_unidade(mapa, adj))
        return tira_repetidos(tup_com_repetidos)

    def backtrack(target):
        result = ()
        while target is not None:
            result = (target,) + result
            target, _ = visited[target]
        return result

    ####################
    # Funcao principal #
    ####################
    # Nao mexer se ja esta' adjacente a inimigo
    if obter_inimigos_adjacentes(mapa, unit):
        return tuple(obter_posicao(unit))

    visited = {}
    # posicao a explorar, posicao anterior e distancia
    to_explore = [(pos_to_tuple(obter_posicao(unit)), None, 0)]
    # registro do numero de passos minimo ate primeira posicao objetivo
    min_dist = None
    # estrutura que guarda todas as posicoes objetivo a igual minima distancia
    min_dist_targets = []

    targets = tuple(pos_to_tuple(obj) for obj in obter_objetivos(unit))

    while to_explore:  # enquanto nao esteja vazio
        pos, previous, dist = to_explore.pop(0)

        if pos not in visited:  # posicao foi ja explorada?
            visited[pos] = (previous, dist)  # registro no conjunto de exploracao
            if pos in targets:  # se a posicao atual eh uma dos objetivos
                # se eh primeiro objetivo  ou se esta a  distancia minima
                if min_dist is None or dist == min_dist:
                    # acrescentor 'a lista de posicoes minimas
                    min_dist = dist
                    min_dist_targets.append(pos)
            else:  # nao 'e objetivo, acrescento adjacentes
                for adj in obter_posicoes_adjacentes(tuple_to_pos(pos)):
                    if eh_posicao_corredor(mapa, adj) and not eh_posicao_unidade(mapa, adj):
                        to_explore.append((pos_to_tuple(adj), pos, dist + 1))

        # Parar se estou a visitar posicoes mais distantes que o minimo,
        # ou se ja encontrei todos os objetivos
        if (min_dist is not None and dist > min_dist) or len(min_dist_targets) == len(targets):
            break

    # se encontrei pelo menos uma posicao objetivo,
    # escolhe a de ordem de leitura menor e devolve o primeiro movimento
    if len(min_dist_targets) > 0:
        # primeiro dos objetivos em ordem de leitura
        tar = sorted(min_dist_targets, key=lambda x: (x[1], x[0]))[0]
        path = backtrack(tar)
        return tuple(tuple_to_pos(path[1]))

    # Caso nenhuma posicao seja alcancavel
    return tuple(obter_posicao(unit))

def calcula_pontos(m,string):
    '''
        A funcao calcula_pontos recebe um mapa e uma cadeia de caracteres
        e devolve a soma dos pontos de vida do exercito representado pela cadeia de caracteres argumento

        calcula_pontos: mapa x str -> int
        '''
    soma = 0
    if obter_exercito(m[2][0]) == string:
        for e in m[2]:
            soma += obter_vida(e)
    if obter_exercito(m[3][0]) == string:
        for e in m[3]:
            soma += obter_vida(e)
    return soma

def simula_turno(mapa):
    '''
        A funcao simula_turno recebe um mapa e simula um turno
        de batalha completo devolvendo o mapa

        calcula_pontos: mapa -> mapa
        '''
    return mapa

def simula_batalha(fileName,mode):
    '''
        A funcao simula_batalha recebe um ficheiro e um modo e simula a
        a batalha completa devolvendo um resultado

        calcula_pontos: str x boolean -> str
        '''
    with open(fileName, "r") as file:
        tamanho = eval(file.readline())
        stats1 =  eval(file.readline())
        stats2 = eval(file.readline())
        walls = eval(file.readline())
        #pos1 = eval(file.readline())
        #pos2 = eval(file.readline())

    exercito1 = ()
    for e in stats1:
        exercito1 += (cria_unidade(cria_posicao(e[0],e[1])),stats1[1],stats1[2],stats1[0],)
    exercito2 = ()
    for e in stats2:
        exercito2 += (cria_unidade(cria_posicao(e[0], e[1])), stats2[1], stats2[2], stats2[0],)
    paredes = ()
    for e in walls:
        paredes += (cria_posicao(e[0],e[1]),)

    mapa = cria_mapa(tamanho,paredes,exercito1,exercito2)
    exercitos = obter_nome_exercitos(mapa)
    print((mapa_para_str(mapa)))
    score1 = calcula_pontos(mapa,exercitos[0])
    score2 = calcula_pontos(mapa,exercitos[1])
    if ( score1 != 0 and score2 != 0 ) or score1 == score2:
        return ("Empate")
    if score1 > score2:
        return (exercitos[0])
    if score2 > score1:
        return (exercitos[1])