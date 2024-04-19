#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,double A[40][50],double B[50][40],double C[40][50],double D[50][40])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 0; j < 50; j++) {
      A[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 50; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 0; j < 40; j++) {
      B[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      for (k = 0; k < 30; k++) {
        A[i][j] += C4[i][k] * D[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 50; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      for (k = 0; k < 30; k++) {
        B[i][j] += D[i][k] * C[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 0; j < 50; j++) {
      double sum = A[i][j];
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{30}
      for (k = 0; k < 30; k++) {
        sum += B[j][k] * D[k][i];
      }
      C[i][j] = sum;
    }
  }
//#pragma endscop
}