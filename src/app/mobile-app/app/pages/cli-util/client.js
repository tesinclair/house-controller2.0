import React from 'react';
import { Alert } from 'react-native';

function clientSend(data){
    url = 'http://192.168.1.171:6767/program?func=' + data;
    fetch(url)
        .then((response) => response.json())
        .then((json) => {
            if (json["status_code"] != 200){
                console.log(json);
                return (Alert.alert(
                    'Light Change Failed',
                    'Failed to change the lights: ' + json["detail"],
                    [
                        {
                            text: 'UNDERSTOOD'
                        },
                    ],
                    {
                        cancelable: true,
                    },
                ));
            }else {
                return true
            }
        }
    ).catch((e) => {
        console.disableYellowBox = true;
        console.error(e);
        throw e;
    });
}

function clientSetBrightness(data){
    url = 'http://192.168.1.171:6767/set?brightness=' + data;
    fetch(url)
        .then((response) => response.json())
        .then((json) => {
            if (json["status_code"] != 200){
                console.log(json);
                return (Alert.alert(
                    'Light Change Failed',
                    'Failed to change the lights: ' + json["detail"],
                    [
                        {
                            text: 'UNDERSTOOD'
                        },
                    ],
                    {
                        cancelable: true,
                    },
                ));
            }else {
                return true
            }
        }
    ).catch((e) => {
        console.disableYellowBox = true;
        console.error(e);
        throw e;
    });
}


export {
    clientSend,
    clientSetBrightness,
}
