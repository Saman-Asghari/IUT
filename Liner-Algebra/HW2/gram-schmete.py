import numpy as np

def orthogonalize(v, Q, j):
    #Subtract projections of v onto all previous orthonormal vectors in Q.
    for i in range(j):
        projection = np.dot(Q[:, i], v) * Q[:, i]
        v -= projection
    return v

def normalize_vector(v):
    #Return a normalized vector if it's not near zero; otherwise, return None.
    norm_v = np.linalg.norm(v)
    if norm_v > 1e-10:
        return v / norm_v, norm_v
    else:
        return None, 0

def check_dependency(A, Q, j):
    #Identify if a column vector is dependent, and compute dependency coefficients if so.
    coeffs = [np.dot(A[:, j], Q[:, i]) for i in range(j)]
    return coeffs

def gram_schmidt_process(A):
    rows, cols = A.shape
    Q = np.zeros((rows, cols))
    R = np.zeros((cols, cols))
    dep_vectors = []
    dep_coefficients = []

    for j in range(cols):
        v = A[:, j].astype(float)  # Convert column vector to float to avoid casting issues
        v = orthogonalize(v, Q, j)
        v_normalized, norm_v = normalize_vector(v)
        
        if v_normalized is not None:
            Q[:, j] = v_normalized
            R[j, j] = norm_v
        else:
            dep_vectors.append(j + 1)  # 1-based indexing for output
            dep_coefficients.append(check_dependency(A, Q, j))

    return Q, (dep_vectors, dep_coefficients) if dep_vectors else None

# Test the function with example matrices

print("\n\ntest case 1: ")
A = np.array([[1, 2, -1, 3],
              [1, 2, 2, 4]])

Q, dep_info = gram_schmidt_process(A)

# Display results
orthonormal_basis = Q[:, np.any(Q != 0, axis=0)]
print("orthonormal basis:\n", orthonormal_basis)

if dep_info is None:
    print("All vectors are linearly independent.")
else:
    dep_indices, coeff = dep_info
    print("Index of dependent vectors:", dep_indices)
    print("coefficients for dependent vectors:\n", coeff)


print("\n\ntest case 2 :")

A = np.array([[1,1, 1, 1],
              [1, -1, -1, 0]
              ,[-1,1,-1,0],
              [-1,-1,1,-1]])

Q, dep_info = gram_schmidt_process(A)

# Display results
orthonormal_basis = Q[:, np.any(Q != 0, axis=0)]
print("Orthonormal basis:\n", orthonormal_basis)

if dep_info is None:
    print("All vectors are linearly independent.")
else:
    dep_indices, coeff = dep_info
    print("Indices of dependent vectors:", dep_indices)
    print("Coefficients for dependent vectors:\n", coeff)



print("\n\ntest case 3 :")

A = np.array([[1, 1, 1, 1],
              [0, 1, 1, 1]
              ,[0,0,1,1],
              [0,0,0,1],
              [0,0,0,0]])

Q, dep_info = gram_schmidt_process(A)

# Display results
orthonormal_basis = Q[:, np.any(Q != 0, axis=0)]
print("Orthonormal basis:\n", orthonormal_basis)

if dep_info is None:
    print("All vectors are linearly independent.")
else:
    dep_indices, coeff = dep_info
    print("Indices of dependent vectors:", dep_indices)
    print("Coefficients for dependent vectors:\n", coeff)

