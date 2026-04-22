import { useCallback, useEffect, useMemo, useRef, useState } from "react";
import { motion } from "framer-motion";
import L from "leaflet";
import "leaflet/dist/leaflet.css";
import {
  ArrowRight,
  Bus,
  Car,
  CheckCircle2,
  Clock3,
  MessageCircle,
  IndianRupee,
  Layers3,
  Leaf,
  LocateFixed,
  MapPin,
  Navigation,
  RefreshCw,
  Route,
  Search,
  Send,
  ShieldCheck,
  Sparkles,
  Train,
  Wallet,
  X,
} from "lucide-react";
import { Button } from "@/components/ui/button";
import { supabase } from "@/integrations/supabase/client";
import trainImage from "@/assets/mumbai.jpg";

const INDIA_BOUNDS = [
  [6.4627, 68.1097],
  [35.5133, 97.3956],
];

const fallbackPlaces = [
  { label: "Sangli District, Maharashtra, India", lat: 16.8524, lon: 74.5815 },
  { label: "Mumbai, Maharashtra, India", lat: 19.076, lon: 72.8777 },
  { label: "Walchand College of Engineering, Sangli, Maharashtra, India", lat: 16.8450, lon: 74.6015 },
  { label: "Pune Institute of Technology, Pune, Maharashtra, India", lat: 18.4575, lon: 73.8508 },
  { label: "Andheri, Mumbai, Maharashtra, India", lat: 19.1197, lon: 72.8468 },
  { label: "Bandra, Mumbai, Maharashtra, India", lat: 19.0596, lon: 72.8295 },
  { label: "Pune Railway Station, Maharashtra, India", lat: 18.5289, lon: 73.8744 },
  { label: "Lonavala, Maharashtra, India", lat: 18.7546, lon: 73.4062 },
];

const markerIcon = new L.DivIcon({
  className: "flow-marker",
  html: '<span></span>',
  iconSize: [24, 24],
  iconAnchor: [12, 12],
});

const modeMeta = {
  walk: { icon: LocateFixed, label: "Walk", className: "bg-walk text-success-foreground", color: "hsl(var(--walk))", glyph: "🚶" },
  auto: { icon: Car, label: "Auto", className: "bg-auto text-accent-foreground", color: "hsl(var(--auto))", glyph: "🛺" },
  train: { icon: Train, label: "Train", className: "bg-rail text-accent-foreground", color: "hsl(var(--rail))", glyph: "🚆" },
  bus: { icon: Bus, label: "Bus", className: "bg-bus text-accent-foreground", color: "hsl(var(--bus))", glyph: "🚌" },
};

const navItems = ["Problem", "Features", "Journey Planner", "How It Works"];

function useDebouncedPlaces(query) {
  const [places, setPlaces] = useState([]);
  const [loading, setLoading] = useState(false);

  useEffect(() => {
    if (query.trim().length < 3) {
      setPlaces([]);
      return;
    }

    const controller = new AbortController();
    const id = window.setTimeout(async () => {
      setLoading(true);
      try {
        const params = new URLSearchParams({
          q: `${query}, India`,
          format: "jsonv2",
          addressdetails: "1",
          limit: "5",
          countrycodes: "in",
          viewbox: "68.1097,35.5133,97.3956,6.4627",
          bounded: "1",
        });
        const response = await fetch(`https://nominatim.openstreetmap.org/search?${params.toString()}`, {
          signal: controller.signal,
        });
        const data = (await response.json());
        setPlaces(
          data.map((item) => ({
            label: item.display_name,
            lat: Number(item.lat),
            lon: Number(item.lon),
          })),
        );
      } catch (error) {
        if (!controller.signal.aborted) setPlaces(fallbackPlaces.filter((place) => place.label.toLowerCase().includes(query.toLowerCase())));
      } finally {
        if (!controller.signal.aborted) setLoading(false);
      }
    }, 350);

    return () => {
      window.clearTimeout(id);
      controller.abort();
    };
  }, [query]);

  return { places, loading };
}

function PlaceInput({ label, value, onChange, onSelect }) {
  const { places, loading } = useDebouncedPlaces(value);

  return (
    <div className="relative space-y-2">
      <label className="font-display text-[0.65rem] font-bold uppercase tracking-[0.42em] text-muted-foreground">{label}</label>
      <div className="flex items-center gap-3 border-2 border-border bg-card px-4 py-3">
        <MapPin className="size-4 shrink-0" />
        <input
          value={value}
          onChange={(event) => onChange(event.target.value)}
          placeholder={`${label} in India`}
          className="w-full bg-transparent text-sm font-medium outline-none placeholder:text-muted-foreground"
        />
        {loading ? <RefreshCw className="size-4 animate-spin" /> : <Search className="size-4" />}
      </div>
      {places.length > 0 && (
        <div className="absolute z-30 max-h-56 w-full overflow-auto border-2 border-border bg-popover shadow-hard">
          {places.map((place) => (
            <button
              key={`${place.lat}-${place.lon}-${place.label}`}
              type="button"
              onClick={() => onSelect(place)}
              className="block w-full border-b border-border px-4 py-3 text-left text-sm transition-colors last:border-b-0 hover:bg-secondary focus:bg-secondary focus:outline-none"
            >
              {place.label}
            </button>
          ))}
        </div>
      )}
    </div>
  );
}

