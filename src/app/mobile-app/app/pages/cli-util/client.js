import React from 'react';
import { Alert } from 'react-native';

const net = require("net");

function clientSend(data){
    const client = new net.Socket();

    client.connect(6767, "192.168.1.171", () => {
        client.write(data);
    });

    client.on('data', (data) => {
        if (data.toString() != "OK"){
            console.log(data.toString());
        }

        client.end();
    });

    client.on('close', () => {
        console.log('[CLIENT]: Server closed connection');
    });
}

export {
    clientSend,
}
