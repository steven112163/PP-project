#!/bin/bash
ITERATION=${1:-100}
SURFACES=(400 800 1600 3200 6400)

{
  echo "Surface, Avg, Min, Max"
  for i in "${SURFACES[@]}"; do
    # Serial
    ./ripple_simulation -s "${i}" -i "${ITERATION}" -c
    # GPU
    ./ripple_simulation -s "${i}" -i "${ITERATION}" -g 1 -c
  done
} >"Reports/report_iter_${ITERATION}.txt"
