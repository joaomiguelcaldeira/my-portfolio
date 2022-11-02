# test.py: Podem usar este script para testar a vossa implementação. Para tal, devem correr o
# script e verificar que o output que obtêm de cada teste é igual ao apresentado no enunciado do
# projeto. Além dos testes presentes, podem acrescentar outros.

from ricochet_robots import *
from search import astar_search, breadth_first_tree_search, \
    depth_first_tree_search, greedy_search

def test1():
    # Ler tabuleiro do ficheiro i1.txt:
    board = parse_instance('i1.txt')

    # Imprimir as posições dos robôs:
    print(board.robot_position('Y'))
    print(board.robot_position('G'))
    print(board.robot_position('B'))
    print(board.robot_position('R'))

def test2():
    # Ler tabuleiro do ficheiro 'i1.txt':
    board = parse_instance('i1.txt')

    # Criar uma instância de RicochetRobots:
    problem = RicochetRobots(board)

    # Criar um estado com a configuração inicial:
    initial_state = RRState(board)

    # Mover o robô azul para a esquerda:
    result_state = problem.result(initial_state, ('B', 'l'))

    # Imprimir a posição do robô azul:
    print(result_state.board.robot_position('B'))

def test3():
    # Ler tabuleiro do ficheiro "i1.txt":
    board = parse_instance("i1.txt")

    # Criar uma instância de RicochetRobots:
    problem = RicochetRobots(board)

    # Criar um estado com a configuração inicial:
    s0 = RRState(board)

    # Aplicar as ações que resolvem a instância
    s1 = problem.result(s0, ('B', 'l'))
    s2 = problem.result(s1, ('Y', 'u'))
    s3 = problem.result(s2, ('R', 'r'))
    s4 = problem.result(s3, ('R', 'u'))

    # Verificar que o robô está no alvo:
    print(problem.goal_test(s4))
    print(s4.board.robot_position('R'))

def test4():
    # Ler tabuleiro do ficheiro "i1.txt":
    board = parse_instance("i1.txt")

    # Criar uma instância de RicochetRobots:
    problem = RicochetRobots(board)

    # Obter o nó solução usando a procura A*:
    solution_node = astar_search(problem)

    print("done.")

if __name__ == "__main__":
    test1()
    print("---")
    test2()
    print("---")
    test3()
    print("---")
    test4()
