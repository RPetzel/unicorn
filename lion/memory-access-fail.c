// cksystemsgroup.github.io/unicorn
// @SOLUTIONS = 256
// @UNROLL = 72

uint64_t main() {
  uint64_t* x;
  uint64_t* v;

  x = VERIFIER_nondet_uchar();

  // access code segment by reaching over data segment with _bump variable, no --check-block-access required

  v = x + -(4096 / 8) + -1;

  *v = *v;
  open(v, 32768, 0);
  read(0, v, 1);
  write(1, v, 1);

  // access memory right above 4GB, avoiding big integer in data segment, no --check-block-access required

  v = x + ((uint64_t*) (4 * 1024 * 1024 * 1024) - x);

  *v = *v;
  open(v, 32768, 0);
  read(0, v, 1);
  write(1, v, 1);

  // access word-unaligned address, no --check-block-access required

  v = (uint64_t*) ((uint64_t) x + 1);

  *v = *v;
  open(v, 32768, 0);
  read(0, v, 1);
  write(1, v, 1);

  // access memory right above memory block but well below 4GB, requires --check-block-access

  v = x + 1;

  *v = *v;
  open(v, 32768, 0);
  read(0, v, 1);
  write(1, v, 1);

  // unsafe access right above memory block even without pointer arithmetic
  read(0, x, 9);
  write(1, x, 9);

  // access memory right below memory block but still above code segment, due to _bump variable, requires --check-block-access

  v = x + -1;

  *v = *v;
  open(v, 32768, 0);
  read(0, v, 1);
  write(1, v, 1);

  return 0;
}
