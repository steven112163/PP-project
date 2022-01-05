#!/bin/bash
SURFACE=${1:-400}
ITERATION=${2:-100}
THREADS=(1 2 4 6 8)

{
  echo "Threads, Avg, Min, Max"
  # Serial
  ./ripple_simulation -s "${SURFACE}" -i "${ITERATION}" -c

  # OpenMP
  for i in "${THREADS[@]}"; do
    ./ripple_simulation -s "${SURFACE}" -i "${ITERATION}" -t "${i}" -c
  done
} >"Reports/report_${SURFACE}_${ITERATION}.txt"
