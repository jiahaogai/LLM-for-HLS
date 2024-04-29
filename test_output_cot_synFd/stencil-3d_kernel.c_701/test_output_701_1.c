#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[27],long sol[27])
{
  long i;
  long j;
  long k;
  long idx;
  long m;
  long n;
  long o;
  long p;
  long q;
  long r;
  long s;
  long t;
  long u;
  long v;
  long w;
  long x;
  long y;
  long z;
  long A[3][3][3];
  long B[1][3][3][3];
  long tmp[3][3][3];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (i = 0; i < 3; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 3; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 3; k++) {
        idx = i * 3 + j * 3 + k;
        A[i][j][k] = orig[idx];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (m = 0; m < 1; m++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (n = 0; n < 3; n++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (o = 0; o < 3; o++) {
        
#pragma ACCEL PIPELINE auto{flatten}
        
#pragma ACCEL TILE FACTOR=auto{1}
        for (p = 0; p < 3; p++) {
          q = 3 * (3 * (m + 1) + o) + p;
          B[m][n][o][p] = A[n][o][p];
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 3; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (s = 0; s < 3; s++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (t = 0; t < 3; t++) {
        x = 3 * (3 * (r + 1) + s) + t;
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        for (u = 0; u < 3; u++) {
          y = 3 * (3 * (s + 1) + u) + t;
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          for (v = 0; v < 3; v++) {
            z = 3 * (3 * (t + 1) + v) + u;
            tmp[r][s][t] = ((B[0][r][u][v] + B[0][s][v][u]) + B[0][t][u][v]) + C0 * (A[r][s][t] - ((B[1][r][u][v] + B[1][s][v][u]) + B[1][t][u][v]));
          }
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (w = 0; w < 3; w++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (x = 0; x < 3; x++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (y = 0; y < 3; y++) {
        for (v = 0; v < 3; v++) {
          sol[idx] = tmp[w][x][y];
          idx++;
        }
      }
    }
  }
}