# fastrand

* **Version:** 0.1-0
* **Status:** [![Build Status](https://travis-ci.org/wrathematics/fastrand.png)](https://travis-ci.org/wrathematics/fastrand)
* **License:** [BSD 2-Clause](http://opensource.org/licenses/BSD-2-Clause)
* **Author:** Drew Schmidt


Fast uniform and gaussian (normal) random number generation.  The package can be built to support a threaded backend via OpenMP or Intel Thread Building Blocks (TBB), as well as a GPU backend via NVIDIA's CUDA.  The package is particularly useful for generating very large vectors for testing numerical algorithms.

The quality of the random numbers is not as good as base R's.  But they are generated much more quickly, for a quasi performance-vs-accuracy tradeoff.



## Installation

<!-- To install the R package, run:

```r
install.package("fastrand")
``` -->

The development version is maintained on GitHub, and can easily be installed by any of the packages that offer installations from GitHub:

```r
### Pick your preference
devtools::install_github("wrathematics/fastrand")
ghit::install_github("wrathematics/fastrand")
remotes::install_github("wrathematics/fastrand")
```

By default, this will select an OpenMP backend.  For Linux and Mac, to build with the GPU backend, you might do something like this:

```bash
R CMD INSTALL fastrand/ --configure-args="--with-backend=CUDA --with-cuda-home=/path/to/cuda/"
```

For Windows, if you want to use the GPU backend, you will have to edit `fastrand/src/Makevars.win` appropriately.



## Package Use and Benchmarks

```r
n = 1e9
memuse::mu(n*8) # double precision size
## 7.451 GiB
memuse::mu(n*4) # single precision size
## 3.725 GiB

# warm ups
invisible(replicate(10, stats::rnorm(5)))
invisible(replicate(10, fastrand::rnorm(5)))

system.time(stats::rnorm(n))
##    user  system elapsed 
##  53.104   1.072  54.182

invisible(gc())

system.time(fastrand::rnorm(n, type="float"))
##    user  system elapsed 
## 118.104   0.432  32.947 
```

There are other benchmarks located in the `inst/benchmarks` subtree of the package source.