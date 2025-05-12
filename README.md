# Handy: An Affordable Myoelectric Prosthetic Hand

Welcome to the official repository for **Handy**, an affordable myoelectric prosthetic hand designed for accessibility, modularity, and ease of assembly. This repository includes all the essential files and code necessary to build and control Handy, including hardware design files, embedded firmware, and a multimedia app interface.

---

## Repository Structure

```
Handy/
├── App/                # Android app source code for controlling Handy
├── Design Files/       # STL and CAD files for 3D printing Handy's mechanical parts
├── ESP32 Code/         # Firmware for the ESP32 microcontroller
├── Multimedia/         # Demo videos, project posters, and presentation materials
├── Images/             # Visual references and assembled prototype images
├── README.md           # Project overview and documentation
```

---

## Features

* **Affordable**: Designed using low-cost components and open-source tools.
* **Myoelectric Controlled**: Uses EMG signals to control prosthetic movement.
* **Wireless Interface**: ESP32-powered wireless control via a custom Android app.
* **Customizable Design**: STL files provided for 3D printing and customization.
* **Open-Source**: All design files, code, and documentation are freely available.

---

## Getting Started

### 1. Hardware Assembly

* 3D print components from the `Design Files/` directory.
* Follow the provided images in `Images/` for reference.
* Assemble the hand and integrate EMG sensors, servo motors, and ESP32.

### 2. Firmware Installation

* Flash the code from the `ESP32 Code/` directory to your ESP32 board.
* Make sure to configure the correct pins and WiFi credentials.

### 3. App Setup

* Clone the `App/` directory into Android Studio.
* Build and install the app on an Android phone.
* Connect the app to the ESP32 via WiFi.

---

## Multimedia

* Check the `Multimedia/` directory for:

  * Demo videos of Handy in action
  * Posters and presentations for exhibitions and competitions

---

## Contributing

Feel free to fork the repository and suggest improvements via pull requests. Whether it's hardware design, code optimization, or UI enhancements — your contributions are welcome!

---

## License

This project is licensed under the MIT License — see the `LICENSE` file for details.

---

## Contact

Created by [MrTG1B](https://github.com/MrTG1B). For questions or collaboration, please raise an issue or contact via GitHub.

---

Thank you for your interest in Handy — empowering lives with accessible technology!
