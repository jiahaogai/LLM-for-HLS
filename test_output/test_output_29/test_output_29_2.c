

/* Evaluate the first 500 members of the series: 
 * 1 + 1/1! + 1/2! + 1/3! + ... + 1/k!
 */
 #pragma ACCEL kernel

void bbgemm(double nx,double ny,double nz,double alpha,double beta,double ex[40][50],double ey[50][60],double eze[40][60],double sz[40][50])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{6}
    for (k = 0; k < 60; k++) {
      eze[i][k] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 0; j < 50; j++) {
      
#pragma ACCEL PARALLEL reduction=sz FACTOR=auto{__PARA__L3}
      for (k = 0; k < 60; k++) {
        sz[i][j] += alpha * ey[j][k] * eze[i][k];
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (k = 0; k < 50; k++) {
      
#pragma ACCEL PARALLEL reduction=ex FACTOR=auto{__PARA__L5}
      for (j = 0; j < 60; j++) {
        ex[i][k] += beta * nz * ey[k][j] * sz[i][j];
      }
    }
  }
//#pragma endscop
}
