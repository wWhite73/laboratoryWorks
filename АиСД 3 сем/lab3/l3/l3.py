import colorama
from colorama import Fore, Back
colorama.init()
import random

# Среди максимальных путей в дереве выбрать тот, у которого сумма ключей всех его вершин максимальна,
# затем удалить центральную вершину и корень этого пути (правым удалением). 
# Выполнить прямой (левый) обход полученного дерева.Задание 1. 
# Реализовать бинарное поисковое дерево (ООП):
#- базовые операции: добавление, поиск, удаление (левое и правое);
#- 3 способа обхода дерева: прямой, обратный, симметричный;
#- методы для определения глубины, высоты и уровня узла;
#- вывод дерева на экран в следующем виде:
class Node:
    def __init__(self, val):
        self.parent = None
        self.val = val
        self.left = None
        self.right = None


max_node = Node(0)
max_d = 0
max_height = 0
max_height_node =Node(0)
height = 0

class Tree:
    def __init__(self):
        self.nil = Node(0)
        self.nil.left = None
        self.nil.right = None
        self.root = self.nil

    # вставка
    def insert(self, val):
        new_node = Node(val)
        new_node.parent = None
        new_node.left = self.nil
        new_node.right = self.nil

        parent = None
        current = self.root
        while current != self.nil:
            parent = current
            if new_node.val < current.val:
                current = current.left
            elif new_node.val > current.val:
                current = current.right
            else:
                return

        new_node.parent = parent
        if parent == None:
            self.root = new_node
        elif new_node.val < parent.val:
            parent.left = new_node
        else:
            parent.right = new_node
    # вывод дерева в указанном виде
    def print_tree(self, node):
        def inner(node, *, last = True, pref = ''):
            if node is None:
              return
            print(pref + ('└─' + Fore.MAGENTA + 'L:'+Fore.BLACK if last else '├─'+ Fore.GREEN + 'R:'+Fore.BLACK ) + (str(node.val) if node.val!=0 else "-"))
            inner(node.right, last = False, pref = pref + ('  ' if last else '│ '))
            inner(node.left, last = True, pref = pref + ('  ' if last else '│ '))
        inner(node) 


    def __repr__(self):
        lines = []
        self.print_tree(self.root)
        return '\n'.join(lines)
    # 
    def find_element(self, node, e):
      if node is not None:
          if e == node.val:
           # print()
            print(f"""Элемент {e} найден в дереве!""")
            print(node.val)
            return node
          elif e < node.val:
            self.find_element(node.left, e)
          else:
            self.find_element(node.right, e)
      else:
          print()
          print(f"""Элемент {e} is {'not found'.upper()} in the tree""")
          return None

    # прямой обход дерева
    def pre_order(self, root):
        if root:
            if root.val!=0: print(root.val, end=" ")
            self.pre_order(root.left)
            self.pre_order(root.right)

    # обратный обход дерева
    def post_order(self, root):
        if root:
            self.post_order(root.left)
            self.post_order(root.right)
            if root.val!=0: print(root.val, end=" ")

    # симметричный обход дерева
    def in_order(self, root):
        if root:
            self.in_order(root.left)
            if root.val!=0: print(root.val, end=" ")
            self.in_order(root.right)

    # поиск глубины узла
    def findDepth(self, node, x):
        if (node == None):
            return -1
        dist = -1
        if (node.val == x):
            return dist + 1
        dist = self.findDepth(node.left, x)
        if dist >= 0:
            return dist + 1
        dist = self.findDepth(node.right, x)
        if dist >= 0:
            return dist + 1
        return dist

    # поиск высоты узла
    def findHeightUtil(self, root, x):
        global height
        if (root == None):
          return -1  
        leftHeight = self.findHeightUtil(root.left, x)
        rightHeight = self.findHeightUtil(root.right, x)
        ans = max(leftHeight, rightHeight) + 1
        if (root.val == x):
            height = ans
        return ans

    # определение уровня узла
    def Level(self, root, X):
        if root is None:
            return 0
        q = []
        currLevel = 1
        q.append(root)
        while(len(q) > 0):
            size = len(q)
            for i in range(size):
                node = q.pop(0)
                if(node.val == X):
                    return currLevel
                if node.left is not None:
                    q.append(node.left)
                if node.right is not None:
                    q.append(node.right)
            currLevel += 1
        return 0

    def rb_transplant(self, u, v):
        if u.parent == None:
            self.root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        v.parent = u.parent
    
    # поиск для левого удаления
    def minimum_left(self, node):
        while node.left != self.nil:
            node = node.left
        return node

    # поиск для правого удаления
    def minimum_right(self, node):
        while node.right != self.nil:
            node = node.right
        return node
    
    # удаление узла
    def delete(self, node, key):
        z = self.nil
        while node != self.nil:
            if node.val == key:
                z = node

            if node.val <= key:
                node = node.right
            else:
                node = node.left

        if z == self.nil:
            print("Cannot find key in the tree")
            return

        y = z
        # нет левого ребенка -> правый ребенок на место удаленного
        if z.left == self.nil:
            x = z.right
            self.rb_transplant(z, z.right)
        # нет правого ребенка -> левый ребенок на место удаленного
        elif (z.right == self.nil):
            x = z.left
            self.rb_transplant(z, z.left)
        else:
            y = self.minimum_left(z.right)
            x = y.right
            if y.parent == z:
               x.parent = y
            else:
                self.rb_transplant(y, y.right)
                y.right = z.right
                y.right.parent = y

            self.rb_transplant(z, y)
            y.left = z.left
            y.left.parent = y





    # поиск максимальной глубины
    def MaxDepth(self, root):
        global max_node
        global max_d
        if root:
            if root.val!=0 and max_d< self.findDepth(self.root, root.val):
                max_node = root
                max_d = self.findDepth(self.root, root.val)
            self.MaxDepth(root.left)
            self.MaxDepth(root.right)
        return [max_node, max_d]

