#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,double A[20][22],double B[22][24],double C[20][24],double D[20][24])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 24; j++) {
      double tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction FACTOR=auto{30}
      for (k = 0; k < 22; k++) {
        tmp += A[i][k] * B[k][j];
      }
      D[i][j] = tmp;
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 24; j++) {
      double tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction FACTOR=auto{1}
      for (k = 0; k < 20; k++) {
        tmp += A[k][i] * D[k][j];
      }
      C[i][j] = tmp;
    }
  }
//#pragma endscop
}