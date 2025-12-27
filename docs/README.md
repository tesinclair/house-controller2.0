# House Controller 2.0

## Project Description
This project aims to provide a comprehensive and modular smart home control system, "House Controller 2.0". It integrates various components for managing household devices, including GPIO-controlled elements and potentially AI-driven functionalities for enhanced automation.

## Features
-   **API for device control:** Python-based API for interacting with GPIO pins and other hardware.
-   **Socket communication:** Real-time communication capabilities for seamless interaction between components.
-   **Desktop Application:** A GTK-based desktop application for user interaction and control (based on `src/app`).
-   **Mobile Application (Deprecated):** Former mobile application components (found in `.deprecated/mobile-app`) are no longer actively maintained.
-   **Utility Libraries:** C-based utilities for various functionalities, including AI, client communication, error handling, lighting, and stack management.

## Setup
Detailed setup instructions for each component (API, Desktop App) will be provided in their respective directories or dedicated documentation files.

### API Setup
Simply create a python environment on a Raspberry Pi with `python3 -m venv venv`, then run `python3 main.py`.

### Desktop App Setup
Navigate to `src/app` run `sudo autogen.sh`. Input your ideal scrips location (default: `~/.houseleds/scripts`).
Wait for it to build, add the `house-controller` binary (inside `src/app/build`) to your PATH and run.

