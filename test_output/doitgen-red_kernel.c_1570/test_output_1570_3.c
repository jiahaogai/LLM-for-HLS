#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int alpha,int beta,int tmp[20][24],int A[20][30],int B[30][40],int C[20][40])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 40; j++) {
      tmp[i][j] = 0.0;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (k = 0; k < 30; k++) {
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L2}
      for (j = 0; j < 40; j++) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PARALLEL reduction=C[i][j] FACTOR=auto{__PARA__L3}
      for (i = 0; i < 20; i++) {
        C[i][j] += beta * tmp[i][j];
      }
    }
  }
//#pragma endscop
}