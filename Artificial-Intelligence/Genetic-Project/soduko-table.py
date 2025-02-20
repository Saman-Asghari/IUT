import numpy as np
import random

def read_sudoku(file_path):
    with open(file_path, 'r') as f:
        return np.array([list(map(int, line.strip().split())) for line in f])

def fitness(board):
    score = 0
    for i in range(9):
        score += len(set(board[i, :])) - 9  
        score += len(set(board[:, i])) - 9
    for x in range(0, 9, 3):
        for y in range(0, 9, 3):
            score += len(set(board[x:x+3, y:y+3].flatten())) - 9
    return score

def create_initial_population(board, population_size):
    population = []
    for _ in range(population_size):
        individual = board.copy()
        for i in range(9):
            for j in range(9):
                if individual[i, j] == 0:
                    possible_values = set(range(1, 10)) - set(individual[i, :]) - set(individual[:, j]) - \
                                      set(individual[i//3*3:(i//3+1)*3, j//3*3:(j//3+1)*3].flatten())
                    if possible_values:
                        individual[i, j] = random.choice(list(possible_values))
                    else:
                        individual[i, j] = random.randint(1, 9)
        population.append(individual)
    return population

def crossover(parent1, parent2):
    child = parent1.copy()
    for x in range(0, 9, 3):
        for y in range(0, 9, 3):
            if random.random() < 0.5:
                child[x:x+3, y:y+3] = parent2[x:x+3, y:y+3]
    return child

def smart_mutate(individual, mutation_rate, initial_board):
    for i in range(9):
        for j in range(9):
            if random.random() < mutation_rate and initial_board[i, j] == 0:
                possible_values = set(range(1, 10)) - set(individual[i, :]) - set(individual[:, j]) - \
                                  set(individual[i//3*3:(i//3+1)*3, j//3*3:(j//3+1)*3].flatten())
                if possible_values:
                    individual[i, j] = random.choice(list(possible_values))
    return individual

def local_search(individual, initial_board):
    for i in range(9):
        for j in range(9):
            if initial_board[i, j] == 0:
                possible_values = set(range(1, 10)) - set(individual[i, :]) - set(individual[:, j]) - \
                                  set(individual[i//3*3:(i//3+1)*3, j//3*3:(j//3+1)*3].flatten())
                if possible_values:
                    individual[i, j] = random.choice(list(possible_values))
    return individual

def genetic_algorithm(board, population_size, generations, mutation_rate):
    initial_board = board.copy()
    population = create_initial_population(board, population_size)
    best_fitness = -np.inf
    best_solution = None
    stagnant_generations = 0  

    for generation in range(generations):
        population = sorted(population, key=fitness, reverse=True)
        current_best_fitness = fitness(population[0])

        if current_best_fitness > best_fitness:
            best_fitness = current_best_fitness
            best_solution = population[0]
            stagnant_generations = 0  
        else:
            stagnant_generations += 1

        if best_fitness == 0:  
            print(f"Solved at Generation {generation}!")
            break
        if stagnant_generations >= 10:  
            print(f"Stopping due to stagnation at Generation {generation}.")
            break

        next_generation = population[:population_size // 2]  
        while len(next_generation) < population_size:
            parent1, parent2 = random.sample(next_generation, 2)
            child = crossover(parent1, parent2)
            child = smart_mutate(child, mutation_rate, initial_board)
            next_generation.append(local_search(child, initial_board))  
        population = next_generation

        print(f"Generation {generation}, Best Fitness: {best_fitness}")

    return best_solution

if __name__ == "__main__":
    board = read_sudoku("sample1_easy.txt")
    solved_board = genetic_algorithm(board, population_size=500, generations=10000, mutation_rate=0.5)
    print("Solved Sudoku:")
    print(solved_board)