function FlowBot({ onPlanClick }) {
  const [open, setOpen] = useState(false);
  const [input, setInput] = useState("");
  const [loading, setLoading] = useState(false);
  const [messages, setMessages] = useState([
    { role: "assistant", content: "Hola !!, I'm FlowBot. Ask me about fares, fastest routes, bus-train mixes" },
  ]);

  const sendMessage = async () => {
    const text = input.trim();
    if (!text || loading) return;
    const nextMessages = [...messages, { role: "user", content: text }];
    setMessages(nextMessages);
    setInput("");
    setLoading(true);

    const { data, error } = await supabase.functions.invoke("flowbot", { body: { messages: nextMessages } });
    const botReply = data?.reply ? data.reply.replace(/[*#]/g, "").trim() : null;
    setMessages((current) => [
      ...current,
      { role: "assistant", content: error ? "FlowBot is warming up. Please try again later." : botReply ?? "I can help plan your FlowTrip route." },
    ]);
    setLoading(false);
  };

  return (
    <div className="fixed bottom-6 right-6 z-50 flex max-w-[calc(100vw-3rem)] flex-col items-end gap-4">
      {open && (
        <motion.section 
          initial={{ opacity: 0, y: 22, scale: 0.96 }} 
          animate={{ opacity: 1, y: 0, scale: 1 }} 
          className="w-[520px] max-w-full overflow-hidden border-[3px] border-black bg-[#f4f5f5] shadow-[6px_6px_0_0_#000]"
        >
          <div className="flex items-stretch border-b-[3px] border-black bg-[#111]">
            <div className="flex w-24 items-center justify-center bg-[#ffe01b] border-r-[3px] border-black text-black">
              <Sparkles className="size-10" />
            </div>
            <div className="flex flex-1 items-center justify-between p-5 text-white">
              <div>
                <div className="font-display text-2xl font-black tracking-wide">FlowBot</div>
                <div className="font-display text-[0.65rem] font-bold uppercase tracking-[0.3em] text-zinc-400">India mobility AI</div>
              </div>
              <button onClick={() => setOpen(false)} className="grid size-12 place-items-center border border-zinc-700 transition-colors hover:bg-zinc-800">
                <X className="size-6" />
              </button>
            </div>
          </div>
          <div className="h-[400px] space-y-5 overflow-y-auto p-6">
            {messages.map((message, index) => (
              <div 
                key={`${message.role}-${index}`} 
                className={`max-w-[88%] whitespace-pre-wrap border-[3px] border-black p-5 text-base font-medium leading-relaxed ${message.role === "user" ? "ml-auto bg-[#ffe01b] text-black" : "bg-white text-black"}`}
              >
                {message.content}
              </div>
            ))}
            {loading && (
              <div className="inline-flex items-center gap-3 border-[3px] border-black bg-white p-5 text-base font-bold text-black">
                <RefreshCw className="size-5 animate-spin" /> Thinking route logic…
              </div>
            )}
          </div>
          <div className="border-t-[3px] border-black bg-white p-6">
            <div className="mb-5 flex flex-wrap gap-2">
              {["Cheapest route?", "Sangli to Mumbai", "Low CO₂"].map((item) => (
                <button 
                  key={item} 
                  onClick={() => setInput(item)} 
                  className="border-[2px] border-black bg-white px-4 py-2 font-display text-[0.65rem] font-bold uppercase tracking-[0.18em] text-black transition-colors hover:bg-zinc-100"
                >
                  {item}
                </button>
              ))}
            </div>
            <div className="flex items-stretch gap-3">
              <input 
                value={input} 
                onChange={(event) => setInput(event.target.value)} 
                onKeyDown={(event) => event.key === "Enter" && sendMessage()} 
                placeholder="Ask FlowBot…" 
                className="min-w-0 flex-1 border-[3px] border-black bg-[#f4f5f5] px-5 py-4 text-base font-bold text-black outline-none placeholder:text-zinc-500 focus:bg-white" 
              />
              <button 
                onClick={sendMessage} 
                disabled={loading} 
                className="grid w-16 place-items-center border-[3px] border-black bg-[#111] text-white transition-transform active:translate-y-1 disabled:opacity-70"
              >
                <Send className="size-6" />
              </button>
            </div>
            <button 
              onClick={onPlanClick} 
              className="mt-5 w-full border-[3px] border-black bg-[#e5e7eb] px-5 py-4 font-display text-[0.75rem] font-bold uppercase tracking-[0.28em] text-black transition-colors hover:bg-[#d1d5db]"
            >
              Open planner
            </button>
          </div>
        </motion.section>
      )}
      <motion.button 
        whileHover={{ y: -4 }} 
        whileTap={{ scale: 0.96 }} 
        onClick={() => setOpen((value) => !value)} 
        className="flex items-center gap-3 border-[3px] border-black bg-[#ffe01b] px-6 py-4 font-display text-lg font-black text-black shadow-[6px_6px_0_0_#000] transition-shadow hover:shadow-[4px_4px_0_0_#000]"
      >
        <MessageCircle className="size-6" /> FlowBot
      </motion.button>
    </div>
  );
}

function buildSegments(distanceKm, durationMin, type) {
  const firstMile = Math.min(3.6, Math.max(1.2, distanceKm * 0.02));
  const lastMile = Math.min(7.2, Math.max(2.4, distanceKm * 0.035));
  const mainKm = Math.max(distanceKm - firstMile - lastMile, distanceKm * 0.82);
  const trainMin = Math.max(45, Math.round(durationMin * (type === "fastest" ? 0.62 : type === "cheapest" ? 0.78 : 0.7)));
  const busMin = Math.max(38, Math.round(durationMin * (type === "cheapest" ? 0.28 : 0.18)));
  const autoMin = Math.max(14, Math.round(durationMin * 0.08));
  const walkMin = Math.max(12, Math.round(firstMile * 12));

  if (type === "cheapest") {
    return [
      { mode: "walk", title: "Start → bus stand", detail: "Low-cost walk link", minutes: walkMin + 6, distanceKm: firstMile, cost: 0 },
      { mode: "bus", title: "State highway bus", detail: "Budget MSRTC corridor", minutes: busMin, distanceKm: mainKm * 0.72, cost: Math.round(mainKm * 0.7) },
      { mode: "train", title: "Suburban rail transfer", detail: "Mumbai local connector", minutes: trainMin, distanceKm: mainKm * 0.28, cost: Math.round(mainKm * 0.45) },
      { mode: "walk", title: "Station → destination", detail: "Final walking link", minutes: Math.max(18, Math.round(lastMile * 13)), distanceKm: lastMile, cost: 0 },
    ];
  }

  if (type === "balanced") {
    return [
      { mode: "walk", title: "Start → pickup", detail: "Short first mile", minutes: walkMin, distanceKm: firstMile, cost: 0 },
      { mode: "auto", title: "Pickup → rail hub", detail: "Reliable auto-rickshaw", minutes: autoMin, distanceKm: lastMile, cost: Math.round(lastMile * 18) },
      { mode: "train", title: "Express rail corridor", detail: "Best time-cost balance", minutes: trainMin, distanceKm: mainKm * 0.82, cost: Math.round(mainKm * 1.05) },
      { mode: "bus", title: "City bus connector", detail: "BEST city transfer", minutes: Math.max(24, Math.round(durationMin * 0.08)), distanceKm: mainKm * 0.08, cost: 35 },
      { mode: "walk", title: "Stop → destination", detail: "Final walk", minutes: Math.max(10, Math.round(lastMile * 8)), distanceKm: Math.min(2.4, lastMile), cost: 0 },
    ];
  }

  return [
    { mode: "auto", title: "Doorstep → rail hub", detail: "Fast auto-rickshaw pickup", minutes: autoMin + 8, distanceKm: lastMile, cost: Math.round(lastMile * 24) },
    { mode: "train", title: "Fastest rail corridor", detail: "Express train priority", minutes: trainMin, distanceKm: mainKm, cost: Math.round(mainKm * 1.45) },
    { mode: "auto", title: "Mumbai pickup → destination", detail: "Quick on-demand auto", minutes: Math.max(16, Math.round(durationMin * 0.06)), distanceKm: Math.min(8, lastMile), cost: Math.round(Math.min(8, lastMile) * 28) },
  ];
}

function buildRouteOptions(distanceKm, durationMin, geometry) {
  return (["fastest", "cheapest", "balanced"]).map((id) => {
    const segments = buildSegments(distanceKm, durationMin, id);
    const cost = segments.reduce((sum, segment) => sum + segment.cost, 0);
    const timeFactor = id === "fastest" ? 0.84 : id === "cheapest" ? 1.18 : 1;
    const costFactor = id === "fastest" ? 1.18 : id === "cheapest" ? 0.74 : 0.94;
    return {
      id,
      name: id === "fastest" ? "Fastest" : id === "cheapest" ? "Cheapest" : "Balanced",
      badge: id === "fastest" ? "Save time" : id === "cheapest" ? "Lowest fare" : "Best overall",
      distanceKm: distanceKm * (id === "cheapest" ? 1.04 : id === "balanced" ? 1.01 : 1),
      durationMin: durationMin * timeFactor,
      geometry,
      segments: segments.map((segment) => ({ ...segment, cost: Math.round(segment.cost * costFactor) })),
      cost: Math.round(cost * costFactor),
      reliability: id === "balanced" ? 94 : id === "fastest" ? 88 : 82,
      co2: Math.round(distanceKm * (id === "cheapest" ? 15 : id === "balanced" ? 18 : 24)),
    };
  });
}

function sliceLine(line, index, total) {
  if (line.length < 2) return line;
  const start = Math.floor((index / total) * (line.length - 1));
  const end = Math.max(start + 2, Math.floor(((index + 1) / total) * (line.length - 1)) + 1);
  return line.slice(start, Math.min(end, line.length));
}

function modeIcon(mode) {
  const meta = modeMeta[mode];
  return new L.DivIcon({
    className: "flow-mode-marker",
    html: `<span style="background:${meta.color}">${meta.glyph}</span>`,
    iconSize: [34, 34],
    iconAnchor: [17, 17],
  });
}

function AppMap({ route, from, to }) {
  const containerRef = useRef(null);
  const mapRef = useRef(null);
  const layerRef = useRef(null);
  const line = route?.geometry ?? [];
  const points = line.length ? line : [from, to].filter(Boolean).map((place) => [place.lat, place.lon]);

  useEffect(() => {
    if (!containerRef.current || mapRef.current) return;

    const map = L.map(containerRef.current, { scrollWheelZoom: true }).setView([19.4, 74.1], 6);
    L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png", {
      attribution: "&copy; OpenStreetMap contributors",
    }).addTo(map);
    const layer = L.layerGroup().addTo(map);
    mapRef.current = map;
    layerRef.current = layer;

    return () => {
      map.remove();
      mapRef.current = null;
      layerRef.current = null;
    };
  }, []);

  useEffect(() => {
    const map = mapRef.current;
    const layer = layerRef.current;
    if (!map || !layer) return;

    layer.clearLayers();
    if (from) L.marker([from.lat, from.lon], { icon: markerIcon }).addTo(layer);
    if (to) L.marker([to.lat, to.lon], { icon: markerIcon }).addTo(layer);
    if (route && line.length > 0) {
      route.segments.forEach((segment, index) => {
        const segmentLine = sliceLine(line, index, route.segments.length);
        if (segmentLine.length > 1) {
          L.polyline(segmentLine, { color: modeMeta[segment.mode].color, weight: 7, opacity: 0.92 }).addTo(layer);
          L.marker(segmentLine[Math.floor(segmentLine.length / 2)], { icon: modeIcon(segment.mode) }).addTo(layer);
        }
      });
    }
    if (points.length > 1) map.fitBounds(L.latLngBounds(points), { padding: [34, 34], maxZoom: 9 });
    else map.setView([19.4, 74.1], 6);
  }, [from, line, points, route, to]);

  return <div ref={containerRef} className="h-[360px] w-full border-2 border-border md:h-[430px]" />;
}

