
- '#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}' for the loop over 'p' inside the 'q' loop
- '#pragma ACCEL PIPELINE auto{__PIPE__L3}' for the loop over 'r'
- '#pragma ACCEL TILE FACTOR=auto{__TILE__L3}' for the loop over 'r'
- '#pragma ACCEL PIPELINE auto{__PIPE__L4}' for the loop over 'q'
- '#pragma ACCEL TILE FACTOR=auto{__TILE__L4}' for the loop over 'q'


 #pragma ACCEL kernel

void kernel_seidel_2d(int tsteps,int n,double A[120][120])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (t = 0; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i <= 118; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (j = 1; j <= 118; j++) {
        A[i][j] = (A[i - 1][j - 1] + A[i - 1][j] + A[i - 1][j + 1] + A[i][j - 1] + A[i][j] + A[i][j + 1] + A[i + 1][j - 1] + A[i + 1][j] + A[i + 1][j + 1]) / 9.0;
      }
    }
  }
//#pragma endscop
}