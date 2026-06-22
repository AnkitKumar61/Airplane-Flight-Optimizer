import React, { useMemo, useEffect, useState } from 'react';
import { MapContainer, Polyline, Marker, Tooltip, useMap } from 'react-leaflet';
import 'leaflet/dist/leaflet.css';
import L from 'leaflet';

// Custom Airplane Node Icon
const createPlaneIcon = (isVisited) => {
  return L.divIcon({
    className: 'custom-div-icon',
    html: `
      <div style="position: relative;">
        <div class="airport-node" style="width: 30px; height: 30px; font-size: 16px;">
          ✈
        </div>
        ${isVisited ? '<div style="position: absolute; bottom: 0; right: -5px; width: 10px; height: 10px; background-color: #4ade80; border-radius: 50%; box-shadow: 0 0 5px #4ade80;"></div>' : ''}
      </div>
    `,
    iconSize: [30, 30],
    iconAnchor: [15, 15]
  });
};

const AutoFitMap = ({ airports }) => {
  const map = useMap();
  useEffect(() => {
    if (airports && airports.length > 0) {
      const validCoords = airports
        .filter(a => parseFloat(a.lat) !== 0)
        .map(a => [parseFloat(a.lat), parseFloat(a.lng)]);
      
      if (validCoords.length > 0) {
        const bounds = L.latLngBounds(validCoords);
        map.fitBounds(bounds, { padding: [80, 80] });
      }
    }
  }, [airports, map]);
  return null;
};

// Animated Plane Component
const AnimatedPlane = ({ path, onVisit }) => {
  const [pos, setPos] = useState(null);
  
  useEffect(() => {
    if (!path || path.length < 2) return;
    
    let isCancelled = false;
    let currentSegment = 0;
    
    const animateSegment = async () => {
      if (currentSegment >= path.length - 1) {
        if (!isCancelled) onVisit(path[currentSegment].code); // mark final destination as visited
        return;
      }
      
      const p1 = path[currentSegment];
      const p2 = path[currentSegment + 1];
      
      if (!isCancelled) onVisit(p1.code); // mark current node as visited
      
      // Pause for 1 second at intermediate airports (but not at the very start)
      if (currentSegment > 0) {
        await new Promise(r => setTimeout(r, 1000));
        if (isCancelled) return;
      }
      
      // Animate flight smoothly
      const duration = 1500; // 1.5 seconds per flight segment
      const startTime = performance.now();
      
      const step = (currentTime) => {
        if (isCancelled) return;
        const elapsed = currentTime - startTime;
        const progress = Math.min(elapsed / duration, 1);
        
        // Linear interpolation for lat/lng
        const currentLat = p1.lat + (p2.lat - p1.lat) * progress;
        const currentLng = p1.lng + (p2.lng - p1.lng) * progress;
        
        setPos([currentLat, currentLng]);
        
        if (progress < 1) {
          requestAnimationFrame(step);
        } else {
          currentSegment++;
          animateSegment();
        }
      };
      
      requestAnimationFrame(step);
    };
    
    animateSegment();
    
    return () => { isCancelled = true; };
  }, [path, onVisit]);
  
  if (!pos) return null;
  
  // Custom Icon for the animated moving plane (Blue and glowing)
  const movingPlaneIcon = L.divIcon({
    className: 'custom-div-icon',
    html: '<div style="font-size: 28px; filter: drop-shadow(0 0 10px #60a5fa); color: #60a5fa; transform: rotate(45deg);">✈</div>',
    iconSize: [28, 28],
    iconAnchor: [14, 14]
  });

  return <Marker position={pos} icon={movingPlaneIcon} zIndexOffset={1000} />;
};


