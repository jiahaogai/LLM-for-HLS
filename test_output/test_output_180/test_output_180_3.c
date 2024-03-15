
 *
 * @param tsteps
 * @param A
 * @param B
 * @param C
 * @param D
 */
 #pragma ACCEL kernel

void kernel_2mm(double A[250][250],double B[250][250],double C[250][250],double D[250][250])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 250; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (j = 0; j < 250; j++) {
      A[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 250; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    for (j = 0; j < 250; j++) {
      B[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 250; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    for (k = 0; k < 250; k++) {
      for (j = 0; j < 250; j++) {
        A[i][j] += C[k][i] * D[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 250; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    for (j = 0; j < 250; j++) {
      for (k = 0; k < 250; k++) {
        B[i][j] += A[k][j] * D[k][i];
      }
    }
  }
//#pragma endscop
}
