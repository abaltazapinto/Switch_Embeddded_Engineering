# Lecture Study Notes — IoT, Edge Computing and Cyber-Physical Systems (Embedded Systems)

## 1. Main Topic of the Lecture

The lecture introduces the **evolution of embedded systems toward IoT and Cyber-Physical Systems (CPS)**.
It explains how modern embedded systems are:

* **connected to networks**
* **data-driven**
* **distributed across cloud, edge and devices**
* **continuously updated**
* **subject to cybersecurity and scalability challenges**

This represents a transition from **isolated embedded devices → connected intelligent systems**.

---

# 1. Evolution of Embedded Systems

## 1.1 First Generation: Isolated Embedded Systems

### Characteristics

* Stand-alone **microcontrollers**
* Very limited **memory and processing power**
* No network connectivity
* Deterministic operation
* Software rarely updated

### Example

* Washing machine controller
* Industrial controller
* Early automotive ECUs

### Key Idea

Embedded systems were **closed systems** with fixed functionality.

---

## 1.2 Networked Embedded Systems

### Characteristics

* Devices connected through **networks**
* Distributed functionality
* Communication between multiple embedded nodes

### Problems Introduced

* **Distributed timing**
* **Synchronization**
* **Network latency**

### Example

Automotive networks:

* CAN
* LIN
* FlexRay

Multiple controllers cooperate to control the car.

---

## 1.3 Cloud-Connected Embedded Systems

Modern embedded systems now integrate:

* **IoT devices**
* **Edge computing**
* **Cloud processing**
* **AI**

### Architecture Layers

Typical architecture:

```
Sensors / Devices
        ↓
Edge Gateway
        ↓
Cloud Services
        ↓
Data Analytics / AI
```

### Example: Smart Washing Machine Monitoring

Sensors measure:

* vibration
* temperature
* usage patterns

Data is sent to:

* **Edge gateway**
* **Cloud analytics system**

Benefits:

* Predictive maintenance
* Remote monitoring
* Performance analysis

---

# 2. Edge Computing

## Definition

**Edge computing** performs **data processing close to the device**, instead of sending everything to the cloud.

### Why Edge Processing?

Sending all raw data to the cloud creates problems:

* latency
* bandwidth usage
* cost
* privacy

### Solution

Process data locally:

```
Sensor → Edge Processing → Cloud
```

Edge can perform:

* filtering
* local analytics
* AI inference
* decision making

---

## Example

Industrial machine monitoring:

Edge device analyzes vibration data.

If anomaly detected:

```
Edge → send alert to cloud
```

Instead of sending continuous raw data.

---

# 3. Multicore Embedded Systems

Modern embedded platforms contain:

* **Multiple CPU cores**
* **GPU**
* **NPU (AI accelerators)**

### Example

Even simple boards can have:

* **Dual-core microcontrollers**
* AI hardware accelerators

### Why Multicore?

To handle:

* networking
* AI inference
* control loops
* security
* user interfaces

### OS Complexity

Single-core OS:

```
Task scheduler → simple
```

Multi-core OS must handle:

* parallel execution
* synchronization
* shared resources

Much more complex.

---

# 4. Communication Protocols for IoT

Embedded systems often require **very lightweight communication**.

### Problem with Traditional Web Protocols

XML / REST can be **too heavy**.

Embedded devices need:

* low bandwidth
* small messages
* low power

---

## MQTT Protocol

### Key Idea

**Publish / Subscribe communication model**

Instead of direct communication.

### Architecture

```
Publisher → MQTT Broker → Subscribers
```

### Example

Temperature sensor:

```
Sensor publishes temperature → MQTT server
1000 devices subscribe to this data
```

### Advantages

* lightweight
* efficient
* scalable
* easy to implement on microcontrollers

### Technologies Mentioned

* MQTT
* Kafka
* REST APIs
* TCP/IP

---

# 5. Containers at the Edge

Edge devices can run **containers** (e.g., Docker).

### Benefits

* application isolation
* security
* easier updates
* multiple applications on same device

Example:

Edge device runs:

```
Container 1 → Data processing
Container 2 → AI inference
Container 3 → Monitoring
```

---

# 6. Over-the-Air Updates (OTA)

Modern embedded systems support **remote updates**.

### Old Method

Device had to be updated manually.

Example:

* take car to dealership

### Modern Method

Firmware update through internet.

```
Cloud → Vehicle → Firmware update
```

Example:

* Tesla OTA updates

### Challenges

* reliability
* safety
* cybersecurity

---

# 7. Cybersecurity in IoT

IoT devices are major **attack targets**.

### Why?

* millions of devices
* often poorly secured
* always connected

### Risks

* botnets
* data theft
* system manipulation
* infrastructure attacks

### Important Engineering Concern

Security must be built into:

* hardware
* firmware
* communication protocols

---

# 8. Cyber-Physical Systems (CPS)

## Definition

A **Cyber-Physical System** integrates:

* computation
* networking
* physical processes

The system **interacts with the physical world in real time**.

---

## Key Characteristic

**Feedback control loops**

Example:

```
Sensor → Controller → Actuator → Physical System
        ↑                       ↓
        ←-------- feedback -----
```

---

## Strong Timing Requirements

Many CPS require **real-time guarantees**.

Examples:

* aircraft control systems
* autonomous vehicles
* power grids
* medical devices

Timing failures can cause **catastrophic results**.

---

# 9. From Control Systems to Data-Driven Systems

Traditional embedded systems were:

```
Control-driven
```

Modern systems are:

```
Data-driven
```

They rely heavily on:

* large data collection
* analytics
* AI

Example:

Fleet management systems analyzing vehicle data.

