import React from 'react';
import { Heading } from './TextItems';
import AiAssistant from './AiAssistant';
import { View, StyleSheet } from 'react-native';

const TitleAiHeader = (props) => {
    return (
        <View style={styles.titleaiContainer}>
            <Heading headingScale={.75} headingText={props.headingText} />
            <AiAssistant scale={1.5}/>
        </View>
    );
};

export default TitleAiHeader;

const styles = StyleSheet.create({
    titleaiContainer: {
        display: 'flex',
        flexDirection: 'row',
        marginHorizontal: 20,
    }
});
