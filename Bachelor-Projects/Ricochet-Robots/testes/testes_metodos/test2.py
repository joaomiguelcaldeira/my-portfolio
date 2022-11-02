# test2.py: testa result e Board

from ricochet_robots import *

board = parse_instance('instances/i1.txt')
problem = RicochetRobots(board)
initial_state = RRState(board)

# Mover o robô azul para a esquerda (deve bater numa barreira):
result_state = problem.result(initial_state, ('B', 'l'))
print(result_state.board.robot_position('B'))

# ---
board = parse_instance('instances/i2.txt')
problem = RicochetRobots(board)
initial_state = RRState(board)

# Mover o robô azul para a esquerda. Não deve alterar a posição do robô:
s1 = problem.result(initial_state, ('B', 'l'))
print(s1.board.robot_position('B'))

# Mover o robô amarelo para baixo:
s1 = problem.result(initial_state, ('Y', 'd'))

# Mover robô azul para baixo. Deve colidir com o amarelo:
s2 = problem.result(s1, ('B', 'd'))

# Imprimir a posição dos robôs:
print(s2.board.robot_position('Y'))
print(s2.board.robot_position('B'))

# Mover robô azul para baixo. Não deve alterar a posição do robô:
s3 = problem.result(s1, ('B', 'd'))
print(s3.board.robot_position('Y'))
