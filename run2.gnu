# script performing loops with the program executions in Gnuplot for the 1D case
# shows the real (1:2) and imaginary part (1:3) of the wave function and the probability amplitude (1:4) along with the potential (1:5)
if(!exists('n')) n=500
do for [i=1:n] {
	plot "< ./schrod_cn_1d.out" u 1:5 w l, "< ./schrod_cn_1d.out" u 1:4 w l, "< ./schrod_cn_1d.out" u 1:2 w l, "< ./schrod_cn_1d.out" u 1:3 w l
	#pause .1
}
