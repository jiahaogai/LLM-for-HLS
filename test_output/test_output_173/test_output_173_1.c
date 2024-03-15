
- '#pragma ACCEL PIPELINE auto{__PIPE__L3}' for the loop over 'r' inside the 'kernel_seidel_2d' loop
- '#pragma ACCEL TILE FACTOR=auto{__TILE__L3}' for the loop over 'r' inside the 'kernel_seidel_2d' loop
- '#pragma ACCEL PIPELINE auto{__PIPE__L2}' for the loop over 'q' inside the 'kernel_seidel_2d' loop
- '#pragma ACCEL TILE FACTOR=auto{__TILE__L2}' for the loop over 'q' inside the 'kernel_seidel_2d' loop
- '#pragma ACCEL PIPELINE auto{__PIPE__L1}' for the loop over 'p' inside the 'kernel_seidel_2d' loop
- '#pragma ACCEL TILE FACTOR=auto{__TILE__L1}' for the loop over 'p' inside the 'kernel_seidel_2d' loop


 #pragma ACCEL kernel

void kernel_seidel_2d(int tsteps,int n,double A[120][120])
{
  int t;
  int p;
  int q;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (p = 1; p <= 118; p++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (q = 1; q <= 118; q++) {
        A[p][q] = (A[p - 1][q - 1] + A[p - 1][q] + A[p - 1][q + 1] + A[p][q - 1] + A[p][q] + A[p][q + 1] + A[p + 1][q - 1] + A[p + 1][q] + A[p + 1][q + 1]) / 9.0;
      }
    }
  }
//#pragma endscop
}
