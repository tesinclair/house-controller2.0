import React, { useState, useRef } from 'react';
import { StyleSheet, Text } from 'react-native';
import { Canvas, useFrame } from '@react-three/fiber';
import { Object3D } from 'three';

const dummy = new Object3D();

const AssistantBubble = (props) => {
    const [talking, setTalking] = useState(false);

    const assistant = useRef();

    useFrame((state, delta) => {
        customDelta = 0.01*Math.cos(delta);
        assistant.current.rotation.x += customDelta;
        assistant.current.rotation.y += customDelta / 1.25;
    });

    return (
        <mesh
            {...props}
            ref={assistant} 
        >
            <icosahedronGeometry
                args={[2, 1]}
            />
            <meshStandardMaterial color="#ddd" wireframe/>
        </mesh>
    );
};

const AiAssistant = (props) => {


    return (
        <Canvas camera = {{position: [0, 5, 5]}}>
            <ambientLight args={[0xdddddd, .25]}/>
            <directionalLight position={[5, 5, 5]} />
            <AssistantBubble {...props} />
        </Canvas>
    );
};

export default AiAssistant;
