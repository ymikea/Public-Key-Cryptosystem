
#include <inttypes.h>

uint64_t Randoms(uint64_t lower, uint64_t upper, uint64_t count);

uint64_t ModularArithmetic(uint64_t a, uint64_t b, uint64_t n);

uint64_t fastExponent(uint64_t a, uint64_t b, uint64_t n);

uint64_t ModulerExpo(uint64_t a, uint64_t b, uint64_t n);

bool witness(uint64_t a, uint64_t n);

bool MillerRabin(uint64_t n, uint64_t s);