const MapView = ({ airports = [], routes = [], shortestPath = null }) => {
  const center = [30, 10]; 
  const [visitedAirports, setVisitedAirports] = useState(new Set());

  // Reset visited airports when the shortest path changes
  useEffect(() => {
    setVisitedAirports(new Set());
  }, [shortestPath]);

  const handleVisit = React.useCallback((code) => {
    setVisitedAirports(prev => new Set(prev).add(code));
  }, []);

  const airportMap = useMemo(() => {
    const map = {};
    airports.forEach(a => {
      map[a.code] = { 
        lat: parseFloat(a.lat || 0), 
        lng: parseFloat(a.lng || 0), 
        name: a.name, 
        city: a.city,
        country: a.country,
        code: a.code
      };
    });
    return map;
  }, [airports]);

  const pathCodes = useMemo(() => {
    if (!shortestPath) return null;
    return shortestPath.map(node => String(typeof node === 'string' ? node : node.code).trim());
  }, [shortestPath]);

  const isPathEdge = (fromCode, toCode) => {
    if (!pathCodes) return false;
    const f = String(fromCode).trim();
    const t = String(toCode).trim();
    for (let i = 0; i < pathCodes.length - 1; i++) {
      const p1 = pathCodes[i];
      const p2 = pathCodes[i+1];
      if ((p1 === f && p2 === t) || (p1 === t && p2 === f)) {
        return true;
      }
    }
    return false;
  };

  return (
    <div className="w-full h-full relative z-0">
      <MapContainer 
        center={center} 
        zoom={2} 
        minZoom={2}
        worldCopyJump={true} 
        className="w-full h-full"
      >
        <AutoFitMap airports={airports} />

        {/* Draw Non-Glowing Routes First (Background) */}
        {routes.map((route, idx) => {
          const from = airportMap[route.from];
          const to = airportMap[route.to];
          if (!from || !to || from.lat === 0 || to.lat === 0) return null;
          if (isPathEdge(route.from, route.to)) return null; 

          return (
            <Polyline 
              key={`bg-${idx}`} 
              positions={[[from.lat, from.lng], [to.lat, to.lng]]} 
              color="#334155" 
              weight={1.5} 
              opacity={0.4} 
            >
              {route.distance && (
                <Tooltip permanent direction="center" className="distance-tooltip">
                  {route.distance} km
                </Tooltip>
              )}
            </Polyline>
          );
        })}

        {/* Draw Glowing Routes Last (Foreground) */}
        {routes.map((route, idx) => {
          const from = airportMap[route.from];
          const to = airportMap[route.to];
          if (!from || !to || from.lat === 0 || to.lat === 0) return null;
          if (!isPathEdge(route.from, route.to)) return null; 

          return (
            <React.Fragment key={`glow-${idx}-${pathCodes.join('-')}`}>
              {/* Outer Glow Layer */}
              <Polyline 
                positions={[[from.lat, from.lng], [to.lat, to.lng]]} 
                color="#60a5fa" 
                weight={10} 
                opacity={0.3} 
              />
              {/* Inner Solid Core */}
              <Polyline 
                positions={[[from.lat, from.lng], [to.lat, to.lng]]} 
                color="#2563eb" 
                weight={4} 
                opacity={1} 
              />
            </React.Fragment>
          );
        })}

        {/* Draw ALL Airports as custom Airplane Icons */}
        {airports.map((airport, idx) => {
          const a = airportMap[airport.code];
          if (!a || a.lat === 0) return null;

          // Now only true if the plane has physically visited this airport!
          const isVisited = visitedAirports.has(a.code);

          return (
            <Marker 
              key={idx} 
              position={[a.lat, a.lng]} 
              icon={createPlaneIcon(isVisited)}
            >
              <Tooltip direction="top" offset={[0, -15]} className="bg-slate-800 text-white border-none shadow-xl">
                <div className="text-center">
                  <div className="font-bold text-blue-400">{a.code}</div>
                  <div className="text-xs">{a.city}</div>
                </div>
              </Tooltip>
            </Marker>
          );
        })}

        {/* Draw the Moving Animated Plane */}
        {shortestPath && shortestPath.length > 1 && (
          <AnimatedPlane path={shortestPath} onVisit={handleVisit} />
        )}
      </MapContainer>
    </div>
  );
};

export default MapView;
