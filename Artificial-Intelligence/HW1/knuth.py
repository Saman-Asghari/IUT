from queue import Queue,LifoQueue
import math
from decimal import *
from time import time

class Node:
    def __init__(self, data, parent=None, action=None,depth=0):
        self.state = data
        self.parent = parent
        self.action = action
        self.depth=depth


class Knuth:
    def __init__(self, goal):
        self.initial = 4  
        self.goal = goal
        self.actions = ['factorial', 'floor', 'root']
        

    def result(self, parent: Node, action):

        next_data = None  
        if action == 'factorial':
            if isinstance(parent.state, int) and parent.state >= 0 and parent.state <= 100: 
                next_data = int(math.factorial(parent.state))
            else:
                return None 

        elif action == 'floor':
            next_data = math.floor(parent.state)

        elif action == 'root':
            if parent.state >= 0:
                sqrt_value = math.sqrt(parent.state)
                if sqrt_value < float('inf'): 
                    next_data = (sqrt_value) 
                else:
                    return None 
            else:
                next_data = parent.state 
        return Node(next_data, parent, action,depth=parent.depth+1)
        

    def is_goal(self, state):
        return state == self.goal


def expand(problem, node):
    for action in problem.actions:
        temp= problem.result(node, action)
        if temp:
            yield temp


def bfs(problem):
    node = Node(problem.initial) 
    if problem.is_goal(node.state):
        return node
    frontier = Queue() 
    frontier.put(node)
    reached = {problem.initial}  
    while not frontier.empty():
        node = frontier.get() 
        for child in expand(problem, node):
            if problem.is_goal(child.state):
                return child
            if child.state not in reached:
                reached.add(child.state)  
                frontier.put(child)
    
    return None  


def dls(problem, limit):
    node = Node(problem.initial)
    frontier = LifoQueue()
    frontier.put(node)
    result = None

    while not frontier.empty():
        node = frontier.get()

        
        if problem.is_goal(node.state):
            return node

        
        if node.depth >= limit:
            result = "cut-off limit"

        else:
            current = node
            is_cycle = False
            while current.parent is not None:
                if current.parent.state == node.state:
                    is_cycle = True
                    break
                current = current.parent

            if not is_cycle:
                for child in expand(problem, node):
                    frontier.put(child)

    return result


def ids(problem):
    for depth in range(100):
        result = dls(problem, depth)
        if result != "cut-off limit":
            return result
    return None  


def print_solution(solution):
    path = []
    counter=0
    while solution.parent is not None:
        path.append((solution.action, solution.state))
        solution = solution.parent
    path.reverse() 
    print("Solution found:")
    for step in path:
        counter+=1
        print(f"Operation {counter}: {step[0]}, Result: {step[1]}",end=' #### ')

start=time()
problem = Knuth(10)
solution = bfs(problem)
end=time()
if solution:
    print(f"time for this {end-start}")
    print_solution(solution)
else:
    print("No solution found.")
print("\n\n\n")
start=time()
solution=ids(problem)
end=time()
if solution:
    print(f"time for this {end-start}")
    print_solution(solution)
else:
    print("No solution found.")

