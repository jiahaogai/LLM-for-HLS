**Requirements:**
 - ACCEL_SIZEOF_CHECK
 - ACCEL_MIN_CHECK
 - ACCEL_MAX_CHECK
 - ACCEL_POW_CHECK
 - ACCEL_LONG_DOUBLE_CHECK


**Parameters:**

  - `orig[8192]`: 
  - `sol[8192]`: 
  - `filter[9]`: 

**Structs:**

 @origin 

---

 @sol 

---

 @temp 

---

 @filter 

---


**Externals:**

  - ACCEL_SIZEOF_CHECK
  - ACCEL_MIN_CHECK
  - ACCEL_MAX_CHECK
  - ACCEL_POW_CHECK
  - ACCEL_LONG_DOUBLE_CHECK

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  int flatten_idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_orig:
/* Standardize from: for(i = 0; i < 32; i++) { */
  for (i = 0; i <= 31 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 0; j < 32; j++) { */
    for (j = 0; j <= 31 - 1; j++) {
      flatten_idx = i * 32 + j;
      s = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = -4; k < 5; k++) { */
      for (k = - 4; k <= 4 - 1; k++) {
        idx = flatten_idx + k;
        if (idx < 0) {
          idx = 0;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        if (idx > 8191) {
          idx = 8191;
        }
        s += ((double )filter[k + 4]) * orig[idx];
      }
      sol[flatten_idx] = s;
    }
  }
}