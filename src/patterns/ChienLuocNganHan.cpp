#include "ChienLuocNganHan.h"
#include <algorithm>
double ChienLuocNganHan::phanBoTien(double soTienDu, double soTienConThieu) {
    return std::min(soTienDu, soTienConThieu);   // tally hết, nhưng không tràn quá 100%
}