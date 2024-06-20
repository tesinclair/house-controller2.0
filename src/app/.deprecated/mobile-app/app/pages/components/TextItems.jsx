import React, {useEffect, useState} from 'react';
import { Text, StyleSheet } from 'react-native'

let headingSize;

const Heading = (props) => {
    const [headingSize, setHeadingSize] = useState(30);

    useEffect(() => {
        if (props.headingScale){
            setHeadingSize(props.headingScale * 30); 
        }
    }, [props.headingScale]);
    return (
        <Text style={[styles.heading, {fontSize: headingSize}]}>
            {props.headingText}
        </Text>
    );
};

const styles = StyleSheet.create({
    heading: {
        textAlign: 'center',
        color: '#ddd',
        fontWeight: 'bold',
        marginVertical: 30,
    },
});

export {
    Heading,
};
