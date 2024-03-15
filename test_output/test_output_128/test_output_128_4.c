  
To annotate PE, use `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}`  
To annotate PE, use `#pragma ACCEL PIPELINE auto{__PIPE__L0}`  
To annotate TILE FACTOR=auto{1}, use `#pragma ACCEL TILE FACTOR=auto{__TILE__L0}`  
To annotate PE, use `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}`  
To annotate PIPELINE auto{__PIPE__L1}, use `#pragma ACCEL PIPELINE auto{__PIPE__L1}`  
To annotate TILE FACTOR=auto{__TILE__L1}, use `#pragma ACCEL TILE FACTOR=auto{__TILE__L1}`  
To annotate PARALLEL FACTOR=auto{__PARA__L2}, FACTOR=auto{32}, SCALE=auto{2}  
To annotate PARALLEL FACTOR=auto{__PARA__L3}, FACTOR=auto{__PARA__L3}, SCALE=auto{__SCALE__L3}  
  
#pragma ACCEL kernel

void kernel_jacobi_2d(int tsteps,int n,double A[90][90],double B[90][90])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{__PIPE__L0}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (i = 1; i < 89; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{12}
      for (j = 1; j < 89; j++) {
        B[i][j] = 0.2 * (A[i][j] + A[i][j - 1] + A[i][1 + j] + A[1 + i][j] + A[i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 89; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (j = 1; j < 89; j++) {
        A[i][j] = 0.2 * (B[i][j] + B[i][j - 1] + B[i][1 + j] + B[1 + i][j] + B[i - 1][j]);
      }
    }
  }
//#pragma endscop
}
