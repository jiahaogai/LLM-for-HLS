#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,double A[40][50],double B[50][40],double C[40][80],double D[80][50])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 80; j++) {
      D[i][j] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (k = 0; k < 50; k++) {
      
#pragma ACCEL PARALLEL reduction=D FACTOR=auto{__PARA__L3}
      for (j = 0; j < 40; j++) {
        D[i][k] += A[i][j] * B[j][k];
      }
    }
  }
//#pragma endscop
}