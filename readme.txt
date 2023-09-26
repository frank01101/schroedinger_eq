Szanowny Panie Profesorze,

Przesyłam z opóźnieniem (za które najmocniej przepraszam) program
zaliczeniowy z symulacji komputerowych. Jest to rozwiązanie równania
Schroedingera w reprezentacji położeniowej w dwóch wymiarach metodą
niejawną drugiego rzędu (Crancka-Nicholsona) z rozwiązaniem układu równań
metodą iteracyjną Jacobiego. Testowałem wiele metod całkowania tego
równania, najpierw w 1D (w którym to przypadku stabilne, dla rozsądnego
kroku czasowego, były metody: dwustopniowa, Rungego-Kutty 4 rzędu,
Crancka-Nicholsona oraz znaleziona przeze mnie w literaturze metoda
rozwiązania analitycznego z przybliżeniem iteracyjnym operatora
exp(laplasjan)), potem w 2D (gdzie jedyną, spośród użytych przeze mnie,
stabilną metodą, dla rozsądnego kroku czasowego, była załączona do tej
wiadomości metoda Crancka-Nicholsona).

Równanie Schroedingera ma, nie licząc członu z potencjałem, postać podobną
do równania dyfuzji, dlatego też dyfuzja jest widoczna na symulacji. Jak
rozumiem, jest ona manifestacją zasady nieoznaczoności Heisenberga.

Aby uruchomić symulację, należy najpierw wywołać program potencjal_2d.out
i, podążając za instrukcjami, wyświetlanymi na ekranie, wybrać odpowiedni
potencjał, który zostanie zapisany w pliku potencjal_2d.dat. Dalej trzeba
postępować już tak, jak robiliśmy to na zajęciach, czyli uruchomić
gnuplota, wykreślić wynik działania programu schrod_init_2d.out, ustawić
wartość n oraz uruchomić skrypt run.gnu, tak jak poniżej:
gnuplot> splot "< ./schrod_init_2d.out 3" u 1:2:5 pt -1 w pm3d
gnuplot> n=200
gnuplot> load "run.gnu"
Program schrod_init_2d.out można wywołać z argumentem wywołania w postaci
liczby od 1 do 3, oznaczającej liczbę cząstek, biorących udział w symulacji.

Symulacja działa, jak mi się wydaje, prawidłowo.

Z wyrazami szacunku
Franciszek Humieja

