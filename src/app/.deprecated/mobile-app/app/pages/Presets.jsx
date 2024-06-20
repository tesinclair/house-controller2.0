import React, { useState } from 'react';
import { Text, View, StyleSheet, Pressable, Alert } from 'react-native';

// Look I'm making my own in C, give me a break...
import { TriangleColorPicker } from 'react-native-color-picker';

import { UtilButton, UtilBrightnessScroller } from './components/Utility';
import cliSend  from './cli-util/client';
import TitleAiHeader from './components/TitleAiHeader';

const Presets = (props) => {
    const [colorPickerColor, setColorPickerColor] = useState('white');
    const [brightness, setBrightness] = useState(1);

    const presetButtons = [
        {name: 'Night Light', data: 'nightLight', id: 1}, 
        {name: 'Collapse', data: 'collapse', id: 2}, 
        {name: 'Virgin Lights', data: 'virginLights', id: 3}, 
        {name: 'Flow', data: 'flow', id: 4}, 
        {name: 'Alternate', data: 'alternate', id: 5}, 
        {name: 'Pulse', data: 'pulse', id: 6},
    ]

    const colorButtons = [
        {name: 'Red', data: 'red', color: 'red', id: 1},
        {name: 'Green', data: 'green', color: 'green', id: 2},
        {name: 'Blue', data: 'blue', color: 'blue', id: 3},
        {name: 'White', data: 'light', color: 'white', id: 4},
    ]

    return (
        <View style={styles.container}>
            <TitleAiHeader headingText="PRESETS MOTHAFUCKER"/>
            <View style={styles.presetBtnContainer}>
                {presetButtons.map((btn) => (
                <UtilButton 
                    key={btn.id}
                    btnText={btn.name}
                    callback={() => cliSend("func:" + btn.data)} 
                />
                ))}
            </View>
            <View style={styles.colorBtnContainer}>
                {colorButtons.map((btn) => (
                <UtilButton 
                    key={btn.id}
                    btnText={btn.name}
                    btnColor={btn.color}
                    callback={() => cliSend("func:" + btn.data)} 
                />
                ))}
            </View>
            <View style={styles.colorSelectorContainer}>
                <TriangleColorPicker
                    hideControls={true}
                    oldColor={colorPickerColor}
                    color={colorPickerColor}
                    onColorChange={(color) => setColorPickerColor(color)}
                    style={styles.colorPicker}
                />
                <UtilButton
                    btnText="Set Color"
                    callback={() => cliSend('func:colorwheel,' + colorPickerColor)}
                />
            </View>
            <View style={styles.brightnessScrollerContainer}>
                <UtilBrightnessScroller 
                    callback={setBrightness}
                />
                <UtilButton
                    btnText="Set Brightness"
                    callback={() => cliSend('brightness:' + brightness)}
                />
            </View>
        </View>
    );
};

export default Presets

const styles = StyleSheet.create({
    container: {
        flexDirection: 'column',
        backgroundColor: '#112',
        minHeight: '100%',
    },
    presetBtnContainer: {
        flexDirection:'row',
        flexWrap: 'wrap',
        justifyContent: 'space-evenly',
        gap: 20,
        marginTop: 50,
        marginHorizontal: 25,
    },
    colorBtnContainer: {
        marginTop: 50,
        flexDirection: 'row',
        justifyContent: 'space-around',
    },
    colorSelectorContainer: {
        marginTop: 50,
        flexDirection: 'row',
        justifyContent: 'space-evenly',
        alignItems: 'center',
    },
    brightnessScrollerContainer: {
        marginTop: 50,
        flexDirection: 'column',
        gap: 20,
        alignItems: 'center',
    },
    colorPicker: {
        width: 150,
        height: 150
    }
});
