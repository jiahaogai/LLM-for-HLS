
				#pragma ACCEL PIPELINE auto{off}
				
				//#pragma ACCEL TILE FACTOR=auto{1}
				 
				//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
				for (tj = 4; tj <= 36; tj += 4) {
				  L2:
				  for (ti = 4; ti <= 36; ti += 4) {
				    mult[tj][ti] = x[tj][ti] * y[tj][ti];
				  }
				}
				
				//#pragma ACCEL PIPELINE auto{off}
				
				//#pragma ACCEL TILE FACTOR=auto{1}
				 
				//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
				for (tj = 4; tj < 40; tj++) {
				  sj = tj * 20;
				  
#pragma ACCEL PIPELINE auto{off}
				  L3:
				  for (ti = 4; ti < 40; ti++) {
				    si = ti * 20;
				    s = 0.0;
				    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
				    L4:
				    for (aj = 0; aj < 4; aj++) {
				      L5:
				      for (ai = 0; ai < 4; ai++) {
				        s = s + x[sj + aj][si + ai] * mult[aj][ai + ti];
				      }
				    }
				    z[sj][si] = s;
				  }
				}
			  }
			}
		  }
		}
	 }
  }
  
#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[20][20],double ey[20][20],double hz[20][20],double _fict_[40])
{
  int t;
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 20; j++) {
      ey[j][0] = _fict_[j];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i = 0; i < 20; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 0; j < 20; j++) {
        ex[j][i] = 0.0;
      }
      
      ey[i][0] = 0.0;
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (k = 1; k < 20; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
        for (j = 0; j < 20; j++) {
          ex[j][i] += 0.25 * (hz[j][k + 1] - hz[j][k - 1]) + 0.25 * (hz[j + 1][k + 1] - hz[j - 1][k + 1]) - 0.25 * (hz[j + 1][k - 1] - hz[j - 1][k - 1]);
        }
        ey[i][k] = 0.0;
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
        for (j = 0; j < 20; j++) {
          ey[j][i] += 0.25 * (hz[k + 1][j] - hz[k - 1][j]) + 0.25 * (hz[j + 1][k + 1] - hz[j - 1][k + 1]) - 0.25 * (hz[j + 1][k - 1] - hz[j - 1][k - 1]);
        }
        hz[i][k] = _fict_[i * k] + 0.25 * (ex[i][k] - ex[i][k - 1]) + 0.25 * (ey[i][k] - ey[i][k - 1]);
      }
    }
  }
//#pragma endscop
}
