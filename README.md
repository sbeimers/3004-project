[![Contributors][contributors-shield1]][contributors-url1]
[![Contributors][contributors-shield3]][contributors-url3]
[![Contributors][contributors-shield2]][contributors-url2]
[![Contributors][contributors-shield4]][contributors-url4]


<p align="center">
  <h2 align="center">COMP 3004 Team Project (Winter 2023)</h2>
  <h3 align="center">Developing and Testing a Heart Wave Device Simulator</h3>
<br>

<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li><a href="#about-the-project">About the Project</a></li>
    <li>
      <a href="#team-members-contributions">Team Member Contributions</a>
      <ul>
        <li><a href="#sebastian-beimers">Sebastian Beimers</a></li>
        <li><a href="#zara-ali">Zara Ali</a></li>
        <li><a href="#elias-hawa">Elias Hawa</a></li>
         <li><a href="#victor-li">Victor Li</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#file-organization">File Organization</a></li>
  </ol>
</details>

## About The Project

This project was created by Sebastian Beimers, Elias Hawa, Zara Ali and Victor Li for Carleton University's COMP 3004 Winter 2023 course, taught by Vojislav Radonjic.

<a href="https://www.youtube.com/watch?v=c5LD6kXPK9Q">Click here</a> to view our project demo video.

## Team Members Contributions
For more information on the team members' contributions, please refer to the <a href="https://github.com/sbeimers/3004-project/pulls?page=1&q=is%3Apr+is%3Aclosed+">pull requests</a>.

### Sebastian Beimers
- Worked on initial system architecture design
- Created log class and related logic
- implemented restore feature
- added UI for battery
- created plot points for high coherence simulations
- created coherence data for all 3 simulations
- added battery ticking, battery recharging, and related logic 

### Zara Ali
- Worked on initial system architecture design 
- Created plot points for medium and low coherence simulations
- Implemented indicator functionality, including coherence and challenge level logic 
- Implemented functionality for device to update every 5 seconds (update functions in MainWindow, Device, and Recording)
- Implemented plot points, coherence, and achievement scores calculation in Recording class
- Implemented functionality for UI to update based on coherence, length of session, achievement score, and plot points during a session
- Implemented functionality for when the skin sensor is interrupted during an active session
- Created all sequence diagrams 

### Elias Hawa
- Worked on UI design and implementation including handling of device state and button handlers
- Worked on initial system architecture design 
- Implemented functionality for device to update every 5 seconds (update functions in MainWindow, Device, and Recording)
- Worked on log history and deletion functionality
- Worked on application to skin functionality

### Victor Li
- Worked on initial system architecture design 
- Implemented power button functionality, including power button logic and power button UI
- Implemented battery logic and battery UI functionality
- created all use cases and the use case diagrams
- created uml diagrams for the system architecture and the class diagram
- created the traceability matrix 
- created the README file

## Getting Started
To get a local copy of this project up and running, please follow the steps below.

### Prerequisites
<ol> 
  <li> Download the course VM <a href="https://carleton.ca/scs/tech-support/virtual-machines/">(COMP3004-F21.ova)</a> using this link <a href="https://carleton.ca/scs/tech-support/virtual-machines/">here</a>. Should the download not start as expected, please connect to the <a href="https://carleton.ca/its/help-centre/remote-access/">Carleton Remote Access VPN</a> and try again.

  <li> Setup a virtualization environment on your computer that allows you to run Virtual Machines. Click <a href="https://carleton.ca/scs/tech-support/virtual-machines/virtual-machine-technical-support/virtual-machine-step-by-step-guide/">here</a> for a <a href="https://carleton.ca/scs/tech-support/virtual-machines/virtual-machine-technical-support/virtual-machine-step-by-step-guide/">Virtual Machine Step-by-Step Guide</a>. More information can be found on the <a href="https://carleton.ca/scs/tech-support/virtual-machines/">SCS Virtual Machines page</a>.
</ol>

### Installation

1. Clone the repository by running this command in the course VM terminal:
   ```sh
   git clone git@github.com:sbeimers/3004-project.git
   ```
2. Start the COMP3004-F21 VM and enter the username "student" and the password "student".
3. Click on "Apps" at the bottom left corner, and then "Qt Creator (Community)".
4. Once Qt Creator is opened, click on File > Open File or Project... > heartwave > heartwave.pro > Open (bottom right of that window).
5. Once the project is opened, click on the green right arrow button at the bottom left corner to run the project simulator.
<br />

**Congratulations! You are now running our project on your VM!**
<br />

## File Organization
The project is organized as follows:
```
3004-project
├── README.md
├── Documentation
│   ├── Heartwave_Design_Patterns.pdf
│   ├── Heartwave_UML.pdf
│   ├── Heartwave_Use_Cases.pdf
│   ├── Heartwave_Traceability_Matrix.pdf
│   ├── Sequence Diagrams
│   │   ├── battery_low_diagram.pdf
│   │   ├── battery_settings_diagram.pdf
│   │   ├── interruption_of_signaldiagram.pdf
│   │   ├── normal_operation_session_diagram.pdf
│   │   ├── view_session_logs_diagram.pdf
├── heartwave
│   ├── heartwave.pro
│   ├── main.cpp
│   ├── mainwindow.cpp
│   ├── mainwindow.h
│   ├── mainwindow.ui
│   ├── const.h
│   ├── device.cpp
│   ├── device.h
│   ├── devicestate.h
│   ├── log.cpp
│   ├── log.h
│   ├── qcustomplot.cpp
│   ├── qcustomplot.h
│   ├── recording.cpp
│   ├── recording.h
```





<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield1]: https://img.shields.io/static/v1?label=Contributor&message=Sebastian_Beimers&color=afff75&style=for-the-badge
[contributors-url1]: https://github.com/sbeimers
[contributors-shield2]: https://img.shields.io/static/v1?label=Contributor&message=Zara_Ali&color=afff75&style=for-the-badge
[contributors-url2]: https://github.com/zaraahlie
[contributors-shield3]: https://img.shields.io/static/v1?label=Contributor&message=Elias_Hawa&color=afff75&style=for-the-badge
[contributors-url3]: https://github.com/EliasJRH
[contributors-shield4]: https://img.shields.io/static/v1?label=Contributor&message=Victor_Li&color=afff75&style=for-the-badge
[contributors-url4]: https://github.com/VictorLi5611
