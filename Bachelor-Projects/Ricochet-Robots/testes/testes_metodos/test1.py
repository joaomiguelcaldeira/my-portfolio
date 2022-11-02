# test1.py: testa parse_instance e Board

from ricochet_robots import *

board = parse_instance('instances/i3.txt')

# Verificar as posições dos robôs:
print(board.robot_position('Y'))
print(board.robot_position('G'))
print(board.robot_position('B'))
print(board.robot_position('R'))

# ---
board = parse_instance('instances/i4.txt')

print(board.robot_position('R'))
print(board.robot_position('G'))
print(board.robot_position('B'))
print(board.robot_position('Y'))
