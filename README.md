# Global Flight Optimizer ✈️

![Dashboard](https://img.shields.io/badge/UI-React_Dashboard-blue)
![Backend](https://img.shields.io/badge/Engine-C++17-green)
![Server](https://img.shields.io/badge/API-Node.js-orange)

A high-performance algorithmic visualizer that calculates the shortest flight paths across a global network of airports. This project was engineered from the ground up to demonstrate a deep understanding of core Computer Science fundamentals, systems architecture, and modern UI design.

## 🚀 Features

- **Custom C++ Pathfinding Engine:** Implements Dijkstra's Algorithm and A* (A-Star) Search from scratch to traverse a graph of real-world airport routes.
- **Geographic Heuristics:** The A* algorithm utilizes the mathematical **Haversine formula** to calculate the curvature of the Earth, transforming a "blind" search into a spatially-aware, highly optimized search.
- **Microsecond Benchmarking:** Uses the C++ `<chrono>` library to calculate the exact execution time of both algorithms, mathematically proving the efficiency gains of heuristic pathfinding.
- **Cross-Language Systems Architecture:** A Node.js / Express backend dynamically spawns the compiled C++ executable via child processes, passes user arguments, and parses standard output into JSON.
- **Abstract Data Visualization:** A custom React frontend built with Vite and TailwindCSS. Uses `react-leaflet` to render a stunning "Control Room" grid and `requestAnimationFrame` to render buttery-smooth, 60fps animations of the plane flying across the graph.

## 🧠 Why I Built This

I wanted to prove that I could take theoretical algorithms taught on whiteboards and engineer a full, production-ready system around them. Many visualizers use simple 2D grids and fake data. I challenged myself to manage C++ memory manually, handle inter-process communication with Node.js, parse real-world airline CSV data, and build a high-performance React rendering engine.

## 🛠️ Technology Stack

- **Core Engine:** C++17 (Graph Data Structures, Priority Queues, Haversine Math)
- **Backend API:** Node.js, Express
- **Frontend UI:** React, Vite, TailwindCSS, React-Leaflet
- **Data:** Real-world CSV datasets of Global Airports and Routes

## ⚙️ How to Run Locally

### 1. Compile the C++ Engine
Navigate to the root directory and compile the executable:
```bash
g++ src/*.cpp -I include -o FlightOptimizer.exe
```

### 2. Start the Node.js API
```bash
cd backend
npm install
node server.js
```

### 3. Start the React Frontend
```bash
cd frontend
npm install
npm run dev
```
