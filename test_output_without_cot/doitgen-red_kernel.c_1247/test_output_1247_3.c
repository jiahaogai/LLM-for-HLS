#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,int n_i,int n_j,double A[40][50][60][80],double B[40][50][60][80],double C[40][50][80][90],double D[40][50][90][100])
{
  int r_i;
  int r_j;
  int r_k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r_i = 0; r_i < 40; r_i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (r_j = 0; r_j < 50; r_j++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (r_k = 0; r_k < 60; r_k++) {
        
#pragma ACCEL PIPELINE auto{__PIPE__L4}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
        for (r_l = 0; r_l < 80; r_l++) {
          
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L5}
          for (i = 0; i < 40; i++) {
            A[i][r_j][r_k][r_l] *= B[i][r_j][r_k][r_l];
          }
        }
      }
      for (r_l = 0; r_l < 80; r_l++) {
        
#pragma ACCEL PIPELINE auto{__PIPE__L6}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
        for (r_k = 0; r_k < 60; r_k++) {
          
#pragma ACCEL PIPELINE auto{__PIPE__L7}
          
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
          for (i = 0; i < 40; i++) {
            C[i][r_j][r_k][r_l] *= D[i][r_j][r_k][r_l];
          }
        }
      }
    }
    for (r_l = 0; r_l < 90; r_l++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L8}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
      for (r_k = 0; r_k < 60; r_k++) {
        
#pragma ACCEL PIPELINE auto{__PIPE__L9}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
        for (r_j = 0; r_j < 50; r_j++) {
          
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L10}
          for (i = 0; i < 40; i++) {
            sum_tmp += A[i][r_j][r_k][r_l] * D[i][r_j][r_k][r_l];
          }
        }
        sum[r_k][r_l] = sum_tmp;
        sum_tmp = ((double )0);
      }
    }
    for (r_l = 0; r_l < 90; r_l++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L11}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L11}
      for (r_k = 0; r_k < 60; r_k++) {
        
#pragma ACCEL PIPELINE auto{__PIPE__L12}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L12}
        for (r_j = 0; r_j < 50; r_j++) {
          
#pragma ACCEL PARALLEL reduction=E FACTOR=auto{__PARA__L13}
          for (i = 0; i < 40; i++) {
            E[i][r_j][r_k][r_l] = A[i][r_j][r_k][r_l] * sum[r_k][r_l];
          }
        }
      }
    }
    for (r_l = 0; r_l < 100; r_l++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L14}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L14}
      for (r_k = 0; r_k < 60; r_k++) {
        
#pragma ACCEL PIPELINE auto{__PIPE__L15}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L15}
        for (r_j = 0; r_j < 50; r_j++) {
          
#pragma ACCEL PARALLEL reduction=F FACTOR=auto{__PARA__L16}
          for (i = 0; i < 40; i++) {
            F[i][r_j][r_k][r_l] *= C[i][r_j][r_k][r_l];
          }
        }
      }
    }
  }
//#pragma endscop
}