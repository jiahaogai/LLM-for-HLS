#pragma ACCEL kernel

void stencil3d(double C0,double C1,double orig[2][2][2],double sol[2][2][2])
{
  int t1;
  int t2;
  int t3;
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (t1 = 0; t1 < 2; t1++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (t2 = 0; t2 < 2; t2++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (t3 = 0; t3 < 2; t3++) {
        sol[t1][t2][t3] = C0;
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        for (i = 1; i < 2; i++) {
          
#pragma ACCEL PARALLEL FACTOR=auto{2}
          for (j = 1; j < 2; j++) {
            
#pragma ACCEL PARALLEL FACTOR=auto{2}
            for (k = 1; k < 2; k++) {
              sol[t1][t2][t3] += 
                C1 * (orig[t1][i - 1][k] + orig[t1][i][k] + 
                      orig[t1][i + 1][k] + orig[t1][i][k - 1] + 
                      orig[t1][i][k + 1] + orig[t1][i - 1][k - 1] + 
                      orig[t1][i - 1][k + 1] + orig[t1][i + 1][k - 1] + 
                      orig[t1][i + 1][k + 1] + orig[t2][i][k] + 
                      orig[t2][i - 1][k] + orig[t2][i + 1][k] + 
                      orig[t2][i][k - 1] + orig[t2][i][k + 1] + 
                      orig[t2][i - 1][k - 1] + orig[t2][i - 1][k + 1] + 
                      orig[t2][i + 1][k - 1] + orig[t2][i + 1][k + 1] + 
                      orig[t3][i][k - 1] + orig[t3][i][k + 1] + 
                      orig[t3 - 1][i][k] + orig[t3 + 1][i][k]);
            }
          }
        }
      }
    }
  }
//#pragma endscop
}