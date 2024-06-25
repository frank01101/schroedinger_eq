# script performing loops with the program executions in Gnuplot for the 2D case
# shows the probability amplitude (1:2:5) along with the potential (1:2:6)
if(!exists('n')) n=200
do for [i=1:n] {
	splot "< ./schrod_cn_2d.out" u 1:2:6 pt -1 w pm3d, "< ./schrod_cn_2d.out" u 1:2:5 pt -1 w pm3d
	#pause .1
}
