Status: 

#pragma ACCEL kernel

void solver(long C0,long C1,long orig[297][40][80],long sol[297][40][80])
{
  long x;
  long y;
  long z;
  long t;
  long i;
  long j;
  long k;
  long d;
  long h;
  long idx;
  long idxm;
  long idxp;
  long idxt;
  long idxd;
  long idxu;
  long idxmz;
  long idxpz;
  long idxtz;
  long idxdp;
  long idxdm;
  long TMP1;
  long TMP2;
  long TMP3;
  long TMP4;
  long TMP5;
  long TMP6;
  long TMP7;
  long TMP8;
  long TMP9;
  long TMP10;
  long TMP11;
  long TMP12;
  long TMP13;
  long TMP14;
  long TMP15;
  long TMP16;
  long TMP17;
  long TMP18;
  long TMP19;
  long TMP20;
  long TMP21;
  long TMP22;
  long TMP23;
  long TMP24;
  long TMP25;
  long TMP26;
  long TMP27;
  long TMP28;
  long TMP29;
  long TMP30;
  long TMP31;
  long TMP32;
  long TMP33;
  long TMP34;
  long TMP35;
  long TMP36;
  long TMP37;
  long TMP38;
  long TMP39;
  long TMP40;
  long _in_C0_;
  long _in_C1_;
  long _in_orig_[80];
  long _out_sol_[80];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop:
/* Standardize from: for(t=0;t<80;t++) {...} */
  for (t = 0; t <= 79; t++) {
    1:
/* Standardize from: for(z=0;z<40;z++) {...} */
    for (z = 0; z <= 39; z++) {
      2:
/* Standardize from: for(y=0;y<40;y++) {...} */
      for (y = 0; y <= 39; y++) {
        3:
/* Standardize from: for(x=0;x<297;x++) {...} */
        for (x = 0; x <= 296; x++) {
          _in_C0_ = C0;
          _in_C1_ = C1;
          _in_orig_[0] = orig[x][y][z];
          _out_sol_[0] = _in_C0_ * _in_orig_[0];
/* Standardize from: for(d=1;d<80;d++) {...} */
          loop_d:
          for (d = 1; d <= 79; d++) {
            TMP1 = 1 * (d - 1);
            idx = x + TMP1;
            if (idx < 0 || 296 < idx) {
              idx = 0;
            }
            _out_sol_[d] = _in_C0_ * _in_orig_[d] + _in_C1_ * sol[idx][y][z];
          }
/* Standardize from: for(t=79;t>0;t--) {...} */
          loop_t:
          for (i = 79; i >= 1; i--) {
            TMP2 = 1 * (i - 1);
            idx = t + TMP2;