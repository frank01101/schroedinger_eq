# skrypt realizujacy petle w gnuplocie
if(!exists('n')) n=500
plot "< ./schrod_cn_1d.out" u 1:5 w l, "< ./schrod_cn_1d.out" u 1:4 w l, "< ./schrod_cn_1d.out" u 1:2 w l, "< ./schrod_cn_1d.out" u 1:3 w l
#pause .1
n=n-1
if(n>0) reread
