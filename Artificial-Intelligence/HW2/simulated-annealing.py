import numpy as np
import math
import random
import time


#define the sinc function
def sinc_function(x, y):
    radius = np.sqrt(x**2 + y**2)
    return np.sin(x**2 + y**2) / radius if radius != 0 else 0


#class for node we use in the sa
class SearchNode:
    def __init__(self, state, parent=None, depth=0, action=None):
        self.state = state
        self.parent = parent
        self.depth = depth
        self.action = action


#class for defining the problem 
class OptimizationProblem:
    def __init__(self, start_state, goal_condition, available_actions):
        self.start_state = start_state
        self.goal_condition = goal_condition
        self.available_actions = available_actions

    #function to check if we reached the goal state
    def goal_reached(self, state):
        if self.goal_condition is None:
            return False
        if isinstance(self.goal_condition, (list, set)):
            return state in self.goal_condition
        return state == self.goal_condition

    #function to avoid loop
    def state_repeats(self, node):
        temp_node = node
        while temp_node.parent:
            temp_node = temp_node.parent
            if temp_node.state == node.state:
                return True
        return False

    #function to apply an action
    def apply_action(self, parent, action):
        parent_state = parent.state
        try:
            updated_state = action(parent_state)
            return SearchNode(updated_state, parent, parent.depth + 1, action)
        except Exception:
            return None


#simulated annealing implementation
def simulated_annealing_solver(problem, cooling_function, value_function):
    start_time = time.perf_counter()
    current_node = SearchNode(problem.start_state)
    step = 1 #used in while


    #it works until the step is below zero
    while True:
        temperature = cooling_function(step)  #we use a function to set temp
        if temperature <= 0:  #if temp is below zero we finish
            return current_node.state, time.perf_counter() - start_time


        #we define neighbors
        neighbors = [problem.apply_action(current_node, act) for act in problem.available_actions]
        neighbors = [node for node in neighbors if node]


        #if the neigbor is empty we are finished
        if not neighbors:
            return current_node.state, time.perf_counter() - start_time


        #we choose randomly
        next_node = random.choice(neighbors)
        delta_value = value_function(*next_node.state) - value_function(*current_node.state)

        #if the value is better we surely accept it else with a probability accept it
        if delta_value > 0:
            current_node = next_node
        else:
            acceptance_prob = math.exp(delta_value / temperature)
            if random.random() < acceptance_prob:
                current_node = next_node

        step += 1


#cooling schedule: exponential decay
def cooling_schedule(step):
    return math.exp(-0.5 * step)


#generate a new neighboring state
def generate_neighbor_state(current_state):
    random_shift = np.random.uniform(-5, 5, size=2)
    return current_state + random_shift


#test simulated annealing on the sinc function
def test_simulated_annealing():
    results = []
    num_trials = 10  #number of tests

    for trial in range(num_trials):
        rng = np.random.default_rng(seed=trial)   #set the random generator
        initial_state = rng.uniform(-5, 5, size=2)
        problem = OptimizationProblem(initial_state, None, [generate_neighbor_state])  #define the problem

        best_state, time_elapsed = simulated_annealing_solver(
            problem, cooling_schedule, sinc_function
        )   #we use this function to solve the problem we defined

        #we show the result here
        results.append(best_state)
        print(f"Trial {trial + 1}: sinc({best_state[0]:.5f}, {best_state[1]:.5f}) = "
              f"{sinc_function(*best_state):.5f} in {time_elapsed:.5f} seconds")

    return results


test_simulated_annealing()