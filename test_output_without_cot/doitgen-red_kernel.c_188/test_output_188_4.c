Reduce `sum_tmp` using: `A[i][j][k]`.
- `#pragma ACCEL PIPELINE auto{__PIPE__L2}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L2}`: 
- `#pragma ACCEL PARALLEL FACTOR=auto{2}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L3}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L3}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L4}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L4}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L5}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L5}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L6}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L6}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L7}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L7}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L8}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L8}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L9}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L9}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L10}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L10}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L11}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L11}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L12}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L12}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L13}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L13}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L14}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L14}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L15}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L15}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L16}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L16}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L17}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L17}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L18}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L18}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L19}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L19}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L20}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L20}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L21}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L21}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L22}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L22}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L23}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L23}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L24}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L24}`: 
- `#pragma ACCEL PIPELINE auto{__PIPE__L25}`: 
- `#pragma ACCEL TILE FACTOR=auto{__TILE__L25}`: 


#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 30; r++) {
    sum[r] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 0; p < 30; p++) {
        sum[p] += A[r][q][p];
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    for (p = 0; p < 30; p++) {
      C4[r][p] = sum[p];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    for (q = 0; q < 30; q++) {
      C4[r][q] += C4[r][s] * A[s][30][q];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  for (r = 0; r < 30; r++) {
    for (q = 0; q < 30; q++) {
      A[r][30][q] = C4[r][q];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L7}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L8}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
    for (q = 0; q < 20; q++) {
      A[q][r][30] = C4[r][q];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L