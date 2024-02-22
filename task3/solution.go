package main

import (
	"fmt"
	"math/rand"
	"time"
)

func cocktailSort(input []int) []int {
	arr := make([]int, len(input))
	copy(arr, input)
	left := 0
	right := len(arr) - 1
	swapped := true
	for left < right && swapped {
		swapped = false
		for i := right; i > left; i = i - 1 {
			if arr[i] < arr[i-1] {
				arr[i], arr[i-1] = arr[i-1], arr[i]
				swapped = true
			}
		}
		left++
		for i := left; i < right; i++ {
			if arr[i] > arr[i+1] {
				arr[i], arr[i+1] = arr[i+1], arr[i]
				swapped = true
			}
		}
		right--
		if !swapped {
			break
		}
	}
	return arr
}

func shellSort(input []int) []int {
	arr := make([]int, len(input))
	copy(arr, input)
	gap := len(arr) / 2
	for gap > 0 {
		for i := gap; i < len(arr); i++ {
			temp := arr[i]
			j := i
			for j >= gap && arr[j-gap] > temp {
				arr[j] = arr[j-gap]
				j -= gap
			}
			arr[j] = temp
		}
		gap /= 2
	}
	return arr
}

func heapSort(input []int) []int {
	arr := make([]int, len(input))
	copy(arr, input)
	var heapify func(arr []int, n int, i int)
	heapify = func(arr []int, n int, i int) {
		largest := i
		l := 2*i + 1
		r := 2*i + 2
		if l < n && arr[l] > arr[largest] {
			largest = l
		}
		if r < n && arr[r] > arr[largest] {
			largest = r
		}
		if largest != i {
			arr[i], arr[largest] = arr[largest], arr[i]
			heapify(arr, n, largest)
		}
	}
	n := len(arr)
	for i := n/2 - 1; i >= 0; i-- {
		heapify(arr, n, i)
	}
	for i := n - 1; i >= 0; i-- {
		arr[0], arr[i] = arr[i], arr[0]
		heapify(arr, i, 0)
	}
	return arr
}

func measureTime(sortFunc func([]int) []int, arr []int) ([]int, int64) {
	start := time.Now()
	result := sortFunc(arr)
	duration := time.Since(start).Microseconds()
	return result, duration
}

func randomArr(n int) []int {
	arr := make([]int, n)
	for i := 0; i <= n-1; i++ {
		arr[i] = rand.Intn(n)
	}
	return arr
}

func main() {
	var n int
	fmt.Scan(&n)
	arr := randomArr(n)
	fmt.Println("Исходный массив:", arr)
	arr, dur := measureTime(cocktailSort, arr)
	fmt.Println("Шейкерная сортировка:\t ", arr, dur)
	arr, dur = measureTime(shellSort, arr)
	fmt.Println("Метод Шелла:\t\t ", arr, dur)
	arr, dur = measureTime(heapSort, arr)
	fmt.Println("Пирамидальная сортировка:", arr, dur)
}
