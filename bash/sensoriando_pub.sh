# Create a Payload for test
#!/bin/bash
source .env

MOSQUITTO_HOST=broker.sensoriando.com.br
THING_UUID=$1
SENSOR_ID=$2
VALUE=$3
VERBOSE=$4

PUB="mosquitto_pub -i "sensoriandoSDK" -h $MOSQUITTO_HOST -u $MOSQUITTO_USER -P $MOSQUITTO_PASSWORD -q $MOSQUITTO_QOS"

if [ -z "$THING_UUID" ]; then
    echo -e "Thing UUID required"
    exit 1
fi

if [ -z "$SENSOR_ID"  ]; then
    echo -e "Sensor ID required"
    exit 1
fi

if [ -z "$VALUE"  ]; then
    echo -e "Value is required"
    exit 1
fi

if [ -z "$VERBOSE"  ]; then
    VERBOSE=0
fi


DATE=$(date -u '+%Y%m%d%H%M%S')
PAYLOAD="{\"dt\": \"$DATE\", \"value\": $VALUE}"

TOPIC=$THING_UUID/$SENSOR_ID
TOPIC=$(echo $TOPIC | sed 's/ //g') #Remove whitespace

if [ $VERBOSE -eq 1 ]; then
    echo -e "Host:\t$MOSQUITTO_HOST"
    echo -e "Thing:\t$THING_UUID"
    echo -e "Sensor:\t$SENSOR_ID"
    echo -e "Topic:\t$TOPIC"
    echo -e "Payload:\t$PAYLOAD"
    echo -e "\n"
fi

if [ $MOSQUITTO_RETAINED -eq 1 ]; then
	$PUB -r -t $TOPIC -m "$PAYLOAD"
else
	$PUB -t $TOPIC -m "$PAYLOAD"
fi

exit 0

