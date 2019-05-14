#include "Bound.h"

Bound::Bound(): isSet(false), value(0.0) {
	
}

Bound::Bound(double value): isSet(true), value(value) {
	
}
