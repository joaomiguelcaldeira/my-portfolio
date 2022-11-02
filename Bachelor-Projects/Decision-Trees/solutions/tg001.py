# -*- coding: utf-8 -*-
"""
Grupo tg01
Student id #93729
Student id #93730
"""

import math
import numpy as np
import copy


def get_branch_major_case(Y):
	countPositive = 0
	countNegative = 0
	for e in Y:
		if(e == 1):
			countPositive += 1
		if(e == 0):
			countNegative += 1
	if(countPositive > countNegative):
		return 1
	else:
		return 0

def entropy(trueCases, falseCases):
	if(trueCases == 0 or falseCases == 0):
		return 0
	else:
		return -trueCases * math.log2(trueCases) - falseCases * math.log2(falseCases)

def calc_GI_caracteristic(D, Y, caracteristic, tamanho_treino, init_I):
	count_P_False = 0
	count_P_True = 0
	count_N_True = 0
	count_N_False = 0
	index = 0
	positiveDoubt = 0
	falseDoubt = 0
	while (index < tamanho_treino):
		if (Y[index] == -1):
			index += 1
			continue
		if (D[index][caracteristic]):  
			if (Y[index]):
				count_P_True += 1
			else:
				count_P_False += 1
		else:  
			if (Y[index]):
				count_N_True += 1
			else:
				count_N_False += 1
		index += 1
	if (count_P_True == 0 or count_P_False == 0):
		positiveDoubt = 0
	else:
		positiveDoubt = (float((count_P_True + count_P_False) / tamanho_treino)) * entropy(
			float(count_P_True / (count_P_True + count_P_False)), float(count_P_False / (count_P_True + count_P_False)))
	if (count_N_True == 0 or count_N_False == 0):
		falseDoubt = 0
	else:
		falseDoubt = (float((count_N_True + count_N_False) / tamanho_treino)) * entropy(
			float(count_N_True / (count_N_True + count_N_False)), float(count_N_False / (count_N_True + count_N_False)))
	return [(init_I - (positiveDoubt + falseDoubt)), [positiveDoubt,count_P_True,count_P_False], [falseDoubt,count_N_True,count_N_False]]

def calc_init_doubt(Y):
	countTrue = 0
	countFalse = 0
	count = 0
	while (count < len(Y)):
		if (Y[count]):
			countTrue += 1
		else:
			countFalse += 1
		count += 1
	nT = float(countTrue / len(Y))
	nF = float(countFalse / len(Y))
	return entropy(nT, nF)

def create_caracteristic_list(D):
	i = 0
	lst = []
	while (i < len(D[0])):
		if not (D[0][i] == -1):
			lst.append(i)
		i += 1
	return lst

def get_caracteristic_size(D):
	i = 0
	count = 0
	while (i < len(D[0])):
		if not (D[0][i] == -1):
			count += 1
		i += 1
	return count

def create_sub_scenario(D, Y, caracteristic, n):
	count = 0
	for e in D:
		if not (int(e[caracteristic]) == n):
			Y[count] = -1
		e[caracteristic] = -1
		count += 1
	return 0

def short_tree(tree):
	if(tree[1] == tree[2] and type(tree[1]) == list):
		return tree[2]
	else:
		return tree

