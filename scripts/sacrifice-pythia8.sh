#! /usr/bin/env -i bash --login

if [[ $# -lt 2 ]]; then
    echo "usage: sacrifice-pythia8.sh [configFileName] [outputFileName]"
    exit -1
fi

# need to find a better way for this
export HOME=~
export USER=`whoami`

SACRIFICE_VERSION=latest

SACRIFICE_CONFIG=$1
SACRIFICE_OUTPUT=$2
SACRIFICE_NEVENTS=$(printf "%.0f" 1.e9)
SACRIFICE_COMMAND="run-pythia -i $SACRIFICE_CONFIG -o $SACRIFICE_OUTPUT -n $SACRIFICE_NEVENTS"

# prepare environment
eval $(alienv printenv -q Sacrifice/$SACRIFICE_VERSION)

# print environment and run
printf '=%.0s' {1..80} && printf '\n'
alienv list
printf '=%.0s' {1..80} && printf '\n'
env
printf '=%.0s' {1..80} && printf '\n'
echo $SACRIFICE_COMMAND
printf '=%.0s' {1..80} && printf '\n'
$SACRIFICE_COMMAND
# rm $AGILE_OUTPUT
