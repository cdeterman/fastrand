% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/rnorm.r
\name{rnorm}
\alias{rnorm}
\title{rnorm}
\usage{
rnorm(n, mean = 0, sd = 1, seed = getseed(), nthreads = getnthreads())
}
\arguments{
\item{n}{The number of values to generate}

\item{mean, sd}{Parameters for normal random variables.}

\item{seed}{Seed for the random number generation.}

\item{nthreads}{An optional argument for specifying the number of threads
(in the case of OpenMP or TBB backends) that the routine should (at most)
use.  Does nothing with a CUDA backend.}
}
\description{
Generate from a normal distribution in parallel.
}
\references{
\url{https://thrust.github.io/doc/group__predefined__random.html}
}