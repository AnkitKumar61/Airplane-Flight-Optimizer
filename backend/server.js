const express = require('express');
const cors = require('cors');
const { execFile } = require('child_process');
const path = require('path');
const fs = require('fs');

const app = express();
const PORT = 3000;

// Allow the React frontend to talk to this server
app.use(cors());

// NEW ENDPOINT: Get list of all available airports
app.get('/api/airports', (req, res) => {
    const csvPath = path.join(__dirname, '..', 'data', 'airports.csv');
    fs.readFile(csvPath, 'utf8', (err, data) => {
        if (err) return res.status(500).json({ error: "Failed to read airports data." });
        
        const airports = [];
        const lines = data.trim().split('\n');
        for (let line of lines) {
            const parts = line.split(',');
            if (parts.length >= 6) {
                // code, name, city, country, lat, lng
                airports.push({
                    code: parts[0],
                    name: parts[1],
                    city: parts[2],
                    country: parts[3],
                    lat: parts[4],
                    lng: parts[5]
                });
            }
        }
        res.json(airports);
    });
});

// NEW ENDPOINT: Get list of all flight routes (edges in our graph)
app.get('/api/routes', (req, res) => {
    const csvPath = path.join(__dirname, '..', 'data', 'routes.csv');
    fs.readFile(csvPath, 'utf8', (err, data) => {
        if (err) return res.status(500).json({ error: "Failed to read routes data." });
        
        const routes = [];
        const lines = data.trim().split('\n');
        for (let line of lines) {
            const parts = line.split(',');
            if (parts.length >= 3) {
                // from, to, distance
                routes.push({
                    from: parts[0],
                    to: parts[1],
                    distance: parts[2]
                });
            }
        }
        res.json(routes);
    });
});

// Define our API endpoint
app.get('/api/flight', (req, res) => {
    const startAirport = req.query.start;
    const endAirport = req.query.end;

    if (!startAirport || !endAirport) {
        return res.status(400).json({ error: "Please provide both start and end airports." });
    }

    // Path to your compiled C++ program
    const exePath = path.join(__dirname, '..', 'FlightOptimizer.exe');

    // Run the C++ program in the background
    execFile(exePath, [startAirport, endAirport], { cwd: path.join(__dirname, '..') }, (error, stdout, stderr) => {
        if (error) {
            console.error("Error executing C++ program:", error);
            return res.status(500).json({ error: "Failed to run optimization engine." });
        }

        try {
            // The C++ program prints raw JSON text. We convert it to a real JavaScript object.
            const resultData = JSON.parse(stdout);
            
            // Send the perfectly formatted answer back to React!
            res.json(resultData);
        } catch (parseError) {
            console.error("Failed to parse JSON from C++:", stdout);
            res.status(500).json({ error: "Engine returned invalid data format." });
        }
    });
});

app.listen(PORT, () => {
    console.log(`Node.js Bridge Server running at http://localhost:${PORT}`);
});
