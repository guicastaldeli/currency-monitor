package main

import (
	"encoding/json"
	"fmt"
	"io"
	"time"
)

const DATA_URL = "/currencies"
const RATE_URL = "%s/latest?base=%s&symbols=%s"
const REQUEST_SUCCESS = 200

// Get Currencies
func getCurrencies() (map[string]string, error) {
	resp, err := httpClient.Get(API_URL + DATA_URL)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()

	if resp.StatusCode != REQUEST_SUCCESS {
		body, _ := io.ReadAll(resp.Body)
		return nil, fmt.Errorf("HTTP %d: %s", resp.StatusCode, string(body))
	}

	var result map[string]string
	if err := json.NewDecoder(resp.Body).Decode(&result); err != nil {
		return nil, err
	}

	return result, nil
}

// Get All Currencies
func getAllCurrencies() {
	mu.Lock()
	snapshot := make([]pair, len(pairs))
	copy(snapshot, pairs)
	mu.Unlock()

	for _, p := range snapshot {
		rate, err := getCurrencyRate(p.From, p.To)
		if err != nil {
			EmitError(fmt.Sprintf("Failed %s/%s: %v", p.From, p.To, err))
			continue
		}

		Emit(map[string]interface{}{
			"type":      "rate",
			"from":      p.From,
			"to":        p.To,
			"rate":      rate,
			"timestamp": time.Now().Unix(),
		})
	}
}

// Get Currency Rate
func getCurrencyRate(from, to string) (float64, error) {
	url := fmt.Sprintf(RATE_URL, API_URL, from, to)
	resp, err := httpClient.Get(url)
	if err != nil {
		return 0, err
	}

	defer resp.Body.Close()
	if resp.StatusCode != REQUEST_SUCCESS {
		body, _ := io.ReadAll(resp.Body)
		return 0, fmt.Errorf("HTTP %d: %s", resp.StatusCode, string(body))
	}

	var parsed struct {
		Rates map[string]float64 `json:"rates"`
	}
	if err := json.NewDecoder(resp.Body).Decode(&parsed); err != nil {
		return 0, err
	}

	rate, ok := parsed.Rates[to]
	if !ok {
		return 0, fmt.Errorf("rate for %s not in response", to)
	}
	return rate, nil
}

// Request Currencies
func requestCurrencies() {
	go func() {
		list, err := getCurrencies()
		if err != nil {
			EmitError(fmt.Sprintf("Failed to load currencies: %v", err))
			return
		}

		Emit(map[string]interface{}{
			"type": "currencies",
			"list": list,
		})
	}()
}
