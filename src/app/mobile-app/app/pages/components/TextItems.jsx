import React from 'react';
import { Text, StyleSheet } from 'react-native'

const Heading = (props) => {
    return (
        <Text style = {styles.heading}>
            {props.headingText}
        </Text>
    );
};

const styles = StyleSheet.create({
    heading: {
        textAlign: 'center',
        color: '#ddd',
        fontWeight: 'bold',
        fontSize: 30,
        marginVertical: 20,
    }
});

export {
    Heading
};
