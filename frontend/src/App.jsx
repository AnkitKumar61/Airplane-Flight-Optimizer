import { useState, useEffect } from 'react';
import './index.css';
import MapView from './MapView';

function App() {
  const [start, setStart] = useState('JFK');
  const [end, setEnd] = useState('DXB');
  const [results, setResults] = useState(null);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState(null);
  
  const [airports, setAirports] = useState([]);
  const [routes, setRoutes] = useState([]);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const [airportsRes, routesRes] = await Promise.all([
          fetch('http://localhost:3000/api/airports'),
          fetch('http://localhost:3000/api/routes')
        ]);
        
        const airportsData = await airportsRes.json();
        const routesData = await routesRes.json();
        
        setAirports(airportsData);
        setRoutes(routesData);
      } catch (err) {
        console.error("Failed to fetch graph data", err);
      }
    };
    fetchData();
  }, []);

  const findShortestPath = async () => {
    setLoading(true);
    setError(null);
    setResults(null);

    try {
      const response = await fetch(`http://localhost:3000/api/flight?start=${start.toUpperCase()}&end=${end.toUpperCase()}`);
      const data = await response.json();

      if (!response.ok) {
        throw new Error(data.error || "Failed to find path");
      }

      setResults(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const PathDisplay = ({ pathArray }) => {
    return (
      <div className="flex flex-wrap gap-2 text-sm mt-2">
        {pathArray.map((airport, index) => (
          <span key={index} className="text-blue-300">
            {airport.code || airport}
            {index < pathArray.length - 1 && <span className="text-slate-500 mx-1">→</span>}
          </span>
        ))}
      </div>
    );
  };

  return (
    <div className="flex h-screen w-full bg-[#0b0f19] text-white font-sans overflow-hidden">
      
      {/* Left Sidebar (Controls & Results) */}
      <div className="w-[400px] flex-shrink-0 bg-[#111827] border-r border-slate-800 p-6 flex flex-col h-full overflow-y-auto">
        <h1 className="text-2xl font-bold tracking-tight mb-8">
          <span className="text-blue-500">Flight</span> Optimizer
        </h1>

        {/* Selection Box */}
        <div className="mb-8">
          <h2 className="text-xs font-bold text-slate-500 tracking-widest uppercase mb-4">Route Selection</h2>
          
          <div className="space-y-4">
            <div>
              <label className="block text-xs text-slate-400 mb-1">Start Airport</label>
              <select 
                value={start} 
                onChange={(e) => setStart(e.target.value)}
                className="w-full bg-[#1f2937] border border-slate-700 text-white rounded px-3 py-2 outline-none focus:border-blue-500 transition-colors"
              >
                {airports.map(a => (
                  <option key={a.code} value={a.code}>{a.city} ({a.code})</option>
                ))}
              </select>
            </div>
            
            <div>
              <label className="block text-xs text-slate-400 mb-1">Destination</label>
              <select 
                value={end} 
                onChange={(e) => setEnd(e.target.value)}
                className="w-full bg-[#1f2937] border border-slate-700 text-white rounded px-3 py-2 outline-none focus:border-blue-500 transition-colors"
              >
                {airports.map(a => (
                  <option key={a.code} value={a.code}>{a.city} ({a.code})</option>
                ))}
              </select>
            </div>

            <button 
              onClick={findShortestPath}
              disabled={loading || !start || !end}
              className="w-full mt-4 bg-blue-600 hover:bg-blue-500 disabled:bg-slate-700 text-white font-semibold py-3 rounded shadow-lg shadow-blue-900/20 transition-all"
            >
              {loading ? "Calculating..." : "Find Shortest Path"}
            </button>
          </div>
          
          {error && <div className="mt-4 text-red-400 text-sm">{error}</div>}
        </div>

        {/* Results Section */}
        {results && (
          <div className="flex-1 flex flex-col gap-6">
            <h2 className="text-xs font-bold text-slate-500 tracking-widest uppercase border-b border-slate-800 pb-2">Analysis Results</h2>
            
            {/* Dijkstra Result */}
            <div className="bg-[#1f2937] rounded-lg p-4 border border-slate-700">
              <h3 className="text-blue-400 font-bold mb-3">Dijkstra's Algorithm</h3>
              {results.dijkstra.found ? (
                <div className="space-y-2 text-sm">
                  <div className="flex justify-between">
                    <span className="text-slate-400">Total Distance:</span>
                    <span className="font-mono">{results.dijkstra.cost.toFixed(0)} km</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-slate-400">Airports Visited:</span>
                    <span className="font-mono">{results.dijkstra.visited}</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-slate-400">Execution Time:</span>
                    <span className="font-mono text-yellow-400">{results.dijkstra.timeMs} ms</span>
                  </div>
                  <div className="mt-3 pt-3 border-t border-slate-700">
                    <span className="text-xs text-slate-500">PATH:</span>
                    <PathDisplay pathArray={results.dijkstra.path} />
                  </div>
                </div>
              ) : (
                <p className="text-sm text-slate-400">No path found.</p>
              )}
            </div>

            {/* A* Result */}
            <div className="bg-[#1f2937] rounded-lg p-4 border border-emerald-900/50">
              <h3 className="text-emerald-400 font-bold mb-3">A* Algorithm</h3>
              {results.astar.found ? (
                <div className="space-y-2 text-sm">
                  <div className="flex justify-between">
                    <span className="text-slate-400">Total Distance:</span>
                    <span className="font-mono">{results.astar.cost.toFixed(0)} km</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-slate-400">Airports Visited:</span>
                    <span className="font-mono">{results.astar.visited}</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-slate-400">Execution Time:</span>
                    <span className="font-mono text-emerald-400">{results.astar.timeMs} ms</span>
                  </div>
                  <div className="mt-3 pt-3 border-t border-slate-700">
                    <span className="text-xs text-slate-500">PATH:</span>
                    <PathDisplay pathArray={results.astar.path} />
                  </div>
                </div>
              ) : (
                <p className="text-sm text-slate-400">No path found.</p>
              )}
            </div>

          </div>
        )}
        
        <div className="mt-auto pt-6 text-xs text-slate-600 text-center">
          Airport Route Visualizer
        </div>
      </div>

      {/* Right Map Canvas */}
      <div className="flex-1 relative">
        <MapView 
          airports={airports} 
          routes={routes} 
          shortestPath={results?.dijkstra?.found ? results.dijkstra.path : null}
        />
      </div>

    </div>
  );
}

export default App;
