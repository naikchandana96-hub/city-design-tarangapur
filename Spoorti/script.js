/* =====================================================
   UNIVERSAL WASM MODULE LOADER (ALL IDEAS)
   ===================================================== */
const moduleCache = {};

async function loadIdeaModule(ideaNo) {
    if (!moduleCache[ideaNo]) {
        const mod = await import(`./idea${ideaNo}/algo.js`);
        moduleCache[ideaNo] = await mod.default({
            locateFile: (path) => `./idea${ideaNo}/${path}`
        });
    }
    return moduleCache[ideaNo];
} 


/* Universal algorithm runner */
async function runAlgo({ idea, func, json, outputId }) {
    const out = document.getElementById(outputId);
    out.style.display = "block";
    out.innerText = "Running algorithm...";

    try {
        const Module = await loadIdeaModule(idea);
        const jsonData = json ? await fetch(json).then(r => r.text()) : "";

        const runner = Module.cwrap(func, "string", ["string"]);
        out.innerText = runner(jsonData);

    } catch (err) {
        out.innerText = "❌ Error: " + err.message;
    }
}

/* =====================================================
   IDEA 1 – SMART DIGITAL AUCTION
   ===================================================== */

window.runAVL = () => runAlgo({
    idea: 1,
    func: "run_avl",
    json: "./idea1/fish_listings.json",
    outputId: "output-avl"
});

window.runHeap = () => runAlgo({
    idea: 1,
    func: "run_heap",
    json: "./idea1/bids.json",
    outputId: "output-heap"
});

window.runWinner = () => runAlgo({
    idea: 1,
    func: "run_winner",
    json: "./idea1/bids.json",
    outputId: "output-winner"
});

/* =====================================================
   IDEA 2 – ECO TOURISM ROUTE OPTIMIZATION
   ===================================================== */

window.runAVL2 = () => runAlgo({
    idea: 2,
    func: "run_avl2",
    json: "./idea2/eco_locations.json",
    outputId: "output-avl2"
});

window.runDijkstra = () => runAlgo({
    idea: 2,
    func: "run_dijkstra",
    json: "./idea2/eco_routes.json",
    outputId: "output-dijkstra"
});

window.runKruskal = () => runAlgo({
    idea: 2,
    func: "run_kruskal",
    json: "./idea2/eco_edges.json",
    outputId: "output-kruskal"
});

/* =====================================================
   IDEA 3 – SMART IRRIGATION SYSTEM
   ===================================================== */

window.runSegment = () => runAlgo({
    idea: 3,
    func: "run_segment_tree",
    json: "./idea3/moisture.json",
    outputId: "output-segment"
});

window.runMinHeap = () => runAlgo({
    idea: 3,
    func: "run_min_heap",
    json: "./idea3/water_network.json",
    outputId: "output-minheap"
});

window.runIrrigationDijkstra = () => runAlgo({
    idea: 3,
    func: "run_dijkstra",
    json: "./idea3/water_priority.json",
    outputId: "output-irrigation-dijkstra"
});

/* =====================================================
   IDEA 4 – BEACH CLEANING ROBOTS
   ===================================================== */

window.runBeachBFS = () => runAlgo({
    idea: 4,
    func: "run_bfs",
    json: "./idea4/beach_grid.json",
    outputId: "output-bfs"
});

window.runBeachDijkstra = () => runAlgo({
    idea: 4,
    func: "run_dijkstra",
    json: "./idea4/energy_graph.json",
    outputId: "output-energy-dijkstra"
});

window.runGarbageHeap = () => runAlgo({
    idea: 4,
    func: "run_heap",
    json: "./idea4/waste.json",
    outputId: "output-garbage-heap"
});

/* =====================================================
   IDEA 5 – DECENTRALIZED SOLAR ENERGY TRADING
   ===================================================== */

window.runSolarDFS = () => runAlgo({
    idea: 5,
    func: "run_dfs",
    json: "./idea5/solar_grid.json",
    outputId: "output-solar-dfs"
});

window.runSolarDijkstra = () => runAlgo({
    idea: 5,
    func: "run_dijkstra",
    json: "./idea5/energy_cost.json",
    outputId: "output-solar-dijkstra"
});

window.runBellmanFord = () => runAlgo({
    idea: 5,
    func: "run_bellman",
    json: "./idea5/trading_edges.json",
    outputId: "output-bellman"
});

/* =====================================================
   IDEA 6 – FISHERY FUEL OPTIMIZATION
   ===================================================== */

window.runFuelBFS = () => runAlgo({
    idea: 6,
    func: "run_bfs",
    json: "./idea6/sea_zones.json",
    outputId: "output-fuel-bfs"
});

window.runFuelDFS = () => runAlgo({
    idea: 6,
    func: "run_dfs",
    json: "./idea6/sea_zones.json",
    outputId: "output-fuel-dfs"
});

window.runFuelDijkstra = () => runAlgo({
    idea: 6,
    func: "run_dijkstra",
    json: "./idea6/fuel_graph.json",
    outputId: "output-fuel-dijkstra"
});

/* =====================================================
   IDEA 7 – FARMERS PRICE OPTIMIZATION
   ===================================================== */

window.runMarketBFS = () => runAlgo({
    idea: 7,
    func: "run_bfs",
    json: "./idea7/market_zones.json",
    outputId: "output-market-bfs"
});

window.runMarketDijkstra = () => runAlgo({
    idea: 7,
    func: "run_dijkstra",
    json: "./idea7/price_graph.json",
    outputId: "output-market-dijkstra"
});

window.runCropHeap = () => runAlgo({
    idea: 7,
    func: "run_heap",
    json: "./idea7/crops.json",
    outputId: "output-crop-heap"
});

/* =====================================================
   IDEA 8 – WATER TAXI & COASTAL ROUTING
   ===================================================== */

window.runWaterBFS = () => runAlgo({
    idea: 8,
    func: "run_bfs",
    json: "./idea8/water_routes.json",
    outputId: "output-water-bfs"
});

window.runWaterDijkstra = () => runAlgo({
    idea: 8,
    func: "run_dijkstra",
    json: "./idea8/travel_time.json",
    outputId: "output-water-dijkstra"
});

window.runTripScheduler = () => runAlgo({
    idea: 8,
    func: "run_heap",
    json: "./idea8/trips.json",
    outputId: "output-trip-heap"
});
