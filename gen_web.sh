#!/bin/bash

emcmake cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -B build-web -S .
emmake cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 --build build-web