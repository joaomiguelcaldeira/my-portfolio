# Grupo 01:
# 93729 Joao Miguel Caldeira
# 93730 Joao Tomas Cardoso

from search import Problem, Node, astar_search, breadth_first_tree_search, \
	depth_first_tree_search, greedy_search,iterative_deepening_search,recursive_best_first_search, compare_searchers
import sys

class RRState:
	state_id = 0

	def __init__(self, board):
		self.board = board
		self.id = RRState.state_id
		RRState.state_id += 1

	def __lt__(self, other):
		""" Este método é utilizado em caso de empate na gestão da lista
		de abertos nas procuras informadas. """
		return self.id < other.id


class Board:

	def __init__(self, boardNodes, boardRobots, corAlvo, posAlvo, size):
		self.boardNodes = boardNodes
		self.boardRobots = boardRobots
		self.corAlvo = corAlvo
		self.posAlvo = posAlvo
		self.size = size  # size = lado do quadrado

	def robot_position(self, robot: str):
		return self.boardRobots.get(robot)


def criaNodes(size):
	"""Funcao que cria um dicionario de tamanho size**2 com keys numeradas de 1 a size**2
	representando as posicoes da esquerda para a direita e de cima para baixo de um quadrado
	com as posicoes adjacentes nos values"""
	i = 1
	nodes = {}
	while(i <= size*size):
		if not((i-1) % size == 0):
			addValue(nodes, i, i-1)
		if not(i % size == 0):
			addValue(nodes, i, i+1)
		if not(i <= size):
			addValue(nodes, i, i-size)
		if not(i > size**2 - size):
			addValue(nodes, i, i+size)
		i += 1
	return nodes


def addValue(dic, key, value):
	"""Funcao que adiciona uma key e um value a um dicionario ou apenas um value
	a uma key ja existente"""
	if key in dic and value not in dic[key]:
		dic[key].append(value)
	else:
		dic[key] = [value]


def addWalls(dic, pos, edge, size):
	"""Funcao que considera as paredes do tabuleiro do jogo e quebra
	as adjacencias correspondentes entre posicoes com uma parede no meio"""
	if (edge == 'l' and not((pos-1) % size == 0)):
		dic[pos].remove(pos - 1)
		dic[pos - 1].remove(pos)
	if (edge == 'r' and not(pos % size == 0)):
		dic[pos].remove(pos + 1)
		dic[pos + 1].remove(pos)
	if (edge == 'u' and not(pos <= size)):
		dic[pos].remove(pos - size)
		dic[pos - size].remove(pos)
	if (edge == 'd' and not(pos > size**2 - size)):
		dic[pos].remove(pos + size)
		dic[pos + size].remove(pos)


def getPos(line, col, size):
	"""Funcao que obtem a posicao no tabuleiro de um conjunto de coordenadas"""
	return size * (line - 1) + col


def getCord(pos, size):
	"""Funcao que obtem as coordenadas de uma posicao do tabuleiro"""
	line = (pos-1) // size + 1
	col = pos - size * (line - 1)
	return(line, col)


def parse_instance(filename: str) -> Board:
	""" Lê o ficheiro cujo caminho é passado como argumento e retorna
	uma instância da classe Board. """
	f = open(filename, "r")

	size = int(f.readline().split()[0])
	boardNodes = criaNodes(size)
	boardRobots = {}
	while(len(boardRobots) != 4):
		linha = f.readline().split()
		boardRobots[linha[0]] = (int(linha[1]), int(linha[2]))

	linhaAlvo = f.readline().split()
	corAlvo = linhaAlvo[0]
	posAlvo = (int(linhaAlvo[1]), int(linhaAlvo[2]))

	boardWalls = {}
	numParedes = int(f.readline().split()[0])
	i = 1
	while(i <= numParedes):
		linha = f.readline().split()
		addWalls(boardNodes, getPos(
			int(linha[0]), int(linha[1]), size), linha[2],size)
		i += 1
	f.close()
	return Board(boardNodes, boardRobots, corAlvo, posAlvo, size)


def getDirection(currentNode, futureNode, size):
	"""Funcao que retorna a direcao de uma posicao em relacao a outra posicao"""
	if (futureNode == currentNode - 1):
		return 'l'
	if (futureNode == currentNode + 1):
		return 'r'
	if (futureNode == currentNode + size):
		return 'd'
	if (futureNode == currentNode - size):
		return 'u'