const Index = () => {
  const [fromQuery, setFromQuery] = useState(fallbackPlaces[0].label);
  const [toQuery, setToQuery] = useState(fallbackPlaces[1].label);
  const [from, setFrom] = useState(fallbackPlaces[0]);
  const [to, setTo] = useState(fallbackPlaces[1]);
  const [departure, setDeparture] = useState("now");
  const [route, setRoute] = useState(null);
  const [routeOptions, setRouteOptions] = useState([]);
  const [status, setStatus] = useState("Ready for India-only routing");
  const [isPlanning, setIsPlanning] = useState(false);
  const plannerRef = useRef(null);

  const totalDistance = route?.distanceKm ?? 356.4;
  const routeSummary = useMemo(
    () => [
      { label: "Journeys planned", value: "47M+" },
      { label: "Uptime SLA", value: "99.9%" },
      { label: "Route latency", value: "<280ms" },
    ],
    [],
  );

  const planRoute = useCallback(async () => {
    if (!from || !to) {
      setStatus("Choose valid Indian start and destination points");
      return;
    }

    setIsPlanning(true);
    setStatus("Computing OSRM route");
    try {
      const response = await fetch(
        `https://router.project-osrm.org/route/v1/driving/${from.lon},${from.lat};${to.lon},${to.lat}?overview=full&geometries=geojson`,
      );
      const data = await response.json();
      if (!data.routes?.[0]) throw new Error("No route returned");
      const osrmRoute = data.routes[0];
      const distanceKm = osrmRoute.distance / 1000;
      const durationMin = osrmRoute.duration / 60;
      const geometry = osrmRoute.geometry.coordinates.map(([lon, lat]) => [lat, lon]);
      const options = buildRouteOptions(distanceKm, durationMin, geometry);
      setRouteOptions(options);
      setRoute(options[0]);
      setStatus("3 smart route options ready");
    } catch (error) {
      setStatus("OSRM could not compute this Indian route right now");
      setRoute(null);
      setRouteOptions([]);
    } finally {
      setIsPlanning(false);
    }
  }, [from, to]);

  useEffect(() => {
    planRoute();
  }, []);

  return (
    <main className="min-h-screen overflow-hidden bg-white text-foreground relative">
      <div className="fixed inset-0 z-0 pointer-events-none bg-[linear-gradient(to_right,#8080801a_1px,transparent_1px),linear-gradient(to_bottom,#8080801a_1px,transparent_1px)] bg-[size:40px_40px]"></div>
      <FlowBot onPlanClick={() => plannerRef.current?.scrollIntoView({ behavior: "smooth" })} />
      <header className="sticky top-0 z-40 border-b-[3px] border-black bg-white/95 backdrop-blur">
        <nav className="mx-auto flex max-w-7xl items-center justify-between px-5 py-3">
          <a href="#top" className="flex items-center gap-2 font-display text-lg font-black">
            <span className="size-3 bg-secondary" /> FlowTrip
          </a>
          <div className="hidden items-center gap-8 text-sm font-medium md:flex">
            {navItems.map((item) => (
              <a key={item} href={`#${item.toLowerCase().replace(/\s+/g, "-")}`} className="hover:text-accent">
                {item}
              </a>
            ))}
          </div>
          <div className="flex items-center gap-2">
            <Button variant="flowOutline" size="sm" onClick={() => plannerRef.current?.scrollIntoView({ behavior: "smooth" })}>
              <MessageCircle /> Ask FlowBot
            </Button>
            <Button variant="flow" size="sm" onClick={() => plannerRef.current?.scrollIntoView({ behavior: "smooth" })}>
              Plan Journey <ArrowRight />
            </Button>
          </div>
        </nav>
      </header>

      <section id="top" className="mx-auto grid max-w-7xl gap-10 px-5 py-14 md:grid-cols-[0.92fr_1.08fr] md:py-20 relative z-10">
        <motion.div initial={{ opacity: 0, y: 30 }} animate={{ opacity: 1, y: 0 }} transition={{ duration: 0.6, staggerChildren: 0.1 }} className="space-y-8 flex flex-col justify-center">
          <motion.span initial={{ opacity: 0, x: -20 }} animate={{ opacity: 1, x: 0 }} className="flow-tag inline-flex items-center gap-2 w-fit border-[3px] border-black bg-white px-3 py-1 font-display text-[0.6rem] font-bold uppercase tracking-widest shadow-[4px_4px_0_0_#000]"><span className="size-2 bg-success" /> Live in 15+ transit authorities</motion.span>
          
          <motion.div initial={{ opacity: 0, y: 20 }} animate={{ opacity: 1, y: 0 }} className="space-y-5">
            <h1 className="max-w-3xl font-display text-4xl font-black leading-[1.05] tracking-tight text-black md:text-[4.5rem]">
              Your Commute.<br/>
              <span className="text-[#0033cc]">Unified. Intelligent. Reliable.</span>
            </h1>
            <p className="max-w-2xl text-lg leading-relaxed text-zinc-600 font-medium">
              Every bus, metro, bike and walk — stitched into one elegant journey. Real-time. Multi-modal. Built for the cities we actually live in.
            </p>
          </motion.div>
          
          <motion.div initial={{ opacity: 0, y: 20 }} animate={{ opacity: 1, y: 0 }} className="flex flex-wrap gap-4 pt-2">
            <Button variant="flow" size="flow" onClick={() => plannerRef.current?.scrollIntoView({ behavior: "smooth" })} className="border-[3px] border-black shadow-[6px_6px_0_0_#000] transition-all hover:-translate-y-1 hover:shadow-[6px_8px_0_0_#000]">
              Start a Journey <ArrowRight />
            </Button>
            <Button variant="flowOutline" size="flow" asChild className="border-[3px] border-black bg-white shadow-[6px_6px_0_0_#000] transition-all hover:-translate-y-1 hover:shadow-[6px_8px_0_0_#000]">
              <a href="#how-it-works">See How It Works</a>
            </Button>
          </motion.div>
          
          <motion.div initial={{ opacity: 0 }} animate={{ opacity: 1 }} transition={{ delay: 0.5 }} className="grid max-w-xl grid-cols-3 gap-5 pt-8 border-t-[3px] border-black/10 mt-4">
            {routeSummary.map((item) => (
              <div key={item.label}>
                <div className="font-display text-3xl font-black text-black">{item.value}</div>
                <div className="font-display text-[0.58rem] font-bold uppercase tracking-[0.42em] text-zinc-500 mt-1">{item.label}</div>
              </div>
            ))}
          </motion.div>
        </motion.div>

        <motion.div initial={{ opacity: 0, scale: 0.95, rotate: -2 }} animate={{ opacity: 1, scale: 1, rotate: 0 }} transition={{ duration: 0.8, type: "spring" }} className="relative z-10 flex items-center">
          <div className="flow-panel overflow-hidden border-[4px] border-black shadow-[12px_12px_0_0_#000] bg-white w-full">
            <div className="relative aspect-[0.85] min-h-[520px]">
              <img src={trainImage} alt="Mumbai local train passing through dense Indian city housing" className="h-full w-full object-cover" width={1280} height={900} />
              
              <div className="absolute right-6 top-6 bg-[#ffe01b] border-[3px] border-black px-4 py-2 font-display text-xs font-black uppercase tracking-[0.32em] text-black shadow-[4px_4px_0_0_#000]">
                v1.0 · beta
              </div>
              
              <div className="absolute bottom-6 left-6 right-6 border-[3px] border-black bg-white p-5 shadow-[6px_6px_0_0_#000]">
                <div className="mb-4 flex items-center justify-between font-display text-[0.65rem] font-black uppercase tracking-[0.35em] text-black">
                  <span className="flex items-center gap-2"><LocateFixed className="size-4"/> Live Route</span>
                  <span className="bg-success/20 text-success px-2 py-1">On Time</span>
                </div>
                
                <div className="flex h-3 border-2 border-black">
                  <div className="w-[30%] bg-[#0033cc] h-full animate-pulse"/>
                  <div className="w-[10%] bg-transparent h-full"/>
                  <div className="w-[40%] bg-[#ffe01b] h-full animate-pulse" style={{animationDelay: "0.2s"}}/>
                  <div className="w-[10%] bg-transparent h-full"/>
                  <div className="w-[10%] bg-success h-full animate-pulse" style={{animationDelay: "0.4s"}}/>
                </div>
                
                <div className="mt-4 flex items-baseline gap-3 text-black">
                  <span className="font-display text-3xl font-black">28</span>
                  <span className="font-display text-xs font-bold uppercase tracking-widest text-zinc-500">MIN</span>
                  <span className="ml-auto font-mono text-sm font-bold text-zinc-500">₹{route?.cost ?? "3.20"}</span>
                </div>
              </div>
            </div>
          </div>
        </motion.div>
      </section>

      <section id="problem" className="mx-auto max-w-7xl px-5 py-20 relative z-10">
        <motion.div initial={{ opacity: 0, y: 40 }} whileInView={{ opacity: 1, y: 0 }} viewport={{ once: true, margin: "-100px" }} transition={{ duration: 0.6 }}>
          <span className="font-display text-xs font-bold uppercase tracking-[0.5em] text-zinc-500">[ 01 / Problem ]</span>
          <h2 className="mt-5 max-w-4xl font-display text-4xl font-black leading-tight text-black md:text-5xl">Urban transit is broken — because it was never designed <em>together.</em></h2>
          <p className="mt-5 max-w-4xl text-lg leading-8 text-zinc-600">India's commuters move through dozens of operators every week. FlowTrip starts by naming what's broken.</p>
        </motion.div>
        <motion.div 
          initial="hidden" 
          whileInView="show" 
          viewport={{ once: true, margin: "-100px" }} 
          variants={{ show: { transition: { staggerChildren: 0.1 } } }} 
          className="mt-12 grid gap-6 md:grid-cols-2"
        >
          {[
            [Layers3, "Fragmented apps", "Every transit mode lives in its own silo — you juggle six apps to cross one city.", "bg-secondary"],
            [Clock3, "Static timetables", "Printed schedules never match reality. Buses disappear, trains shift, plans break.", "bg-bus"],
            [Wallet, "Hidden costs", "Surge fares, transfer penalties, and missing price visibility wreck daily budgets.", "bg-auto"],
            [ShieldCheck, "No reliability signal", "You cannot see which route will actually show up on time — you just hope.", "bg-rail"],
          ].map(([Icon, title, text, color]) => (
            <motion.article 
              key={String(title)} 
              variants={{ hidden: { opacity: 0, y: 20 }, show: { opacity: 1, y: 0 } }} 
              className="border-[3px] border-black bg-white p-7 shadow-[6px_6px_0_0_#000] transition-transform hover:-translate-y-2 hover:shadow-[8px_8px_0_0_#000]"
            >
              <div className={`mb-7 inline-flex size-12 items-center justify-center border-[3px] border-black ${color}`}><Icon className="size-6" /></div>
              <div className="font-display text-[0.62rem] font-bold uppercase tracking-[0.45em] text-zinc-500">[{title.charAt(0).padStart(2, "0")}]</div>
              <h3 className="mt-3 font-display text-xl font-black text-black">{String(title)}</h3>
              <p className="mt-3 text-zinc-600 font-medium">{String(text)}</p>
            </motion.article>
          ))}
        </motion.div>
      </section>

      <section id="features" className="bg-[#ffe01b] py-24 relative z-10 border-y-[3px] border-black shadow-[0_6px_0_0_#000]">
        <motion.div initial={{ opacity: 0, scale: 0.95 }} whileInView={{ opacity: 1, scale: 1 }} viewport={{ once: true }} transition={{ duration: 0.6 }} className="mx-auto max-w-7xl px-5">
          <span className="font-display text-xs font-bold uppercase tracking-[0.5em] text-black/70">[ 02 / Solution ]</span>
          <h2 className="mt-5 font-display text-4xl font-black text-black md:text-5xl">One interface for every way the <span className="text-[#0033cc] bg-white px-2 border-2 border-black">city moves.</span></h2>
          <p className="mt-5 max-w-5xl text-lg leading-8 text-black/80 font-medium">FlowTrip stitches BMTC, BEST, DMRC, MSRTC, IRCTC, Mumbai locals, autos, and on-demand cabs into a single planning fabric.</p>
          <motion.div initial="hidden" whileInView="show" viewport={{ once: true }} variants={{ show: { transition: { staggerChildren: 0.05 } } }} className="mt-12 grid gap-4 md:grid-cols-3 lg:grid-cols-6">
            {[
              [LocateFixed, "Walk", "Integrated", "bg-walk"],
              [Bus, "Bus", "Integrated", "bg-bus"],
              [Train, "Train", "Integrated", "bg-rail"],
              [Route, "Metro", "Integrated", "bg-rail"],
              [Navigation, "Auto", "Integrated", "bg-auto"],
              [Car, "Cab", "Integrated", "bg-auto"],
            ].map(([Icon, title, meta, color]) => (
              <motion.div key={String(title)} variants={{ hidden: { opacity: 0, y: 10 }, show: { opacity: 1, y: 0 } }} className="flex flex-col items-center gap-3 border-[3px] border-black bg-white p-5 text-center shadow-[4px_4px_0_0_#000] hover:shadow-[6px_6px_0_0_#000] transition-shadow">
                <div className={`flex size-12 items-center justify-center border-[3px] border-black ${color}`}><Icon className="size-6" /></div>
                <div><div className="font-display font-black text-black">{String(title)}</div><div className="font-display text-[0.58rem] font-bold uppercase tracking-[0.42em] text-zinc-500 mt-1">{String(meta)}</div></div>
              </motion.div>
            ))}
          </motion.div>
        </motion.div>
      </section>

      <section id="journey-planner" ref={plannerRef} className="mx-auto max-w-7xl px-5 py-20">
        <span className="font-display text-xs font-bold uppercase tracking-[0.5em] text-muted-foreground">[ 03 / Journey Planner ]</span>
        <h2 className="mt-5 font-display text-4xl font-black md:text-5xl">Plan any journey across India.</h2>
        <div className="mt-5 flex flex-wrap gap-2">
          {fallbackPlaces.slice(0, 4).map((place, index) => (
            <button key={place.label} onClick={() => (index % 2 === 0 ? (setFrom(place), setFromQuery(place.label)) : (setTo(place), setToQuery(place.label)))} className="border border-border bg-card px-3 py-2 font-display text-[0.62rem] font-bold uppercase tracking-[0.35em] hover:bg-secondary">
              {place.label.split(",")[0]}
            </button>
          ))}
        </div>

        <div className="mt-10 grid gap-8 lg:grid-cols-[0.85fr_1.15fr]">
          <div className="flow-panel p-5 md:p-7">
            <div className="space-y-6">
              <PlaceInput label="From" value={fromQuery} onChange={(value) => { setFromQuery(value); setFrom(null); }} onSelect={(place) => { setFrom(place); setFromQuery(place.label); }} />
              <div className="flex justify-center"><div className="bg-secondary p-2"><RefreshCw className="size-4" /></div></div>
              <PlaceInput label="To" value={toQuery} onChange={(value) => { setToQuery(value); setTo(null); }} onSelect={(place) => { setTo(place); setToQuery(place.label); }} />
              <div className="space-y-2">
                <label className="font-display text-[0.65rem] font-bold uppercase tracking-[0.42em] text-muted-foreground">Departure</label>
                <div className="grid grid-cols-3 gap-2">
                  {["now", "+15 min", "+1 hr"].map((item) => (
                    <button key={item} onClick={() => setDeparture(item)} className={`border-2 border-border px-4 py-3 font-display text-xs font-bold uppercase tracking-[0.24em] ${departure === item ? "bg-primary text-primary-foreground" : "bg-card"}`}>{item}</button>
                  ))}
                </div>
              </div>
              <Button variant="flow" size="flow" className="w-full" onClick={planRoute} disabled={isPlanning}>
                {isPlanning ? <RefreshCw className="animate-spin" /> : <Sparkles />} Plan Journey
              </Button>
              <div className="flex items-center gap-2 text-sm font-bold"><CheckCircle2 className="size-4" /> {status}</div>
            </div>
          </div>

          <div className="space-y-5">
            {routeOptions.length > 0 && (
              <div className="grid gap-3 md:grid-cols-3">
                {routeOptions.map((option) => (
                  <button
                    key={option.id}
                    type="button"
                    onClick={() => setRoute(option)}
                    className={`border-2 border-border p-4 text-left transition-transform hover:-translate-y-1 ${route?.id === option.id ? "bg-secondary shadow-hard" : "bg-card"}`}
                  >
                    <div className="flex items-center justify-between gap-3">
                      <div className="font-display text-lg font-black">{option.name}</div>
                      <span className="bg-primary px-2 py-1 font-display text-[0.55rem] font-bold uppercase tracking-[0.24em] text-primary-foreground">{option.badge}</span>
                    </div>
                    <div className="mt-3 grid grid-cols-3 gap-2 text-sm font-bold">
                      <span>{Math.round(option.durationMin)} min</span>
                      <span>₹{option.cost}</span>
                      <span>{option.reliability}%</span>
                    </div>
                    <div className="mt-3 flex gap-1">
                      {option.segments.map((segment, index) => (
                        <span key={`${option.id}-${segment.mode}-${index}`} className={`h-2 flex-1 border border-border ${modeMeta[segment.mode].className}`} />
                      ))}
                    </div>
                  </button>
                ))}
              </div>
            )}
            <div className="grid gap-3 md:grid-cols-4">
              {[
                [Clock3, "Time", route ? `${Math.round(route.durationMin)} min` : "—"],
                [IndianRupee, "Cost", route ? `₹${route.cost}` : "—"],
                [ShieldCheck, "Reliability", route ? `${route.reliability}%` : "—"],
                [Leaf, "CO₂", route ? `${route.co2}g` : "—"],
              ].map(([Icon, label, value]) => (
                <div key={String(label)} className="border-2 border-border bg-card p-4">
                  <Icon className="mb-3 size-5" />
                  <div className="font-display text-2xl font-black">{String(value)}</div>
                  <div className="font-display text-[0.58rem] font-bold uppercase tracking-[0.34em] text-muted-foreground">{String(label)}</div>
                </div>
              ))}
            </div>
            <div className="flow-panel overflow-hidden">
              <AppMap route={route} from={from} to={to} />
              <div className="border-t-2 border-border p-5">
                <div className="mb-4 flex justify-between font-display text-[0.65rem] font-bold uppercase tracking-[0.42em]"><span>{route?.name ?? "Route"} · {route?.segments.length ?? 0} segments</span><span>{route ? `${route.distanceKm.toFixed(1)} km total` : "No route yet"}</span></div>
                <div className="space-y-3">
                  {route ? route.segments.map((segment) => {
                    const meta = modeMeta[segment.mode];
                    const Icon = meta.icon;
                    return (
                      <div key={`${segment.mode}-${segment.title}`} className="grid grid-cols-[44px_1fr_auto] items-center gap-3 border-2 border-border bg-background p-3">
                        <div className={`flex size-9 items-center justify-center border-2 border-border ${meta.className}`}><Icon className="size-4" /></div>
                        <div><div className="font-display font-bold">{segment.title}</div><div className="font-display text-[0.58rem] font-bold uppercase tracking-[0.34em] text-muted-foreground">{meta.label} · {segment.detail}</div></div>
                        <div className="text-right text-sm font-bold"><div>{segment.minutes} min</div><div className="text-muted-foreground">₹{segment.cost}</div></div>
                      </div>
                    );
                  }) : <div className="border-2 border-dashed border-border p-8 text-center font-display font-bold">Choose Indian locations to compute a live OSRM route.</div>}
                </div>
              </div>
            </div>
          </div>
        </div>
      </section>

      <section id="how-it-works" className="mx-auto max-w-7xl px-5 py-20">
        <span className="font-display text-xs font-bold uppercase tracking-[0.5em] text-muted-foreground">[ 04 / How it works ]</span>
        <h2 className="mt-5 font-display text-4xl font-black md:text-5xl">From query to commute, in four moves.</h2>
        <div className="mt-10 grid gap-6 md:grid-cols-2">
          {[
            [Search, "Tell us where", "Pick a source and destination anywhere in India with Nominatim autocomplete."],
            [Route, "We stitch the journey", "FlowTrip blends walk, auto, rail and bus into a continuous plan using OSRM distance."],
            [ShieldCheck, "Three real options", "Compare fastest, cheapest and most reliable route logic with transparent metrics."],
            [Sparkles, "Ask FlowBot anything", "A travel assistant surface is ready for Indian mobility questions and support."],
          ].map(([Icon, title, text], index) => (
            <article key={String(title)} className="flow-panel p-7">
              <div className="font-display text-[0.62rem] font-bold uppercase tracking-[0.42em] text-muted-foreground">Step 0{index + 1}</div>
              <div className="mt-5 inline-flex size-11 items-center justify-center bg-primary text-primary-foreground"><Icon className="size-5" /></div>
              <h3 className="mt-6 font-display text-xl font-black">{String(title)}</h3>
              <p className="mt-3 text-muted-foreground">{String(text)}</p>
            </article>
          ))}
        </div>
      </section>

      <footer className="relative overflow-hidden bg-[#0a0a0a] pb-[340px] pt-20 text-zinc-400">
        <div className="relative z-10 mx-auto max-w-7xl px-5">
          <div className="grid gap-12 md:grid-cols-5 lg:gap-8">
            <div className="md:col-span-2">
              <div className="flex items-center gap-2 font-display text-xl font-bold text-white">
                <span className="size-3 bg-yellow-400" /> FlowTrip
              </div>
              <p className="mt-5 max-w-sm text-sm leading-relaxed text-zinc-400">
                The operating system for urban mobility. Unified, intelligent, reliable.
              </p>
            </div>
            
            <div>
              <h3 className="mb-6 font-display text-[0.65rem] font-bold uppercase tracking-[0.2em] text-zinc-500">Product</h3>
              <ul className="space-y-4 text-sm">
                <li><a href="#" className="transition-colors hover:text-white">Journey Planner</a></li>
                <li><a href="#" className="transition-colors hover:text-white">Features</a></li>
                <li><a href="#" className="transition-colors hover:text-white">AI Assistant</a></li>
                <li><a href="#" className="transition-colors hover:text-white">Changelog</a></li>
              </ul>
            </div>

            <div>
              <h3 className="mb-6 font-display text-[0.65rem] font-bold uppercase tracking-[0.2em] text-zinc-500">Company</h3>
              <ul className="space-y-4 text-sm">
                <li><a href="#" className="transition-colors hover:text-white">About</a></li>
                <li><a href="#" className="transition-colors hover:text-white">Customers</a></li>
                <li><a href="#" className="transition-colors hover:text-white">Careers</a></li>
                <li><a href="#" className="transition-colors hover:text-white">Press</a></li>
              </ul>
            </div>

            <div>
              <h3 className="mb-6 font-display text-[0.65rem] font-bold uppercase tracking-[0.2em] text-zinc-500">Resources</h3>
              <ul className="space-y-4 text-sm">
                <li><a href="#" className="transition-colors hover:text-white">Docs</a></li>
                <li><a href="#" className="transition-colors hover:text-white">API</a></li>
                <li><a href="#" className="transition-colors hover:text-white">Transit partners</a></li>
                <li><a href="#" className="transition-colors hover:text-white">Support</a></li>
              </ul>
            </div>

            <div>
              <h3 className="mb-6 font-display text-[0.65rem] font-bold uppercase tracking-[0.2em] text-zinc-500">Legal</h3>
              <ul className="space-y-4 text-sm">
                <li><a href="#" className="transition-colors hover:text-white">Privacy</a></li>
                <li><a href="#" className="transition-colors hover:text-white">Terms</a></li>
                <li><a href="#" className="transition-colors hover:text-white">Security</a></li>
                <li><a href="#" className="transition-colors hover:text-white">Contact</a></li>
              </ul>
            </div>
          </div>

          <div className="mt-20 flex flex-col items-center justify-between gap-4 border-t border-zinc-800/50 pt-8 font-mono text-[0.65rem] text-zinc-500 md:flex-row">
            <span>© 2026 FlowTrip Labs. All rights reserved.</span>
            <span>Built for cities that never stop.</span>
          </div>
        </div>

        <div className="pointer-events-none absolute bottom-12 left-0 right-0 flex select-none justify-center">
          <span className="font-display text-[20vw] font-black leading-none text-zinc-800/30">
            FlowTrip
          </span>
        </div>
      </footer>
    </main>
  );
};

export default Index;