#! /bin/bash

#echo `dps`;
source ~/.bashrc

#dps
echo "[" $(docker ps --format "{{json .}}" | paste -sd, -) "]"
#echo "[" $(docker ps --format '{{json .}}' | jq -c '[.ID, .Names, .Image, .Ports, .State, .Status, .CreatedAt, .RunningFor]' | paste -sd, -) "]"
#echo "[" $(docker ps --format '{{json .}}' | jq -c '[.ID, .Names, .Image, .Ports, .State, .Status, .CreatedAt, .RunningFor]') "]"