class RicochetRobots(Problem):
	def __init__(self, board: Board):
		""" O construtor especifica o estado inicial. """
		self.initial = RRState(board)
		self.heuristicNodes = setUpHeuristic(board)
	def actions(self, state: RRState):
		""" Retorna uma lista de ações que podem ser executadas a
		partir do estado passado como argumento. """
		lst = []
		size = state.board.size
		for e in state.board.boardRobots:
			tup = state.board.boardRobots[e]
			pos = getPos(tup[0], tup[1], size)
			for j in state.board.boardNodes[pos]:
				lst.append((e, getDirection(pos, j, size)))
		return lst

	def result(self, state: RRState, action):
		""" Retorna o estado resultante de executar a 'action' sobre
		'state' passado como argumento. A ação retornada deve ser uma
		das presentes na lista obtida pela execução de
		self.actions(state). """
		actions = self.actions(state)	
		cordRobot = state.board.boardRobots[action[0]]
		posRobot = getPos(cordRobot[0], cordRobot[1],state.board.size) 
		newPos = self.newRobotPosition(action[0],action[1],posRobot,state.board)
		newBoard = Board(state.board.boardNodes.copy(),state.board.boardRobots.copy(),state.board.corAlvo,state.board.posAlvo,state.board.size)
		newBoard.boardRobots[action[0]] = newPos
		newState = RRState(newBoard)
		return newState

	def goal_test(self, state: RRState):
		""" Retorna True se e só se o estado passado como argumento é
		um estado objetivo. Deve verificar se o alvo e o robô da
		mesma cor ocupam a mesma célula no tabuleiro. """
		return state.board.boardRobots[self.initial.board.corAlvo] == self.initial.board.posAlvo

	def h(self, node: Node):
		""" Função heuristica utilizada para a procura A*. """
		cordAlvo = node.state.board.posAlvo
		corAlvo = node.state.board.corAlvo
		cordRobot = node.state.board.boardRobots[corAlvo]
		if(cordRobot[0] == cordAlvo[0]) or (cordAlvo[1] == cordRobot[1]):
			return 1
		return 2

	def newRobotPosition(self, robot, direct, pos, board: Board):
		allPos = getAllRobotPositions(board.boardRobots,board.size)
		if (direct == 'l'):
			while((pos - 1) in board.boardNodes[pos] and not ((pos-1) in allPos)):
				pos -= 1
			return getCord(pos,board.size)
		if (direct == 'r'):
			while((pos + 1) in board.boardNodes[pos] and not ((pos+1) in allPos)):
				pos += 1
			return getCord(pos,board.size)
		if (direct == 'u'):
			while((pos - board.size) in board.boardNodes[pos] and not ((pos-board.size) in allPos)):
				pos -= board.size
			return getCord(pos,board.size)
		if (direct == 'd'):
			while((pos + board.size) in board.boardNodes[pos] and not ((pos+board.size) in allPos)):
				pos += board.size
			return getCord(pos,board.size)
		return getCord(pos,board.size)


def columnOfAdj(boardNodes,pos,size):
	"""Funcao que obtem uma corrente de posicoes adjacentes verticalmente"""
	column = []
	pos1 = pos
	while(pos1 - size > 0 and (pos1 - size) in boardNodes[pos1]):
		column.append(pos1 - size)
		pos1 -= size
	while(pos + size <= size**2 and (pos + size) in boardNodes[pos]):
		column.append(pos + size)
		pos += size
	return column


def lineOfAdj(boardNodes,pos,size):
	"""Funcao que obtem uma corrente de posicoes adjacentes horizontalmente"""
	line = []
	pos1 = pos
	while(pos1 - 1 > 0 and (pos1 - 1) in boardNodes[pos1]):
		line.append(pos1 - 1)
		pos1 -= 1
	while(pos + 1 <= size**2 and (pos + 1) in boardNodes[pos]):
		line.append(pos + 1)
		pos += 1
	return line


def setUpHeuristic(board):
	"""Funcao que cria um dicionario com o valor de heuristica para cada
	posicao do tabuleiro. A funcao de heuristica consiste em obter o numero
	minimo de passos para um robot numa dada posicao chegar a posicao alvo,
	considerando sempre o melhor cenario possivel, obtendo uma heuristica admissivel"""
	allPos = getAllRobotPositions(board.boardRobots,board.size)
	targetPos = getPos(board.posAlvo[0],board.posAlvo[1],board.size)
	costNode = {targetPos: 0}
	cicles = 0
	while(len(costNode) < len(board.boardNodes)):
		col = columnOfAdj(board.boardNodes,targetPos,board.size)
		line = lineOfAdj(board.boardNodes,targetPos,board.size)
		for e in col:
			if not e in costNode:
				costNode[e] = costNode[targetPos] + 1
		for e in line:
			if not e in costNode:
				costNode[e] = costNode[targetPos] + 1
		if (cicles + 1 < len(costNode)):
			cicles += 1
			targetPos = list(costNode.keys())[cicles]
		else:
			for e in board.boardNodes:
				if not (e in costNode):
					costNode[e] = 100
			break
	return costNode


def getAllRobotPositions(boardRobots,size):
	"""Funcao que obtem uma lista de todas as posicoes ocupadas por robots"""
	posLst = []
	for e in boardRobots:
		tup = boardRobots[e]
		posLst.append(getPos(tup[0],tup[1],size))
	return posLst


def getMovements(node: Node):
	"""Funcao imprime todas as acoes feitas para completar o jogo,
	fazendo backtracking ate ao no inicial (que nao tem parent)"""
	lst = []
	while(node.parent):
		lst.append(node.action)
		node = node.parent
	lst.reverse()
	for e in lst:
		print(e[0]+" "+e[1])


if __name__ == "__main__":
	# TODO:
	board = parse_instance(str(sys.argv[1]))
	problem = RicochetRobots(board)
	node = recursive_best_first_search(problem)
	print(node.path_cost)
	getMovements(node)
	pass