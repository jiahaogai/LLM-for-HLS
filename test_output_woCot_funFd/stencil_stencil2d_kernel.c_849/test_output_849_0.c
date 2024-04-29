#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int idx;
  int idy;
  int fl;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 8; j < 8184; j += 8) {
      ti = i - 8;
      tj = j - 8;
      fl = filter[0];
      idx = ti * 64 + tj;
      idy = i * 64 + j;
      sol[idy] = orig[idx] * fl;
      fl = filter[1];
      idx += 64;
      sol[idy] += orig[idx] * fl;
      fl = filter[2];
      idx += 64;
      sol[idy] += orig[idx] * fl;
      fl = filter[3];
      idx += 64;
      sol[idy] += orig[idx] * fl;
      fl = filter[4];
      idx += 64;
      sol[idy] += orig[idx] * fl;
      fl = filter[5];
      idx += 64;
      sol[idy] += orig[idx] * fl;
      fl = filter[6];
      idx += 64;
      sol[idy] += orig[idx] * fl;
      fl = filter[7];
      idx += 64;
      sol[idy] += orig[idx] * fl;
      fl = filter[8];
      idx += 64;
      sol[idy] += orig[idx] * fl;
    }
  }
}