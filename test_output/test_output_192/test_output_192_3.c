

 #pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,double A[25][20][30],double B[25][30][40],double C[25][40][50])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_q:
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      loop_s:
      for (s = 0; s < 30; s++) {
        A[r][q][s] = ((double )0);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    loop_t:
    for (t = 0; t < 30; t++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_u:
      for (u = 0; u < 40; u++) {
        double sum = 0.0;
        
#pragma ACCEL PIPELINE auto{off}
        loop_v:
        for (v = 0; v < 20; v++) {
          sum += A[r][v][t] * B[v][t][u];
        }
        A[r][q][s] = sum;
      }
    }
  }
}
