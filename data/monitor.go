package main

import "time"

type pair struct {
	From string
	To   string
}

var (
	pairs    []pair
	interval = 30 * time.Second
)

//Set Interval Seconds
func setIntervalSeconds(sec int) {
	mu.Lock()
	defer mu.Unlock()

	const secs = 1
	if sec < secs {
		sec = secs
	}

	interval = time.Duration(sec) * time.Second
}

// Monitor Loop
func monitorLoop() {
	getAllCurrencies()

	ticker := time.NewTicker(interval)
	defer ticker.Stop()

	for {
		select {
		case <-stopCh:
			return
		case <-ticker.C:
			getAllCurrencies()
		}
	}
}

// Add Pair
func addPair(f, t string) {
	if f == "" || t == "" || f == t {
		return
	}

	mu.Lock()
	defer mu.Unlock()

	for _, p := range pairs {
		if p.From == f && p.To == t {
			return
		}
	}

	pairs = append(pairs, pair{From: f, To: t})
}

// Remove Pair
func removePair(f, t string) {
	mu.Lock()
	defer mu.Unlock()

	filtered := pairs[:0]
	for _, p := range pairs {
		if !(p.From == f && p.To == t) {
			filtered = append(filtered, p)
		}
	}
	pairs = filtered
}

// Clear Pairs
func clearPairs() {
	mu.Lock()
	defer mu.Unlock()
	pairs = nil
}

// Start Monitor
func startMonitor() {
	mu.Lock()
	defer mu.Unlock()

	if running {
		return
	}
	running = true

	stopCh = make(chan struct{})

	go monitorLoop()
}

// Stop Monitor
func stopMonitor() {
	mu.Lock()
	defer mu.Unlock()
	if !running {
		return
	}

	close(stopCh)
	running = false
}
