

# Parallel Sparse Matrix-Vector Multiplication (PSVM)

This example computes an approximation of the function y = Axapprox, where A is a m x n sparse matrix in the CSR format, x is a n x 1 dense vector, and y is a m x 1 dense vector. The matrix A is approximated by a subset of its nonzero elements specified by the vector S. The subset is chosen such that the number of nonzero elements in the new matrix is less than a specified threshold. The approximation error is computed as follows:
```
e = y - Axapprox
ae = y - Ax
```
where xapprox is the computed approximation.

## Authors:

- [Alessandro Iadarola](https://github.com/alessandro-iadarola)

## Build and Run Instructions

To build and run the application, execute the following steps:

1. Build the program using the following `make` command:

```bash
    make
```

2. Run the program using the following command:

```bash
    make run
```

3. You will see the following output:

```bash
========= Program result =========

Optimal threshold = 2
Error = 0.43773444099999999898
Time = 0.169614
```

### Input

The input consists of two files:

* `A.csr` is the sparse matrix in the CSR (Compressed Sparse Row) format.
* `S.csr` is the list of nonzero elements in the matrix A that will be used to compute the approximation y.

### Data

The sparse matrix A and the vector x are stored in a text file. Each row of the matrix contains the indices of the elements of the row in the text file. The row indices are stored first, then the column indices and finally the values of the nonzero elements. The vector x is also stored in a text file. The elements of x are also stored in a text file. The files are in Matlab (.mat) format.

### License

This example is released under the [3-Clause BSD License](https://github.com/intel/