#include <stdint.h>

#include <thrust/device_vector.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/random.h>
#include <thrust/random/linear_congruential_engine.h>
#include <thrust/transform.h>

#include "fastrand.h"
#include "hash.h"

#define UNIF_SETTINGS thrust::tuple<const unsigned int, const flouble, const flouble>


struct parallel_random_uniform : public thrust::unary_function<thrust::tuple<const unsigned int, const flouble, const flouble>, flouble>
{
  thrust::tuple<const unsigned int, const flouble, const flouble> t;
  parallel_random_uniform(thrust::tuple<const unsigned int, const flouble, const flouble> _t) : t(_t) {}

  __host__ __device__
  flouble operator()(unsigned int threadIdx)
  {
    unsigned int seed = thrust_hash(threadIdx) * thrust::get<0>(t);
    
    thrust::default_random_engine rng(seed);
//    thrust::random::taus88 rng(seed);
    thrust::uniform_real_distribution<flouble> u01(thrust::get<1>(t), thrust::get<2>(t));
    
    return u01(rng);
  }
};



extern "C" SEXP R_fast_runif(SEXP n1_, SEXP n2_, SEXP min_, SEXP max_, SEXP seed_, SEXP nthreads)
{
  SEXP x;
  const int32_t n1 = INT(n1_);
  const int32_t n2 = INT(n2_);
  const R_xlen_t n = n1*n1 + n2;
  const flouble min = (flouble) REAL(min_)[0];
  const flouble max = (flouble) REAL(max_)[0];
  const unsigned int seed = INTEGER(seed_)[0];
  const int veclen = STRIDE < n ? STRIDE : n;
  
  const int top = (int) n/veclen;
  
  FASTRAND_GEN_NTHREADS(nthreads);
  
  PROTECT(x = allocVector(REALSXP, n));
  
  thrust::device_vector<flouble> vec(veclen);
  
  for (int i=0; i<((int) n/veclen); i++)
  {
    UNIF_SETTINGS t(seed+i, min, max);
    thrust::transform(THRUST_IT(0), THRUST_IT(veclen), vec.begin(), parallel_random_uniform(t));
    thrust::copy(vec.begin(), vec.end(), REAL(x) + i*STRIDE);
  }
  
  if (n-top > 0)
  {
    int rem = n - veclen*top;
    UNIF_SETTINGS t(seed+n/veclen, min, max);
    thrust::transform(THRUST_IT(0), THRUST_IT(rem), vec.begin(), parallel_random_uniform(t));
    thrust::copy(vec.begin(), vec.begin() + rem, REAL(x) + (n-rem));
  }
  
  UNPROTECT(1);
  return x;
}
