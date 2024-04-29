#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int tk;
  int idx;
  int idy;
  int idz;
  int fl;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 8; j < 8184; j += 8) {
      inner:
      for (k = 8; k < 8184; k += 8) {
        idx = i - 8;
        idy = j - 8;
        idz = k - 8;
        fl = filter[0];
        sol[k + 8] = (orig[k + 8] + fl * (orig[idz + 8] + orig[idz + 16] + orig[idz + 24] + orig[idz + 32] + orig[idz + 40] + orig[idz + 48] + orig[idz + 56] + orig[idz + 64])) + ((fl += filter[1]) * (orig[idy + 8] + orig[idy + 16] + orig[idy + 24] + orig[idy + 32] + orig[idy + 40] + orig[idy + 48] + orig[idy + 56] + orig[idy + 64])) + ((fl += filter[2]) * (orig[idx + 8] + orig[idx + 16] + orig[idx + 24] + orig[idx + 32] + orig[idx + 40] + orig[idx + 48] + orig[idx + 56] + orig[idx + 64])) + ((fl += filter[3]) * (orig[idx + idy + 8] + orig[idx + idy + 16] + orig[idx + idy + 24] + orig[idx + idy + 32] + orig[idx + idy + 40] + orig[idx + idy + 48] + orig[idx + idy + 56] + orig[idx + idy + 64])) + ((fl += filter[4]) * (orig[idx + idz + 8] + orig[idx + idz + 16] + orig[idx + idz + 24] + orig[idx + idz + 32] + orig[idx + idz + 40] + orig[idx + idz + 48] + orig[idx + idz + 56] + orig[idx + idz + 64])) + ((fl += filter[5]) * (orig[idz + idy + 8] + orig[idz + idy + 16] + orig[idz + idy + 24] + orig[idz + idy + 32] + orig[idz + idy + 40] + orig[idz + idy + 48] + orig[idz + idy + 56] + orig[idz + idy + 64])) + ((fl += filter[6]) * (orig[idz + idx + 8] + orig[idz + idx + 16] + orig[idz + idx + 24] + orig[idz + idx + 32] + orig[idz + idx + 40] + orig[idz + idx + 48] + orig[idz + idx + 56] + orig[idz + idx + 64])) + ((fl += filter[7]) * (orig[idz + idy + idx + 8]));
      }
    }
  }
}