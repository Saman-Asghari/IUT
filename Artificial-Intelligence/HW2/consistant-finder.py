import numpy as np

# i defined the sync function
def sinc(x, y):
    r = np.sqrt(x**2 + y**2)
    return np.sin(x**2 + y**2) / r if r != 0 else 0  #if the dominator is zero i initilize the function with 0



#in this function i calculte the dereviation of the function by both variable x and y
def gradient_sinc(x, y):
    r = np.sqrt(x**2 + y**2)
    if r == 0:
        return 0, 0
    sin_val = np.sin(x**2 + y**2)
    cos_val = np.cos(x**2 + y**2)
    grad_x = (2 * x * cos_val * r - sin_val * x / r) / r  #this is the function derevation by x
    grad_y = (2 * y * cos_val * r - sin_val * y / r) / r  #this is the function derevation by y
    return grad_x, grad_y  #returns the derevations functions



# this function is the main algorithm
def gradient_ascent(start_x, start_y, learning_rate=0.1, iterations=100):
    #learning rate is the value we move in the sinc function
    #iteration is the value of times we iterate through that point we are
    x, y = start_x, start_y
    for _ in range(iterations):
        grad_x, grad_y = gradient_sinc(x, y)  #in here we initlize the value by the function we defined befor
        x += learning_rate * grad_x  #the amount we move for x
        y += learning_rate * grad_y  #the amount we move for y
    return x, y, sinc(x, y)


#due to the question we run the algorithm 10 times
results = []  #we store each algorithm run here
for _ in range(10):
    start_x, start_y = np.random.uniform(-10, 10, 2)  # Random start locations
    max_x, max_y, max_val = gradient_ascent(start_x, start_y)
    results.append((max_x, max_y, max_val))

# in here we show the results for each run
print("Gradient Ascent Results:")
for result in results:
    print(f"Point: ({result[0]:.3f}, {result[1]:.3f}), Sinc value: {result[2]:.3f}")