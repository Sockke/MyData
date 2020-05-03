package main

import (
	"math"
	"math/rand"
	"time"
)

const MAX_INT = int(^uint(0) >> 1)
const MIN_INT = int(^MAX_INT)

func main() {
	v := []int{9, 5, 2, 7}
	maxnum, minnum := getMaxAndMin(v)
	fmt.Println("maxnum:", maxnum)
	fmt.Println("minnum:", minnum)

	reuslt := getPow(2, 3)
	fmt.Println("2^3 =", reuslt)
	reuslt = getSqrt(reuslt)
	fmt.Println("根号8为:", reuslt)

	num := getRand()
	fmt.Println("1~100:", num)
}

func main() {

}

func getMaxAndMin(v []int) (float64, float64) {
	maxnum := float64(MIN_INT)
	minnum := float64(MAX_INT)
	for _, e := range v {
		maxnum = math.Max(maxnum, float64(e))
		minnum = math.Min(minnum, float64(e))
	}
	return maxnum, minnum
}

func getPow(x, y float64) float64 {
	return math.Pow(x, y)
}

func getSqrt(num float64) float64 {
	return math.Sqrt(num)
}

// 随机数
func getRand() int {
	rand.Seed(time.Now().Unix())
	randNum := rand.Intn(100) + 1
	return randNum
}
