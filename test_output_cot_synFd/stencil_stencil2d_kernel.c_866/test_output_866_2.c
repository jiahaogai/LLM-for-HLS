#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int tk;
  int fi;
  int fj;
  int fk;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_l1:
/* Standardize from: for(i = 0; i < 128; i++) {...} */
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loop_l2:
/* Standardize from: for(j = 0; j < 64; j++) {...} */
    for (j = 0; j < 64; j++) {
      val = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_l3:
/* Standardize from: for(k = 0; k < 9; k++) {...} */
      for (k = 0; k < 9; k++) {
        ti = i - 4 + (k >> 2);
        tj = j - 2 + (k & 0x03);
        tk = k - 4;
        fi = filter[k];
        fj = filter[k];
        fk = filter[k];
        if (ti < 0 || 127 < ti || tj < 0 || 63 < tj || tk < 0 || 8 < tk) {
          val += fi * fj * fk * orig[0];
        }
         else {
          val += fi * fj * fk * orig[ti * 64 + tj];
        }
      }
      sol[i * 64 + j] = val;
    }
  }
}