def createdecisiontree(D, Y, noise=False):
	D = D.astype(int)
	Y = Y.astype(int)
	tamanho_treino = len(D)
	caracteristic_list = create_caracteristic_list(D)
	I = calc_init_doubt(Y)
	tree = []
	hypothesis_tree = []
	positive_caracteristic = 1
	false_caracteristic = 1
	gi = -1
	select_caracteristic = 0
	for e in caracteristic_list:
		caracteristic_gi = calc_GI_caracteristic(D, Y, e, tamanho_treino, I)
		if (caracteristic_gi[0] > gi):
			gi = caracteristic_gi[0]
			select_caracteristic = e
			positive_caracteristic = caracteristic_gi[1]
			false_caracteristic = caracteristic_gi[2]
	if(0 < gi < 0.05):
		return get_branch_major_case(Y)
	if  (false_caracteristic[0] != 0 and positive_caracteristic[0] != 0):
		new_D_L = D.copy()
		new_Y_L = Y.copy()
		create_sub_scenario(new_D_L, new_Y_L, select_caracteristic, 0)
		left_caracteristic_list = create_caracteristic_list(new_D_L)
		Left_I = calc_init_doubt(new_Y_L)
		gi_left = -1
		select_caracteristic_left = -1
		for e in left_caracteristic_list:
			l_caracteristic_gi = calc_GI_caracteristic(new_D_L, new_Y_L, e, len(new_D_L), Left_I)
			if (l_caracteristic_gi[0] > gi_left):
				gi_left = l_caracteristic_gi[0]
				select_caracteristic_left = e

		new_D_R = D.copy()
		new_Y_R = Y.copy()
		create_sub_scenario(new_D_R, new_Y_R, select_caracteristic, 1)
		right_caracteristic_list = create_caracteristic_list(new_D_R)
		Right_I = calc_init_doubt(new_Y_R)
		gi_right = -1
		select_caracteristic_right = -1
		for e in right_caracteristic_list:
			r_caracteristic_gi = calc_GI_caracteristic(new_D_R, new_Y_R, e, len(new_D_R), Right_I)
			if (r_caracteristic_gi[0] > gi_right):
				gi_right = r_caracteristic_gi[0]
				select_caracteristic_right = e
		if(select_caracteristic_left == select_caracteristic_right and select_caracteristic_left != -1):
			hypothesis_tree.append(select_caracteristic_left)
			newGi = calc_GI_caracteristic(D, Y, select_caracteristic_left, tamanho_treino, I)
			trueGi = newGi[1]
			falseGi = newGi[2]
			if (falseGi[0] == 0):
				count = 0
				while (count < tamanho_treino):
					if (D[count][select_caracteristic_left] == 0):
						if (Y[count] == 1):
							hypothesis_tree.append(1)
							break
						if(Y[count] == 0):
							hypothesis_tree.append(0)
							break
					count += 1
			else:
				new_D_F = D.copy()
				new_Y_F = Y.copy()
				create_sub_scenario(new_D_F, new_Y_F, select_caracteristic_left, 0)
				if(get_caracteristic_size(new_D_F) == 0):
					if(falseGi[1] > falseGi[2]):
						hypothesis_tree.append(1)
					else:
						hypothesis_tree.append(0)
				else:
					hypothesis_tree.append(createdecisiontree(new_D_F, new_Y_F))
			if (trueGi[0] == 0):
				count = 0
				while (count < tamanho_treino):
					if (D[count][select_caracteristic_left]):
						if (Y[count] == 1):
							hypothesis_tree.append(1)
							break
						if (Y[count] == 0):
							hypothesis_tree.append(0)
							break
					count += 1
			else:
				new_D_P = D.copy()
				new_Y_P = Y.copy()
				create_sub_scenario(new_D_P, new_Y_P, select_caracteristic_left, 1)
				if(get_caracteristic_size(new_D_P) == 0):
					if(trueGi[1] > trueGi[1]):
						hypothesis_tree.append(1)
					else:
						hypothesis_tree.append(0)
				else:
					hypothesis_tree.append(createdecisiontree(new_D_P, new_Y_P))
			hypothesis_tree = short_tree(hypothesis_tree)
	tree.append(select_caracteristic)
	if (false_caracteristic[0] == 0):
		count = 0
		while (count < tamanho_treino):
			if (D[count][select_caracteristic] == 0):
				if (Y[count] == 1):
					tree.append(1)
					break
				if(Y[count] == 0):
					tree.append(0)
					break
			count += 1
	else:
		new_D_F = D.copy()
		new_Y_F = Y.copy()
		create_sub_scenario(new_D_F, new_Y_F, select_caracteristic, 0)
		if(get_caracteristic_size(new_D_F) == 0):
			if(false_caracteristic[1] > false_caracteristic[2]):
				tree.append(1)
			else:
				tree.append(0)
		else:
			tree.append(createdecisiontree(new_D_F, new_Y_F))
	if (positive_caracteristic[0] == 0):
		count = 0
		while (count < tamanho_treino):
			if (D[count][select_caracteristic]):
				if (Y[count] == 1):
					tree.append(1)
					break
				if (Y[count] == 0):
					tree.append(0)
					break
			count += 1
	else:
		new_D_P = D.copy()
		new_Y_P = Y.copy()
		create_sub_scenario(new_D_P, new_Y_P, select_caracteristic, 1)
		if(get_caracteristic_size(new_D_P) == 0):
			if(positive_caracteristic[1] > positive_caracteristic[1]):
				tree.append(1)
			else:
				tree.append(0)
		else:
			tree.append(createdecisiontree(new_D_P, new_Y_P))
	tree = short_tree(tree)
	if(hypothesis_tree != []):
		if(len(str(hypothesis_tree)) < len(str(tree))):
			return hypothesis_tree
		else:
			return tree
	return tree