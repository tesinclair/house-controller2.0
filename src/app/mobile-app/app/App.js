import { StyleSheet, StatusBar, View } from 'react-native';
import React from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createMaterialTopTabNavigator } from '@react-navigation/material-top-tabs';
import Home from './pages/Home';
import Custom from './pages/Custom';
import Presets from './pages/Presets';
import LightSim from './pages/LightSim';

const Tab = createMaterialTopTabNavigator();

export default function App() {
  return (
    <NavigationContainer> 
      <StatusBar hidden={false} />
      <Tab.Navigator 
        initialRouteName='Home'
        backBehavior='initialRoute'
      >
        <Tab.Screen
            name="Home"
            component={Home}
        />
        <Tab.Screen
            name="Custom"
            component={Custom}
        />
        <Tab.Screen
            name="Presets"
            component={Presets}
        />
        <Tab.Screen
            name="LightSim"
            component={LightSim}
        />
      </Tab.Navigator>
    </NavigationContainer>
  );
}

