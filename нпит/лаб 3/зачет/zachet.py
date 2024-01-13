# SLR(1)

import copy

# выполнить граматическое дополнение
def grammarAugmentation(rules, nonterm_userdef,
						start_symbol):

	newRules = []

	newChar = start_symbol + "'"
	while (newChar in nonterm_userdef):
		newChar += "'"

	# добовление правила для добавлениясимвола начала
	newRules.append([newChar,
					['.', start_symbol]])

	for rule in rules:
	
		# отделить LHS от RHS
		k = rule.split("->")
		lhs = k[0].strip()
		rhs = k[1].strip()
		
		# разделить все правила  '|'
		# сохранить один вывод в одном правиле
		multirhs = rhs.split('|')
		for rhs1 in multirhs:
			rhs1 = rhs1.strip().split()
			
			# добавить точечный укащатель в начале RHS
			rhs1.insert(0, '.')
			newRules.append([lhs, rhs1])
	return newRules


# найти закрытие
def findClosure(input_state, dotSymbol):
	global start_symbol, \
		separatedRulesList, \
		statesDict

	# closureSet хранит обработанные выходные данные
	closureSet = []

	if dotSymbol == start_symbol:
		for rule in separatedRulesList:
			if rule[0] == dotSymbol:
				closureSet.append(rule)
	else:
		closureSet = input_state

	prevLen = -1
	while prevLen != len(closureSet):
		prevLen = len(closureSet)

		tempClosureSet = []

		for rule in closureSet:
			indexOfDot = rule[1].index('.')
			if rule[1][-1] != '.':
				dotPointsHere = rule[1][indexOfDot + 1]
				for in_rule in separatedRulesList:
					if dotPointsHere == in_rule[0] and \
							in_rule not in tempClosureSet:
						tempClosureSet.append(in_rule)

		for rule in tempClosureSet:
			if rule not in closureSet:
				closureSet.append(rule)
	return closureSet


def compute_GOTO(state):
	global statesDict, stateCount

	# find all symbols on which we need to
	# make function call - GOTO
	generateStatesFor = []
	for rule in statesDict[state]:
		# if rule is not "Handle"
		if rule[1][-1] != '.':
			indexOfDot = rule[1].index('.')
			dotPointsHere = rule[1][indexOfDot + 1]
			if dotPointsHere not in generateStatesFor:
				generateStatesFor.append(dotPointsHere)

	# call GOTO iteratively on all symbols pointed by dot
	if len(generateStatesFor) != 0:
		for symbol in generateStatesFor:
			GOTO(state, symbol)
	return


def GOTO(state, charNextToDot):
	global statesDict, stateCount, stateMap

	# newState - stores processed new state
	newState = []
	for rule in statesDict[state]:
		indexOfDot = rule[1].index('.')
		if rule[1][-1] != '.':
			if rule[1][indexOfDot + 1] == \
					charNextToDot:
				# swapping element with dot,
				# to perform shift operation
				shiftedRule = copy.deepcopy(rule)
				shiftedRule[1][indexOfDot] = \
					shiftedRule[1][indexOfDot + 1]
				shiftedRule[1][indexOfDot + 1] = '.'
				newState.append(shiftedRule)

	# add closure rules for newState
	# call findClosure function iteratively
	# - on all existing rules in newState

	# addClosureRules - is used to store
	# new rules temporarily,
	# to prevent concurrent modification error
	addClosureRules = []
	for rule in newState:
		indexDot = rule[1].index('.')
		# check that rule is not "Handle"
		if rule[1][-1] != '.':
			closureRes = \
				findClosure(newState, rule[1][indexDot + 1])
			for rule in closureRes:
				if rule not in addClosureRules \
						and rule not in newState:
					addClosureRules.append(rule)

	# add closure result to newState
	for rule in addClosureRules:
		newState.append(rule)

	# find if newState already present
	# in Dictionary
	stateExists = -1
	for state_num in statesDict:
		if statesDict[state_num] == newState:
			stateExists = state_num
			break

	# stateMap is a mapping of GOTO with
	# its output states
	if stateExists == -1:
	
		# if newState is not in dictionary,
		# then create new state
		stateCount += 1
		statesDict[stateCount] = newState
		stateMap[(state, charNextToDot)] = stateCount
	else:
	
		# if state repetition found,
		# assign that previous state number
		stateMap[(state, charNextToDot)] = stateExists
	return


