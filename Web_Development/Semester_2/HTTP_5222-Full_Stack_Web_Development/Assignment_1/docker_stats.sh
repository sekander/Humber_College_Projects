#! /bin/bash

source ~/.bashrc

#dss
echo "[" $(docker stats --no-stream --format "{{json .}}" | paste -sd, -) "]"
