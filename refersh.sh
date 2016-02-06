#!/bin/sh

SLEEP=2


FIXED_HOURLY_RATE=1000

START=$(date +%s)
git pull
sleep $SLEEP
END=$(date +%s)
DIFF=$(echo "$END - $START" | bc)
CURRENT_RATE=$(echo "3600/$DIFF"  | bc)

ACTION=""

if [ $CURRENT_RATE -ge $FIXED_HOURLY_RATE ]; then
	SLEEP_UPDATE=$(echo "$SLEEP+1" | bc);
	sed -i -e s/SLEEP=$SLEEP/SLEEP=$SLEEP_UPDATE/g refersh.sh
	ACTION="+1"
fi

if [ $CURRENT_RATE -lt $FIXED_HOURLY_RATE ]; then
	SLEEP_UPDATE=$(echo "$SLEEP-1" | bc);
	sed -i -e s/SLEEP=$SLEEP/SLEEP=$SLEEP_UPDATE/g refersh.sh
	ACTION="-1"
fi

echo "Current Requests Per Hour: $CURRENT_RATE, Sleep Time: $SLEEP, Action: $ACTION"

source refersh.sh
