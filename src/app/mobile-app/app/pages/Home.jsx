import React from 'react';
import { StyleSheet, Text, View, Alert } from 'react-native';
import { Heading } from './components/TextItems';
import AiAssistant from './components/AiAssistant';
import { UtilButton } from './components/Utility';
import { clientSend } from './cli-util/client';


const quitCallback = () => {
    return (Alert.alert('Are You Sure?',
        'This will close down the server. Maybe you mean wait?',[
            {
                text: 'NO, CANCEL!!',
                style: 'cancel',
            },
            {
                text: 'YES, QUIT!',
                onPress: () => clientSend("quit"),
            },
        ]
    ));
};

const Home = (props) => {
    return (
        <View style={styles.container}>
            <Heading headingText="LIGHTS MOTHAFUCKER"/>
            <AiAssistant />
            <View style={styles.btnContainer}>
                <UtilButton 
                    btnText="Wait"
                    callback={() => clientSend("stop")}
                />
                <UtilButton
                    btnText="QUIT!"
                    btnColor='darkred'
                    callback={quitCallback}
                />
            </View>
        </View>
    );
};


export default Home;

const styles = StyleSheet.create({
    container: {
        flexDirection: 'column',
        backgroundColor: '#112',
        minHeight: '100%'
    },
    btnContainer: {
        flexDirection: 'row',
        justifyContent: 'space-evenly',
        marginBottom: 25,
    },
});
