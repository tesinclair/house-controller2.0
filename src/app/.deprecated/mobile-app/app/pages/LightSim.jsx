import React from 'react';
import { View, StyleSheet } from 'react-native';
import TitleAiHeader from './components/TitleAiHeader';

const LightSim = (props) => {
    return (
        <View style={styles.container}>
            <TitleAiHeader headingText="LIGHTSIM MOTHERFUCKER" />
        </View>
    );
};

export default LightSim;

const styles = StyleSheet.create({
    container: {
        flexDirection: 'column',
        backgroundColor: '#112',
        minHeight: '100%'
    },
});
