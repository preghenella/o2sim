#! /usr/bin/env -i bash --login

if [[ $# -lt 2 ]]; then
    echo "usage: agile_pythia.sh [configFileName] [outputFileName]"
    exit -1
fi

# need to find a better way for this
export HOME=~
export USER=`whoami`

AGILE_VERSION=latest
PYTHIA6_VERSION=latest

AGILE_CONFIG=$1
AGILE_OUTPUT=$2
AGILE_NEVENTS=1.e9
AGILE_COMMAND="agile-runmc Pythia6:HEAD -P $AGILE_CONFIG -o $AGILE_OUTPUT -n $AGILE_NEVENTS"

# prepare environment
eval $(alienv printenv -q AGILe/$AGILE_VERSION pythia6/$PYTHIA6_VERSION)

# print environment and run
printf '=%.0s' {1..80} && printf '\n'
alienv list
printf '=%.0s' {1..80} && printf '\n'
env
printf '=%.0s' {1..80} && printf '\n'
echo $AGILE_COMMAND
printf '=%.0s' {1..80} && printf '\n'
$AGILE_COMMAND
rm $AGILE_OUTPUT
