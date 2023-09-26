# skrypt realizujacy petle w gnuplocie
if(!exists('n')) n=200
splot "< ./schrod_cn_2d.out" u 1:2:6 pt -1 w pm3d, "< ./schrod_cn_2d.out" u 1:2:5 pt -1 w pm3d
#pause .1
n=n-1
if(n>0) reread
