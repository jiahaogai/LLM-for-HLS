
 #pragma ACCEL kernel

void kernel_seidel_2d(int orig_A[25][20],int sol[25][20],int filter[3][3])
{
  int i;
  int j;
  int k;
  int l;
  int i0;
  int j0;
  int tmp;
  int tmp_row;
  int tmp_col;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
  for (j = 2; j < 18; j++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    loopi:
    for (i = 2; i < 18; i++) {
      tmp_row = ((int )0);
      
#pragma ACCEL PIPELINE auto{off}
      loopk:
      for (k = 0; k < 3; k++) {
        tmp_col = ((int )0);
        
#pragma ACCEL PIPELINE auto{__PIPE__L4}
        loopl:
        for (l = 0; l < 3; l++) {
          i0 = i - 1 + k;
          j0 = j - 1 + l;
          mul = filter[k][l] * orig_A[i0][j0];
          tmp_col += mul;
        }
        tmp_row += tmp_col;
      }
      sol[i][j] = tmp_row;
      tmp = orig_A[i][j];
      aj < 20; j++) {
    orig_A[i][j] = ((int )1);
  }
}
}
dd = (tmp_row - tmp);
      mul = (seidel_coeff * add);
      if (mul < ((int )0)) {
        mul = -mul;
      }
      if (mul < ((int )1e-2)) {
        mul = ((int )1e-2);
      }
      if (mul > ((int )1e2)) {
        mul = ((int )1e2);
      }
      mul = mul * orig_A[i][j];
      if (mul > ((int )(18 * 20))) {
        mul = ((int )(18 * 20));
      }
      if (mul < ((int )(-18 * 20))) {
        mul = ((int )(-18 * 20));
      }
      orig_A[i][j] = tmp + mul;
    }
  }
}
void kernel_seidel_2d_init(int orig_A[25][20],int filter[3][3])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 0; j < 20; j++) {
      orig_A[i][j] = (i * j + 1) + 1;
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      filter[i][j] = 1;
    }
  }
}
void kernel_seidel_2d_exit(int sol[25][20])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 2; i < 25 - 2; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (j = 2; j < 20 - 2; j++) {
      sol[i][j] = ((long )((double )sol[i][j] * sqrt(((double )((int )1)) / ((double )seidel_coeff)))) + ((long )((double )((int )18) * sqrt(((double )((int )1)) / ((double )seidel_coeff)))) + ((long )(orig_A[i][j])) - ((long )(sol[i - 2L][j - 2L])) - ((long )(sol[i - 2L][j])) - ((long )(sol[i][j - 2L])) - ((long )(sol[i - 2L][j + 2L])) - ((long )(sol[i + 2L][j - 2L])) - ((long )(sol[i + 2L][j])) - ((long )(sol[i][j + 2L]));
    }
  }
}
int main()
{
  int orig_A[25][20] = {{1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}};
  int sol[25][20] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};
  int filter[3][3] = {{1, 1, 1}, {1, -7, 1}, {1, 1, 1}};
  
#pragma ACCEL kernel
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  kernel_seidel_2d(orig_A,sol,filter);
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  kernel_seidel_2d_exit(sol);
}
 
#pragma ACCEL PARALLEL FACTOR=auto{1}

void kernel_seidel_2d(int orig_A[25][20],int sol[25][20],int filter[3][3])
{
  int i;
  int j;
  int k;
  int l;
  int i0;
  int j0;
  int tmp;
  int tmp_row;
  int tmp_col;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
  for (j = 2; j < 18; j++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    loopi:
    for (i = 2; i < 18; i++) {
      tmp_row = ((int )0);
      
#pragma ACCEL PIPELINE auto{off}
      loopk:
      for (k = 0; k < 3; k++) {
        tmp_col = ((int )0);
        
#pragma ACCEL PIPELINE auto{__PIPE__L4}
        loopl:
        for (l = 0; l < 3; l++) {
          i0 = i - 1 + k;
          j0 = j - 1 + l;
          mul = filter[k][l] * orig_A[i0][j0];
          tmp_col += mul;
        }
        tmp_row += tmp_col