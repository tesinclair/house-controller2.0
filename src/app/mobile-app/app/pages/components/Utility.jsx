import React, { useState, useEffect }from 'react';
import { Pressable, Text, StyleSheet } from 'react-native';
import Slider from '@react-native-community/slider';

const UtilButton = (props) => {
    const [color, setColor] = useState('#333');

    useEffect(() => {
        if (props.btnColor){
            setColor(props.btnColor);
        }
    }, [props.btnColor]);

    return (

        <Pressable
            key={props.btnKey ? props.btnKey : null}
            style={[styles.button, {backgroundColor: color}]} 
            onPress={props.callback}
        >
            <Text style={styles.btnText}> {props.btnText} </Text>
        </Pressable>
    );
};

const UtilBrightnessScroller = (props) => {
    return (
        <Slider
            style={styles.brightnessScroller}
            minimumValue={0}
            maximumValue={100}
            minimumTrackTintColor="#555"
            maximimTrackTintColor="#333"
            lowerLimit={0}
            upperLimit={100}
            onValueChange={(brightness) => props.callback(brightness)}
            step={1}
            value={100}
        />
    );
};

export {
    UtilButton,
    UtilBrightnessScroller,
}

const styles = StyleSheet.create({
    button:{
        height: 40,
        width: 100,
        borderRadius: 10,
    },
    btnText: {
        fontSize: 15,
        color: '#ddd',
        textAlign: 'center',
        paddingTop: 10,
    },
    brightnessScroller: {
    },
});


