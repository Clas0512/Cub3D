


// DDA çizgi çizme algoritmasıdır. Çizgiyi çizmek için iki uç noktanın 
//   x-koordinatları ve y-koordinatları arasındaki artımlı 
//   farkı kullanarak çalışan basit ve etkili bir algoritmadır.

// The steps involved in DDA line generation algorithm are:
// 		1-)(x1,y1) ve (x2,y2) 'ye sahip olmamız lazım.
// 		2-)Uç noktaların x-koordinatları ve y-koordinatları arasındaki farkı sırasıyla dx ve dy olarak hesaplayın. (dx, dy)
//		3-)Doğrunun eğimini m = dy/dx olarak hesaplayın.
// 		4-)Çizginin başlangıç ​​noktasını (x1,y1) olarak ayarlayın.
// 		5-)Doğrunun x koordinatlarını her seferinde birer birer artırarak döngü yapın ve y = y1 + m(x – x1)
// 			denklemini kullanarak karşılık gelen y koordinatını hesaplayın.
// 		6-)Hesaplanan (x,y) koordinatındaki pikseli çizin.
// 		7-)Bitiş noktasına (x2,y2) ulaşılana kadar 5. ve 6. adımları tekrarlayın.