def generateStates(statesDict):
	prev_len = -1
	called_GOTO_on = []

	# run loop till new states are getting added
	while (len(statesDict) != prev_len):
		prev_len = len(statesDict)
		keys = list(statesDict.keys())

		# make compute_GOTO function call
		# on all states in dictionary
		for key in keys:
			if key not in called_GOTO_on:
				called_GOTO_on.append(key)
				compute_GOTO(key)
	return

# calculation of first
# epsilon is denoted by '#' (semi-colon)

# pass rule in first function
def first(rule):
	global rules, nonterm_userdef, \
		term_userdef, diction, firsts
	
	# recursion base condition
	# (for terminal or epsilon)
	if len(rule) != 0 and (rule is not None):
		if rule[0] in term_userdef:
			return rule[0]
		elif rule[0] == '#':
			return '#'

	# condition for Non-Terminals
	if len(rule) != 0:
		if rule[0] in list(diction.keys()):
		
			# fres temporary list of result
			fres = []
			rhs_rules = diction[rule[0]]
			
			# call first on each rule of RHS
			# fetched (& take union)
			for itr in rhs_rules:
				indivRes = first(itr)
				if type(indivRes) is list:
					for i in indivRes:
						fres.append(i)
				else:
					fres.append(indivRes)

			# if no epsilon in result
			# - received return fres
			if '#' not in fres:
				return fres
			else:
			
				# apply epsilon
				# rule => f(ABC)=f(A)-{e} U f(BC)
				newList = []
				fres.remove('#')
				if len(rule) > 1:
					ansNew = first(rule[1:])
					if ansNew != None:
						if type(ansNew) is list:
							newList = fres + ansNew
						else:
							newList = fres + [ansNew]
					else:
						newList = fres
					return newList

				fres.append('#')
				return fres

def follow(nt):
	global start_symbol, rules, nonterm_userdef, \
		term_userdef, diction, firsts, follows

	solset = set()
	if nt == start_symbol:
		solset.add('$')

	# проверка всех правил
	for curNT in diction:
		rhs = diction[curNT]
		for subrule in rhs:
			if nt in subrule:
				while nt in subrule:
					index_nt = subrule.index(nt)
					subrule = subrule[index_nt + 1:]
					
					# если пустое значение вызовите LHS
					if len(subrule) != 0:

						res = first(subrule)
						
						# если epsilon в результате используем правило
						# - (A->aBX)- follow of -
						# - follow(B)=(first(X)-{ep}) U follow(A)
						if '#' in res:
							newList = []
							res.remove('#')
							ansNew = follow(curNT)
							if ansNew != None:
								if type(ansNew) is list:
									newList = res + ansNew
								else:
									newList = res + [ansNew]
							else:
								newList = res
							res = newList
					else:
					
						# when nothing in RHS, go circular
						# - and take follow of LHS
						# only if (NT in LHS)!=curNT
						if nt != curNT:
							res = follow(curNT)

					# add follow result in set form
					if res is not None:
						if type(res) is list:
							for g in res:
								solset.add(g)
						else:
							solset.add(res)
	return list(solset)


