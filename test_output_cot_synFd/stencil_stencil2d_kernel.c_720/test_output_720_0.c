#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{126}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 1; k < 33; k++) {
      i = (j - 1) * 32 + k - 1;
      val = ((orig[i] + orig[i + 1]) + orig[i + 32]) + orig[i + 33];
      val = val + ((orig[i + 32 + 1] + orig[i + 34]) + orig[i + 64]);
      val = val + ((orig[i + 64 + 1] + orig[i + 66]) + orig[i + 96]);
      val = val + ((orig[i + 96 + 1] + orig[i + 98]) + orig[i + 128]);
      val = val + ((orig[i + 128 + 1] + orig[i + 130]) + orig[i + 160]);
      val = val + ((orig[i + 160 + 1] + orig[i + 162]) + orig[i + 192]);
      val = val + ((orig[i + 192 + 1] + orig[i + 194]) + orig[i + 224]);
      val = val + ((orig[i + 224 + 1] + orig[i + 226]) + orig[i + 256]);
      val = val + ((orig[i + 256 + 1] + orig[i + 258]) + orig[i + 288]);
      val = val + ((orig[i + 288 + 1] + orig[i + 290]) + orig[i + 320]);
      val = val + ((orig[i + 320 + 1] + orig[i + 322]) + orig[i + 352]);
      val = val + ((orig[i + 352 + 1] + orig[i + 354]) + 128);
      sol[i] = val;
    }
  }
}