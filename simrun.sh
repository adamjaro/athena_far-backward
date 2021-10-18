#!/bin/bash

npsim\
  --enableGun --gun.direction "0 0 -1" \
  --gun.energy 8000 \
  --gun.particle e- \
  --compactFile athena_fb_only.xml \
  --random.seed 123 \
  --physics.list FTFP_BERT \
  --field.eps_min 5e-06 \
  --field.eps_max 1e-04 \
  --numberOfEvents 1\
  --outputFile out.root



#      --gun.energy 8000 \
#  --gun.energy 12500 \

