import React from 'react';
import { StyleSheet, Text, View } from 'react-native';
import { Heading } from './components/TextItems';
import AiAssistant from './components/AiAssistant';

const Home = (props) => {
    return (
        <View style={styles.container}>
            <Heading headingText="LIGHTS MOTHAFUCKER"/>
            <AiAssistant variation='FULLSCREEN' />
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
});
