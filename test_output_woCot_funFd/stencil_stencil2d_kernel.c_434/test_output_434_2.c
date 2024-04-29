Code: #pragma ACCEL kernel

<<<<<<< HEAD
void kernel_jacobi_1(double A[8192],double sol[8192])
{
  int i;
  int j;
  double temp;
  double _in_A[8192];
  double _out_sol[8192];
=======
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int pad;
  pad = 1;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 64; j++) {
      _in_A[i * 64 + j] = A[i * 64 + j];
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      temp = (_in_A[i * 64 + j] + ((_in_A[i * 64 + j + 1] + _in_A[i * 64 + j - 1]) + (_in_A[(i - 1) * 64 + j] + _in_A[(i + 1) * 64 + j])) / 4.0);
      if (temp < 0.0) {
        temp = 0.0;
      }
      _out_sol[i * 64 + j] = temp;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      sol[i * 64 + j] = _out_sol[i * 64 + j];
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: expected identifier or ‘(’ before ‘void’
 void kernel_jacobi_1(double A[8192],double sol[8192])
 ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: expected identifier or ‘(’ before ‘void’
 void kernel_jacobi_1(double A[8192],double sol[8192])
 ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: expected identifier or ‘(’ before ‘void’
 void kernel_jacobi_1(double A[8192],double sol[8192])
 ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: expected identifier or ‘(’ before ‘void’
 void kernel_jacobi_1(double A[8192],double sol[8192])
 ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: expected identifier or ‘(’ before ‘void’
 void kernel_jacobi_1(double A[8192],double sol[8192])
 ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: expected identifier or ‘(’ before ‘void’
 void kernel_jacobi_1(double A[8192],double sol[8192])
 ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: expected identifier or ‘(’ before ‘void’
 void kernel_jacobi_1(double A[8192],double sol[8192])
 ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error:
=======
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0;
      inner:
      for (k = -1 * pad; k <= 1 * pad; k++) {
        int cur;
        cur = orig[i * 8 + j + k];
        sum += cur;
      }
      sol[i * 8 + j] = sum;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer_2:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle_2:
    for (j = 0; j < 8; j++) {
      int sum = 0;
      int pad;
      pad = 1;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner_2:
      for (k = -1 * pad; k <= 1 * pad; k++) {
        int cur;
        cur = sol[(((i - 1) * 8) + j) + k];
        sum += cur;
      }
      sol[i * 8 + j] = sum;
    }
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
