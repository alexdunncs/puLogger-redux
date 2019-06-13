#ifndef BOUND
#define BOUND

struct Bound {
  bool isSet;
  double value;

	Bound();
  Bound(double value);

  bool operator < (double other);
  bool operator > (double other);
  
};

#endif
