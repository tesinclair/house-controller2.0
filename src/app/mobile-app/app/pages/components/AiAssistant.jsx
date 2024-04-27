import React, { useState } from 'react';
import { StyleSheet, Text } from 'react-native';
import { Canvas } from '@react-three/fiber';

const AiAssistant = (props) => {
    const [talking, setTalking] = useState(false);
    const [interact, setInteract] = useState(false);

    return (
        <Canvas>
            <ambientLight />
            <mesh 
                {...props}
                onClick={(e) => {
                    setInteract(true);
                    setTimeout(() => setInteract(false), 200);
                }}
                scale={interact ? 1.5 : 1}
            >
                <sphereGeometry />
                <meshStandardMaterial color="#ddd" />
            </mesh>
        </Canvas>
    );
};

export default AiAssistant;
