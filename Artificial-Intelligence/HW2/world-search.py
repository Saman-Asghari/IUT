import random
from queue import Queue


class jarooproblem:
    def __init__(self, m, n):
        #here we initilize the dimensions
        self.m = m   
        self.n = n
        # Generate random positions for the  garbages
        self.garbage_positions = [
            (random.randint(0, m - 1), random.randint(0, n - 1))
            for _ in range(random.randint(1, m * n))
        ]
        #here we print the garbages position
        print(f"Garbage positions: {self.garbage_positions}")

        #generate the initial bilive state
        self.bilive = {
            ((i, j), tuple(self.generate_room_states()))
            for i in range(m)
            for j in range(n)
        }
        #generate the room so we can start the search
        #D shows dirty and C shows clean
    def generate_room_states(self):
        return [
            "D" if (i, j) in self.garbage_positions else "C"
            for i in range(self.m)
            for j in range(self.n)
        ]

    #see if we reached the goal so every room is c
    def is_goal(self, bilief):
        for state in bilief:
            _, room_states = state
            if "D" in room_states:
                return False
        return True


    #in here we define a transition function
    def transition(self, belief_state, action):
        new_belief = set()
        for vacuum_pos, zamin in belief_state:
            x, y = vacuum_pos
            newzamin = list(zamin)

             # Clean the current position
            if action == "suck":
                idx = x * self.n + y
                newzamin[idx] = "C" 
                new_belief.add(((x, y), tuple(newzamin)))


            #we go up in the grid
            elif action == "up" and x > 0:
                new_belief.add(((x - 1, y), tuple(newzamin)))

             #we go down in the grid
            elif action == "down" and x < self.m - 1:
                new_belief.add(((x + 1, y), tuple(newzamin)))
            
                
            #we go left in the grid
            elif action == "left" and y > 0:
                new_belief.add(((x, y - 1), tuple(newzamin)))
                            
            #we go right in the grid
            elif action == "right" and y < self.n - 1:
                new_belief.add(((x, y + 1), tuple(newzamin)))

        return new_belief


    #in this function we solve the problem
    #note that we used bfs here becuase we used a queue and also we create a set of visited possiblities
def sensorless_jaro_solver(m, n):
    problem = jarooproblem(m, n)

    frontier = Queue()
    frontier.put((problem.bilive, []))  # (belief state, actions taken)
    visited = set()


    #bfs condition
    while not frontier.empty():
        current_belief, actions = frontier.get()


        #check we reached the goal
        if problem.is_goal(current_belief):
            return actions


        # To handle unhashable sets  :(((
        belief_tuple = tuple(sorted(current_belief))  
        if belief_tuple in visited:
            continue


        visited.add(belief_tuple)


        #in here we defined for each node what can we do
        for action in ["suck", "up", "down", "left", "right"]:
            new_belief = problem.transition(current_belief, action)
            if new_belief:
                frontier.put((new_belief, actions + [action]))

    return None  # No solution found


# Input m x n dimensions from the user
m = int(input("Enter the number of rows (m): "))
n = int(input("Enter the number of columns (n): "))

# Solve the problem and print the result
solution = sensorless_jaro_solver(m, n)
if solution:
    print("Solution found! Actions to clean the grid:")
    for i, action in enumerate(solution, 1):
        print(f"{i}. {action}")
else:
    print("No solution found.")

