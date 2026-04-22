# FlowTrip

India smart mobility platform built with React, Vite, Tailwind CSS, Framer Motion, Leaflet, OpenStreetMap, Nominatim, and OSRM.

## Features

- Reference-style FlowTrip landing page with animated route accents
- Journey planner with India-only location autocomplete via Nominatim
- Real Leaflet + OpenStreetMap map rendering
- Real OSRM route calls using `/route/v1/driving/{lon1},{lat1};{lon2},{lat2}`
- Sangli → Mumbai prefilled working case
- Multi-modal segment timeline: walk, auto, train, auto
- Cost, time, reliability, and CO₂ estimates

## Run

```bash
npm install
npm run dev
```

No API keys are required for the public Nominatim and OSRM endpoints used in this prototype.
