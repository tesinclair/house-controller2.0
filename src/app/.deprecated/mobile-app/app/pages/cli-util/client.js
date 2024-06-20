import TcpSocket from 'react-native-tcp-socket';

const options = {
    host: '192.168.1.171',
    port: 6767,
};

const cliSend = (data) => {
    const client = TcpSocket.createConnection(options, (err) => {
        if (err){
            console.error('Error connecting:', err);
            return;
        }
        
        client.write(data);

        client.on('data', (data) => {
            console.log('Recieved data: ', data.toString());
        });

        client.on('error', (error) => {
            console.error('Socket error:', error);
        });

        client.destroy();
    });
}

export default cliSend

