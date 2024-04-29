Code: #pragma ACCEL kernel

void kernel_jacobi_1(double A[8192],double sol[8192])
{
  int i;
  int j;
  double temp;
  double _in_A[8192];
  double _out_sol[8192];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
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