# задание вариант 6
def Task(tree):
    global max_node
    global max_d
    global max_height
    global max_height_node
    node_left, depth_left = tree.MaxDepth(tree.root)
    node = node_left
    sums = 0
    while node!=tree.root:
        node = node.parent
        sums += node.val
        if max_height < tree.findHeightUtil(tree.root, node.val):
            max_height =tree.findHeightUtil(tree.root, node.val)
            max_height_node = node
        
    max_height_left = max_height
    max_height_node_left = max_height_node
    max_height = 0
    max_height_node = Node(0)
    max_node = Node(0)
    max_d = 0
    node_right, depth_right = tree.MaxDepth(tree.root.right)
    depth_center = depth_right / 2
    node = node_right
    center_node = node
    while node!=tree.root:
        node = node.parent
        if (type(node) == type(tree.root)):
            if (tree.findHeightUtil(tree.root, node.val) == depth_center):
                center_node = node
            sums += node.val
        if (node== max_height_node_left):
            break
        if max_height < tree.findHeightUtil(tree.root, node.val):
            max_height = tree.findHeightUtil(tree.root, node.val)
            max_height_node = node
        
    max_height_tree = tree.root
    tree.delete(center_node, center_node.val)
    tree.delete(tree.root, max_height_tree.val)
    print(tree)
    print('Длина максимального пути:',depth_left+depth_right+2)
    print('Максимальный путь из узла со значением', node_left.val, 'в узел со значением ', node_right.val )  
    print( 'Сумма ', sums)
    print( 'Удалена центральная вершина ', center_node.val)
    print( 'Удален корень ', max_height_tree.val)
    print('Прямой обход дерева:')
    tree.pre_order(tree.root)
    print()
    



tree = Tree()
for x in range(1, 10):
    v = random.randrange(1,100,1)
    tree.insert(v)
print('Начальное дерево')
print(tree)
while True:
    print('Выберите действие:')
    print('A) Добавить элемент')
    print('B) Удалить элемент')
    print('C) Найти элемент')
    print('D) Прямой обход дерева')
    print('E) Обратный обход дерева')
    print('F) Симметричный обход дерева')
    print('G) Определить глубину узла')
    print('H) Определить высоту узла')
    print('I) Определить уровень узла')
    print('J) Вывести дерево')
    print('TASK) Задание 2')
    print()
    print('X) Выйти')
    print()
    print()

    x = input()
    if x=='A':
      tree.insert(int(input("Введите число для добавления:")))
      print()
    elif x=='B':
      tree.delete(tree.root, int(input("Введите число для удаления:")))
      print()
    elif x=='C':
        tree.find_element(tree.root, int(input("Введите число для поиска:")))
        print()
    elif x=='D':
        tree.pre_order(tree.root)
        print()
    elif x=='E':
        tree.post_order(tree.root)
        print()
    elif x=='F':
        tree.in_order(tree.root)
        print()
    elif x=='G':
        print(tree.findDepth(tree.root, int(input("Введите число для определения глубины:"))))
        print()
    elif x=='H':
        print(tree.findHeightUtil(tree.root, int(input("Введите число для определения высоты:"))))
        print()
    elif x=='I':
        print(tree.Level(tree.root, int(input("Введите число для определения уровня:"))))
        print()
    elif x=='J':
      print(tree)
      print()
    elif x=='TASK':
      Task(tree)
      print()
    elif x=='X':
        exit()
        print()
    else:
        print("Попробуйте снова")
        print()