def createParseTable(statesDict, stateMap, T, NT):
	global separatedRulesList, diction

	# создание строк и столбцов
	rows = list(statesDict.keys())
	cols = T+['$']+NT

	# создание пустой таблицы
	Table = []
	tempRow = []
	for y in range(len(cols)):
		tempRow.append('')
	for x in range(len(rows)):
		Table.append(copy.deepcopy(tempRow))

	# запись shift и GOTO в таблице
	for entry in stateMap:
		state = entry[0]
		symbol = entry[1]
		# получение index
		a = rows.index(state)
		b = cols.index(symbol)
		if symbol in NT:
			Table[a][b] = Table[a][b]\
				+ f"{stateMap[entry]} "
		elif symbol in T:
			Table[a][b] = Table[a][b]\
				+ f"S{stateMap[entry]} "

	#начало процедуры сокращения

	# нумерация разделенных правил
	numbered = {}
	key_count = 0
	for rule in separatedRulesList:
		tempRule = copy.deepcopy(rule)
		tempRule[1].remove('.')
		numbered[key_count] = tempRule
		key_count += 1

	# начало процедуры сокращения
	addedR = f"{separatedRulesList[0][0]} -> " \
		f"{separatedRulesList[0][1][1]}"
	rules.insert(0, addedR)
	for rule in rules:
		k = rule.split("->")
		
		# удаление ненужных пробелов
		k[0] = k[0].strip()
		k[1] = k[1].strip()
		rhs = k[1]
		multirhs = rhs.split('|')
		
		# удаление ненужных пробелов
		for i in range(len(multirhs)):
			multirhs[i] = multirhs[i].strip()
			multirhs[i] = multirhs[i].split()
		diction[k[0]] = multirhs

	# find 'handle' items and calculate follow.
	for stateno in statesDict:
		for rule in statesDict[stateno]:
			if rule[1][-1] == '.':
			
				# сопоставьте элемент
				temp2 = copy.deepcopy(rule)
				temp2[1].remove('.')
				for key in numbered:
					if numbered[key] == temp2:
						follow_result = follow(rule[0])
						for col in follow_result:
							index = cols.index(col)
							if key == 0:
								Table[stateno][index] = "Accept"
							else:
								Table[stateno][index] =\
									Table[stateno][index]+f"R{key} "

	print("\nSLR(1) parsing table:\n")
	frmt = "{:>8}" * len(cols)
	print(" ", frmt.format(*cols), "\n")
	ptr = 0
	j = 0
	for y in Table:
		frmt1 = "{:>8}" * len(y)
		print(f"{{:>3}} {frmt1.format(*y)}"
			.format('I'+str(j)))
		j += 1

def printResult(rules):
	for rule in rules:
		print(f"{rule[0]} ->"
			f" {' '.join(rule[1])}")

def printAllGOTO(diction):
	for itr in diction:
		print(f"GOTO ( I{itr[0]} ,"
			f" {itr[1]} ) = I{stateMap[itr]}")

# MAIN

rules = ["A -> b b * a A a b * b B",
		"A -> a b * b B b b * a",
		"B -> a b * b b b * a",
        "B -> b b * a B"
		]
nonterm_userdef = ['A', 'B']
term_userdef = ['a', 'b', '*']
start_symbol = nonterm_userdef[0]


# раздел правил- *END*
print("\nOriginal grammar input:\n")
for y in rules:
	print(y)

# вывод обработанных данных
print("\nGrammar after Augmentation: \n")
separatedRulesList = \
	grammarAugmentation(rules,
						nonterm_userdef,
						start_symbol)
printResult(separatedRulesList)

# нахождения закрытия
start_symbol = separatedRulesList[0][0]
print("\nCalculated closure: I0\n")
I0 = findClosure(0, start_symbol)
printResult(I0)

# statesDictв нем храним мсостояния
# stateMap для хранения GOTO
statesDict = {}
stateMap = {}

# добавить первое состояние statesDict
statesDict[0] = I0
stateCount = 0

# вычисление состояний с помощью GOTO
generateStates(statesDict)

# вывод переходных состояний
print("\nStates Generated: \n")
for st in statesDict:
	print(f"State = I{st}")
	printResult(statesDict[st])
	print()

print("Result of GOTO computation:\n")
printAllGOTO(stateMap)


diction = {}

# вызов функции createParseTable
createParseTable(statesDict, stateMap,
				term_userdef,
				nonterm_userdef)