import React from 'react';
import { Text, View, StyleSheet } from 'react-native';
import TitleAiHeader from './components/TitleAiHeader';

const Custom = (props) => {
    return (
        <View style={styles.container}>
            <TitleAiHeader headingText="CUSTOM MOTHAFUCKER" />
        </View>
    );
};

export default Custom;

const styles = StyleSheet.create({
    container: {
        flexDirection: 'column',
        backgroundColor: '#112',
        minHeight: '100%'
    },
});
