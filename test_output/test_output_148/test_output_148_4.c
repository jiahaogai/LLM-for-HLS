

 #pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,double A[25][20][30],double C4[30][30],double B[25][30],double D[20][30],double E[25][20])
{
  int r;
  int q;
  int p;
  int a;
  int b;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L3}
      for (a = 0; a < 30; a++) {
        A[r][q][a] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{__PARA__L5}
      for (a = 0; a < 30; a++) {
        B[r][a] += D[q][a] * E[r][q];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L0}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PARALLEL reduction=C4 FACTOR=auto{__PARA__L7}
      for (a = 0; a < 30; a++) {
        C4[a] += A[r][q][a] * B[r][a];
      }
    }
  }
}