---

# 10. System Evolution Trends

### Closed Systems → Open Systems

Old:

* fixed software
* no external interfaces

New:

* APIs
* integration with cloud services
* software updates

---

### Static Systems → Continuous Deployment

Old embedded systems:

* software unchanged for years

Modern systems:

* continuous updates
* new features deployed remotely

---

### Local Timing → Multi-Layer Timing

Timing now depends on multiple layers:

```
Device
Edge
Cloud
Network
```

Each introduces **latency and uncertainty**.

---

# 11. Data Governance

With connected devices collecting data, regulations are important.

Examples:

* **GDPR**
* EU data regulations

Concerns:

* data ownership
* privacy
* data access rights

---

# 12. Real-World Applications

### Automotive

* OTA updates
* autonomous vehicles
* fleet management

### Healthcare

Example:

Remote physiotherapy systems analyzing movement.

### Industrial IoT

Machine monitoring using vibration sensors.

### Smart Infrastructure

Power grids and energy monitoring.

---

# MIND MAP OF THE LECTURE

```
Embedded Systems Evolution
│
├── Isolated Embedded Systems
│   ├ limited memory
│   ├ microcontrollers
│   └ fixed functionality
│
├── Networked Systems
│   ├ distributed nodes
│   ├ synchronization
│   └ communication protocols
│
├── IoT Systems
│   ├ sensors
│   ├ gateways
│   └ cloud connectivity
│
├── Edge Computing
│   ├ local processing
│   ├ reduced latency
│   └ AI inference
│
├── Communication
│   ├ MQTT
│   ├ REST
│   ├ Kafka
│   └ TCP/IP
│
├── Multicore Embedded Platforms
│   ├ CPU cores
│   ├ GPU
│   └ AI accelerators
│
├── Cybersecurity
│   ├ attack surfaces
│   ├ secure updates
│   └ authentication
│
└── Cyber-Physical Systems
    ├ sensors
    ├ actuators
    ├ feedback loops
    └ real-time constraints
```

---

# One-Page Exam Cheat Sheet

### Embedded System Evolution

1. Isolated systems
2. Networked systems
3. Cloud-connected IoT systems

---

### Edge Computing

Processing data **near the device**.

Benefits:

* low latency
* lower bandwidth
* faster decisions

---

### MQTT

Publish / Subscribe model:

```
Publisher → Broker → Subscribers
```

Used because:

* lightweight
* efficient for embedded devices

---

### Multicore Embedded Systems

Modern platforms include:

* multicore CPUs
* GPU
* NPU

Challenge:

* synchronization
* parallel programming

---

### Cyber-Physical Systems

Integration of:

* computation
* networking
* physical processes

Key property:

**real-time feedback control loops**

Examples:

* aircraft
* autonomous vehicles
* medical devices
* power grids

---

### OTA Updates

Remote firmware updates via network.

Benefits:

* maintainability
* security patches

Risks:

* safety
* cybersecurity

---

# Typical Exam Traps

1️⃣ **Confusing IoT with CPS**

* IoT → connectivity
* CPS → real-time control of physical systems

---

2️⃣ **Thinking cloud replaces edge**

Wrong.

Edge **reduces latency and bandwidth**.

---

3️⃣ **Ignoring timing in distributed systems**

Cloud + edge introduces **non-deterministic delays**.

---

4️⃣ **Assuming embedded systems are simple**

Modern embedded systems can include:

* multicore processors
* GPUs
* AI accelerators
* Linux OS

---

# Possible Exam Questions

### Conceptual Questions

1. Explain the **difference between edge computing and cloud computing**.

2. Describe the **MQTT publish-subscribe communication model**.

3. What are **Cyber-Physical Systems** and why do they require real-time guarantees?

4. Why are **multicore processors increasingly common in embedded systems**?

5. Explain the challenges of **cybersecurity in IoT systems**.

---

### Architecture Question

Design a **smart industrial monitoring system** using:

* sensors
* edge device
* cloud analytics

Explain where processing should occur.

---

### Short Definition Questions

Define:

* IoT
* Edge computing
* MQTT
* Cyber-Physical System
* OTA update

---

# Oral Exam Questions (Professor Style)

1.

“Why is sending all sensor data directly to the cloud a bad design in many IoT systems?”

---

2.

“Explain the **publish–subscribe model** and why it is suitable for IoT.”

---

3.

“What new challenges appear when embedded systems become **networked and distributed**?”

---

4.

“Why are **real-time constraints critical** in cyber-physical systems?”

---

5.

“If you design an autonomous vehicle system, where would you place AI processing: **cloud or edge? Why?**”

---

# Final Lecture Summary

## Key Concepts

* IoT systems
* Edge computing
* Cloud-connected embedded systems
* Multicore embedded platforms
* Cyber-Physical Systems
* MQTT communication
* OTA updates
* Cybersecurity

---

## Key Terminology

* IoT
* Edge Computing
* MQTT
* Publish-Subscribe
* Cyber-Physical System (CPS)
* Multicore processors
* OTA (Over-the-Air update)
* Data Governance
* AI inference at the edge

---

## Typical Exam Traps

* Confusing **IoT vs CPS**
* Ignoring **latency and timing**
* Thinking **cloud replaces edge**
* Forgetting **security risks in IoT**

---

## Real-World Examples

* Tesla OTA vehicle updates
* Industrial vibration monitoring
* Remote medical rehabilitation systems
* Smart infrastructure monitoring

---

✅ If you want, I can also:

* Turn this lecture into a **visual diagram that makes CPS/IoT architecture very easy to remember for exams**, or
* Give you a **10-minute exam revision version** professors expect students to reproduce in answers.
