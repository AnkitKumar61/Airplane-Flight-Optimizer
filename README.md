<div align="center">
  <h1>🌍 Global Airplane Flight Optimizer</h1>
  <p><strong>A high-performance algorithmic visualizer simulating real-world global flight paths using C++ and React.</strong></p>

  [![React](https://img.shields.io/badge/Frontend-React_18-61DAFB?style=for-the-badge&logo=react&logoColor=black)]()
  [![Vite](https://img.shields.io/badge/Bundler-Vite_5-646CFF?style=for-the-badge&logo=vite&logoColor=white)]()
  [![TailwindCSS](https://img.shields.io/badge/Styling-Tailwind_CSS-38B2AC?style=for-the-badge&logo=tailwind-css&logoColor=white)]()
  [![Node.js](https://img.shields.io/badge/Backend-Node.js-339933?style=for-the-badge&logo=node.js&logoColor=white)]()
  [![C++](https://img.shields.io/badge/Engine-C++_17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)]()
  <br />
</div>

<br />

## 📖 Overview

The **Global Flight Optimizer** is a full-stack algorithmic engine built to find the shortest flight paths across the world's largest airports. Rather than using theoretical, randomly generated 2D grids, this project utilizes **real-world latitude and longitude datasets** and implements complex mathematical heuristics to calculate the curvature of the Earth.

The core pathfinding engine is written entirely from scratch in **C++** for maximum execution speed and memory management, while the frontend is built in **React** using a custom SVG mapping engine to visualize the algorithms mathematically.

---

## ✨ Core Features

- ⚡ **Dual Pathfinding Engine:** Implements both **Dijkstra's Algorithm** and the **A* (A-Star) Search Algorithm**.
- 🌍 **Geographical Heuristics:** The A* algorithm utilizes the mathematical **Haversine formula** to measure great-circle distances across the globe, allowing it to drastically outperform Dijkstra by searching directionally.
- ⏱️ **Microsecond Benchmarking:** Uses the native C++ `<chrono>` library to record and display the exact execution time of the algorithms in real-time.
- 🔌 **Cross-Language Interoperability:** A Node.js API acts as a bridge, dynamically spawning the compiled C++ binary via child processes and translating its stdout (JSON) to the frontend.
- 🎨 **Abstract Data Visualization:** The UI ditches standard map tiles for a pure CSS-grid "Control Room" aesthetic, utilizing `requestAnimationFrame` for buttery-smooth 60 FPS airplane interpolation.

---

## 🛠️ Architecture & Tech Stack

| Layer | Technology | Purpose |
| --- | --- | --- |
| **Frontend** | React, Vite, Tailwind | State management, UI controls, and dashboard styling. |
| **Visualizer** | React-Leaflet, SVG | Custom HTML nodes and dual-layered SVG paths for rendering the graph map. |
| **API** | Node.js, Express | Handles HTTP requests, reads static CSV data, and spawns C++ processes. |
| **Engine** | C++17 | Graph data structures, Priority Queues, Haversine math, and Algorithm execution. |

---

## 🔬 Algorithm Comparison

This project actively pits two of the most famous computer science algorithms against each other to prove the value of heuristic-driven search.

### 1. Dijkstra's Algorithm (The "Blind" Search)
Dijkstra explores the graph uniformly in all directions. Because it does not know the geographic location of the destination, it is forced to check many useless airports. It guarantees the shortest path, but at the cost of high time complexity.

### 2. A* Algorithm (The "Guided" Search)
A* is spatially aware. By using the Haversine formula (which calculates the physical distance between two GPS coordinates on a sphere) as its heuristic `h(n)`, A* actively avoids airports that move the plane in the wrong direction. It finds the exact same shortest path as Dijkstra but usually in a fraction of the time and by visiting significantly fewer nodes.

---

## 🚀 Getting Started

To run this project locally, you will need `Node.js` and a `C++ Compiler` (like `g++` via MinGW or GCC).

### 1. Compile the C++ Engine
Navigate to the root directory and compile the C++ source code into an executable.
```bash
# For Windows
g++ src/*.cpp -I include -o FlightOptimizer.exe

# For Mac/Linux
g++ src/*.cpp -I include -o FlightOptimizer
```

### 2. Start the Backend API
Navigate to the backend directory, install the dependencies, and start the Express server.
```bash
cd backend
npm install
node server.js
```

### 3. Start the Frontend Visualizer
Open a new terminal, navigate to the frontend directory, install dependencies, and start the Vite development server.
```bash
cd frontend
npm install
npm run dev
```

Visit `http://localhost:5173` in your browser to view the application.

---

## 📂 Project Structure

<details>
<summary>Click to view Directory Structure</summary>

```text
Airplane-Flight-Optimizer/
│
├── src/                     # C++ Source Code
│   ├── main.cpp             # Entry point & JSON formatter
│   ├── DijkstraOptimizer.cpp# Dijkstra's logic
│   ├── AStarOptimizer.cpp   # A* logic & Heuristics
│   ├── HaversineHelper.cpp  # Earth curvature math
│   └── Graph.cpp            # Adjacency List graph structure
│
├── include/                 # C++ Headers (.h files)
│
├── backend/                 # Node.js Server
│   └── server.js            # Express API & Child Process Spawner
│
├── frontend/                # React Dashboard
│   ├── src/
│   │   ├── App.jsx          # Sidebar & Results layout
│   │   ├── MapView.jsx      # Leaflet grid & Animated Plane logic
│   │   └── index.css        # Tailwind & custom SVG glows
│   └── package.json         # React Dependencies
│
└── data/                    # Real-world Dataset
    ├── airports.csv         # Global Hubs (Lat/Lng)
    └── routes.csv           # Flight Connections & Distances
```
</details>

---

<div align="center">
  <br/>
  <b>Engineered to demonstrate full-stack systems architecture and advanced algorithmic optimization.</b>
</div>
